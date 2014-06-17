#ifndef SIEC_H
#define SIEC_H

#include <iostream>
#include <WinSock2.h>

class Siec{
public:
	Siec();
	~Siec();
	int firstConn();
	void connection();
	void connection2();
	void importx(const int x);
	void importy(const int y);
	int exportx();
	int exporty();
	int exportShoot();
	void importShoot(const char a);
	void importDrawn(const char b);

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
	char help[1];
};
#endif