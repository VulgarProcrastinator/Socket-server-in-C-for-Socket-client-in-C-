#include "socketutil.h"

int createTCPIpv4Socket(){return socket(AF_INET, SOCK_STREAM, 0);};
    // AF_INET - address family INET A.K.A. IPv4
    // SOCK_STREAM - TCP socket would assume Datagram sockets are for UDP
    // 0 - is for "saying we want an IP layer to be used after our Transport layer"

struct sockaddr_in* createIpv4Address(char *ip, int port){

    //ip ="142.250.188.46";
    
    struct sockaddr_in* address = malloc(sizeof( struct sockaddr_in));
    // struct sockaddr_in {
    //     short int sin_family; // Address family
    //     unsigned short int sin_port; // Port number
    //     struct in_addr sin_addr; // Internet address that is 32-bits, or 4 bytes
    //     unsigned char sin_zero[8]; // Set to zero
    // };
    address->sin_family = AF_INET;
    address->sin_port = htons(port); // will flip the bites to convert in to Network Byte Order

    if(strlen(ip) == 0){
        address->sin_addr.s_addr = INADDR_ANY;
    }else{
        inet_pton(AF_INET, ip, &address->sin_addr.s_addr); // the last part is where it will return the value
    // after spesifying presentation form(version of IP) it will convert a string into an int
    }


    return address;
}

