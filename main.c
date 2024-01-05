#include <netinet/in.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include "lib/socketutil.h"


struct AcceptedSocket{
    int acceptedSocketFD;
    struct sockaddr_in address;
    int error;
    bool acceptedSuccessfully;
};


struct AcceptedSocket* acceptIncomingConnection(int serverSocketFD){
    struct sockaddr_in clientAddress;
    int clientAddressSize = sizeof(struct sockaddr_in);
    int clientSocketFD = accept(serverSocketFD, &clientAddress, &clientAddressSize);
    // accept is a "blocking call", after calling it it will
    // return the "file descriptor" of the connecting client
    // it will create a file descriptor on the server side for each connecting socket  
    // so now our file descriptor on the server and client should be identical and we
    // can use same functions

    struct AcceptedSocket* acceptedSocket = malloc(sizeof(struct AcceptedSocket));
    acceptedSocket->address = clientAddress;
    acceptedSocket->acceptedSocketFD = clientSocketFD;
    acceptedSocket->acceptedSuccessfully = clientSocketFD>0;

    if (!acceptedSocket->acceptedSuccessfully){
        acceptedSocket->error = clientSocketFD;
    }

    return acceptedSocket;
}

int main(){

    int serverSocketFD = createTCPIpv4Socket();

    struct sockaddr_in *serverAdress = createIpv4Address("", 25000);
    
    int result = bind(serverSocketFD, serverAdress, sizeof(*serverAdress));

    if (result == 0){
        printf("Binded socket successfully \n");
    }else {
        fprintf(stderr, "Failed to bind a socket \n");
    }

    int listenResult =listen(serverSocketFD, 10);
    // 10 is a "block loging ammount"(the number of connections we will queue)
        
    struct AcceptedSocket* clientSocket = acceptIncomingConnection(serverSocketFD);

    char buffer[1024];
    while (true) {
        
        size_t ammountRecv = recv(clientSocket->acceptedSocketFD, buffer, 1024, 0);
        // fansy read()

        if (ammountRecv > 0){
            buffer[ammountRecv] =0;
            printf("Recived Responce: %s\n\r", buffer);
        }else if(ammountRecv < 0) {
            break;
        }else {
            break;
        }

    }


    close(clientSocket->acceptedSocketFD);
    shutdown(serverSocketFD, SHUT_RD);


    return 0;
}
