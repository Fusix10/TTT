#pragma once
#include <WinSock2.h>
class Client
{
public:
	Client();
	~Client();
	void Send(int size, int x, int y);
	char* Lisent();
	void Update();
private:
	WSADATA WSAData;
	SOCKET sock;
	SOCKADDR_IN sin;
	int verif;
	char buffer[501];
};

