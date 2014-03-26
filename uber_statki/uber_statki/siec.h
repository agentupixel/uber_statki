#ifndef SIEC_H
#define SIEC_H



#include "wspolny_naglowek.h"
#include "logika.h"
#include <WinSock2.h>

class Siec{
public:
	Siec();
	~Siec();
	void connection();
private:
	int toint(char sign[]);
	char tochar(int sign);
	int x;
	int y;
	WSADATA WsaDat;
	SOCKET Socket;
	struct hostent *host;
	SOCKADDR_IN SockAddr;
	char buffer[1];
	char tempBuffer[1];
	Logika *logika;
};
#endif