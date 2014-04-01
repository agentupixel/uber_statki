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
	logika = new Logika();
	logika->ustawStatki();
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

void Siec::connection(){
	x = 1;
	y = 2;
	recv(Socket, buffer, 1, 0);
	while (buffer[0] != 'l'){
		if (buffer[0] == 't'){
			std::cout << "wybierz cel" << std::endl;
			std::cin >> x;
			std::cin >> y;
			buffer[0] = tochar(x);
			tempBuffer[0] = tochar(y);
			std::cout << "pierwszys" << std::endl;
			send(Socket, buffer, 1, 0);
			std::cout << "drugis" << std::endl;
			send(Socket, tempBuffer, 1, 0);
			std::cout << "pierwszyr" << std::endl;
			recv(Socket, buffer, 1, 0);
			std::cout << "drugir" << std::endl;
			recv(Socket, tempBuffer, 1, 0);
			std::cout << "koniec" << std::endl;
			if ((logika->oznaczCzyTrafiony(buffer[0], x, y)) == 't')
				logika->oznaczCzyZatopiony(tempBuffer[0], x, y);
			if (buffer[0] != 'p' && buffer[0] != 't')
				std::cout << "smieci";

			/*
			send i recv operuj¹ jedynie na char [], wiêc nie przeœlemy struktury
			zawartoœci tempBuffer i buffer
			t - trafiony
			p - pudlo
			z - zatpiony
			n - niezatopiony
			l - przegrana - wysylana przez gracza, jesli juz nie ma zadnych statkow
			*/
		}
		else
			if (buffer[0] == 'p'){
				std::cout << "celuje przeciwnik" << std::endl;
				std::cout << "pierwszypr" << std::endl;
				recv(Socket, buffer, 1, 0);
				x = toint(buffer);
				std::cout << "drugipr" << std::endl;
				recv(Socket, tempBuffer, 1, 0);
				std::cout << "koniecpr" << std::endl;
				y = toint(buffer);
				//todo: sprawdzenie, czy trafi³ i odpowiednie ustawienie buffer i tempbuffer
				buffer[0] = logika->czyPrzeciwnikTrafil(x, y);
				tempBuffer[0] = logika->czyPrzeciwnikZatopil(buffer[0], x, y);
				std::cout << "pierwszyps" << std::endl;
				send(Socket, buffer, 1, 0);
				std::cout << "drugips" << std::endl;
				send(Socket, tempBuffer, 1, 0);
				std::cout << "koniec" << std::endl;
				buffer[0] = (buffer[0] == 't') ? 'p' : 't';
				std::cout << buffer[0] << std::endl;
			}
	}
}
