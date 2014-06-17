#include "siec.h"
#pragma comment(lib,"ws2_32.lib")

Siec::Siec(){
	if (WSAStartup(MAKEWORD(2, 2), &WsaDat) != 0)
	{			
		std::cout << "Winsock error - Winsock initialization failed\r\n";
		WSACleanup();
		system("PAUSE");
		exit(0);
	}

	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Socket == INVALID_SOCKET)
	{
		std::cout << "Winsock error - Socket creation Failed!\r\n";
		WSACleanup();
		system("PAUSE");
		exit(0);
	}
		
	if ((host = gethostbyname("localhost")) == NULL)
	{
		std::cout << "Failed to resolve hostname.\r\n";
		WSACleanup();
		system("PAUSE");
		exit(0);
	}

		
	SockAddr.sin_port = htons(27015);
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

	if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0)
	{
		std::cout << "Failed to establish connection with server\r\n";
		WSACleanup();
		system("PAUSE");
		exit(0);
	}

	
	memset(buffer, 0, 1);
	memset(tempBuffer, 0, 1);

}

Siec::~Siec(){
	shutdown(Socket, SD_SEND);
	closesocket(Socket);
	WSACleanup();
}

int Siec::toint(char sign[]){
	int x = static_cast<int>(sign[0]);
	return x;
}

char Siec::tochar(int sign){
	char x;
	x = static_cast<char>(sign);
	return x;
}

void Siec::importx(const int x){
	Siec::x = x;
}

void Siec::importy(const int y){
	Siec::y = y;
}

int Siec::exportx(){
	return x;
}

int Siec::exporty(){
	return y;
}

void Siec::importShoot(const char a){
	Siec::buffer[0] = a;
}

void Siec::importDrawn(const char b){
	Siec::tempBuffer[0] = b;
}

int Siec::exportShoot(){
	if (buffer[0] == 'p')
		return 0;
	else
		if (buffer[0] == 't' && tempBuffer[0] == 'n')
			return 1;
		else
			return 2;
}

int Siec::firstConn(){
	recv(Socket, buffer, 1, 0);
	if (buffer[0] == 'p')
		return 0;
	else
		return 1;
}

void Siec::connection(){
	if (buffer[0] != 'l'){
		if (buffer[0] == 't'){
			help[0] = buffer[0];
			buffer[0] = tochar(x);
			tempBuffer[0] = tochar(y);
			std::cout << x << ',' << y << std::endl;
			send(Socket, buffer, 1, 0);
			send(Socket, tempBuffer, 1, 0);
		}
		else
			if (buffer[0] == 'p'){
				help[0] = buffer[0];
				recv(Socket, buffer, 1, 0);
				recv(Socket, tempBuffer, 1, 0);
				x = toint(buffer);
				y = toint(tempBuffer);

			}
	}
}

void Siec::connection2(){
	if (help[0] == 'p'){
		send(Socket, buffer, 1, 0);
		send(Socket, tempBuffer, 1, 0);
		buffer[0] = (buffer[0] == 't') ? 'p' : 't';
	}
	if (help[0] == 't'){
		recv(Socket, buffer, 1, 0);
		recv(Socket, tempBuffer, 1, 0);
	}
}

