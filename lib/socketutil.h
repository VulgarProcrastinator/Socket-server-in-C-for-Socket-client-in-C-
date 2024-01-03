#ifndef SOCKETUTIL_H
#define SOCKETUTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int createTCPIpv4Socket();

struct sockaddr_in* createIpv4Address(char *ip, int port);

#endif