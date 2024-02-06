#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#define DEFAULT_BUFLEN 512
#include <iostream>
#define DEFAULT_PORT "27015"

int Client() {
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;


}