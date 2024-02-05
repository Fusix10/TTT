#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#define DEFAULT_BUFLEN 512
#include <iostream>

int buffToInteger(char* buffer)
{
    int a = int((unsigned char)(buffer[0]) << 24 |
                (unsigned char)(buffer[1]) << 16 |
                (unsigned char)(buffer[2]) << 8 |
                (unsigned char)(buffer[3]));
    return a;
};

void somefunction(int v[], int len) {
    std::cout << "vector has " << len << " elements,"
        << " first value is " << v[0] << ","
        << " last value is " << v[len - 1] << std::endl;
}

int main()
{
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2, 0), &WSAData);
    SOCKET sock;
    SOCKADDR_IN sin;
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    sin.sin_family = AF_INET;
    sin.sin_port = htons(4148);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    bind(sock, (SOCKADDR*)&sin, sizeof(sin));
    listen(sock, 0);
    int val = 0;
    while (1)
    {
        int sizeof_csin = sizeof(sin);
        val = accept(sock, (SOCKADDR*)&sin, &sizeof_csin);
        
            if (val != INVALID_SOCKET)
            {
                char recvbuf[DEFAULT_BUFLEN];
                int iResult, iSendResult;
                int recvbuflen = DEFAULT_BUFLEN;

                // Receive until the peer shuts down the connection
                do {
                    iResult = recv(val, recvbuf, recvbuflen, 0);
                    if (iResult > 0) {
                        printf("Bytes received: %d\n", iResult);

                        int b[3];
                        memcpy(b, recvbuf,3 * sizeof(int));
                        somefunction(b, 3);//on s'en branle

                        iSendResult = send(val, recvbuf, iResult, 0);
                        if (iSendResult == SOCKET_ERROR) {
                            printf("send failed: %d\n", WSAGetLastError());
                            closesocket(val);
                            WSACleanup();
                            return 1;
                        }
                        printf("Bytes sent: %d\n", iSendResult);
                    }
                    else if (iResult == 0)
                        printf("Connection closing...\n");
                    else {
                        printf("recv failed: %d\n", WSAGetLastError());
                        closesocket(val);
                        WSACleanup();
                        return 1;
                    }
                } while (iResult > 0);
                // int taille obligadade( combien de bite),int i,int j
                // int Taille, int i, int j, bool error/succes
            }
    }
    WSACleanup();
    return 0;
}
