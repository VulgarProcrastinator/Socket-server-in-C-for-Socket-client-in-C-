#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

#include "lib/socketutil.h"

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
        
    struct sockaddr_in clientAddress;
    int clientAddressSize = sizeof(struct sockaddr_in);
    int clientSocketFD = accept(serverSocketFD, &clientAddress, &clientAddressSize);
    // accept is a "blocking call", after calling it it will
    // return the "file descriptor" of the connecting client
    // it will create a file descriptor on the server side for each connecting socket  
    // so now our file descriptor on the server and client should be identical and we
    // can use same functions

    char buffer[1024];
    recv(clientSocketFD, buffer, 1024, 0);
    // fansy read()

    printf("Responce: %s \n", buffer);


    return 0;
}
