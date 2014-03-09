#include <winsock.h>
#include <windows.h>
#include <iostream>
#include <time.h>

//#include "../wspoldzielony_naglowek.h"

#pragma comment(lib, "wsock32.lib")

using namespace std;

// struktura reprezentujaca klienta-gracza
struct SGracz
{
	SOCKET socket;
	sockaddr_in adres;
	int ostatniaWylosowanaLiczba;
	bool gotowy;
	bool wszystkiePionkiNaMecie;
	bool odlaczony;
};

SGracz gracze[4];
int iloscGraczy = 0;
int graczeNaMecie = 0;
int ruchGracza = 0;
//SGra gra;
SGracz gra;
void InicjujGre()
{
	memset(&gra, 0, sizeof(gra));
	memset(&gracze, 0, sizeof(gracze));
	iloscGraczy = 0;
}

void CzyscPole(int pole)
{
	// jesli pole jest zajete
	if (gra.plansza[pole])
	{
		char pionek = gra.plansza[pole];
		// odeslij stojacego tam pionka do domku
		gra.plansza[pole] = 0;
		int czyj = pionek - 1;
		for (int i = 0; i < 4; i++)
		{
			if (gra.domki[czyj][i] == 0)
			{
				gra.domki[czyj][i] = pionek;
				return;
			}
		}
		// to nie powinno sie zdazyc
		printf("CzyscPole: blad, nie bylo miejsca w domku!\n");
	}
}

void WyslijPakiet(int gracz, void *dane, int dlugosc)
{
	int wyslano = send(gracze[gracz].socket, (char*)dane, dlugosc, 0);
	printf("WyslijPakiet : wyslane %i (%i)\n", wyslano, dlugosc);
}
void WyslijPakiet4Bajtowy(int gracz, int ident)
{
	WyslijPakiet(gracz, &ident, 4);
}
void PrzesunPionekZPolaODanaIloscKratek(int gracz, int pole, int ileKratek)
{
	// pole ujemne oznacza wyjscie z domku
	if (pole < 0)
	{
		if (ileKratek == 1 || ileKratek == 6)
		{
			printf("Gracz %i wychodzi pionkiem z domku!\n", gracz);
			gra.domki[gracz][-pole - 1] = 0;
			int poleStartowe;
			if (gracz == 0)
			{
				poleStartowe = GRACZ1_START;
			}
			else if (gracz == 1)
			{
				poleStartowe = GRACZ2_START;
			}
			else if (gracz == 2)
			{
				poleStartowe = GRACZ3_START;
			}
			else if (gracz == 3)
			{
				poleStartowe = GRACZ4_START;
			}
			CzyscPole(poleStartowe);
			gra.plansza[poleStartowe] = gracz + 1;


		}
	}
	else
	{
		int dokad = pole + ileKratek;
		int polaStartowe[4] =
		{
			GRACZ1_START, GRACZ2_START, GRACZ3_START, GRACZ4_START,
		};
		int poleKoncowe[4] =
		{
			GRACZ1_META, GRACZ2_META, GRACZ3_META, GRACZ4_META
		};
		if (pole < poleKoncowe[gracz] && dokad >= poleKoncowe[gracz])
		{
			printf("Pionek wszedl na mete\n");
			int i;
			for (i = 0; i < 4; i++)
			{
				if (gra.meta[gracz][i] == 0)
				{
					gra.meta[gracz][i] = gra.plansza[pole];
					break;
				}
			}
			if (i == 3)
			{
				// wyslik pakiet do zwyciezscy
				WyslijPakiet4Bajtowy(gracz, PSK_WYGRALES);

				gracze[gracz].wszystkiePionkiNaMecie = true;
				graczeNaMecie++;
			}
			gra.plansza[pole] = 0;
		}
		else {
			if (dokad >= 40)
			{
				dokad -= 40;
			}
			CzyscPole(dokad);
			gra.plansza[dokad] = gra.plansza[pole];
			gra.plansza[pole] = 0;
			printf("Gracz %i przesuwa pionek z %i do %i\n", gracz, pole, dokad);
		}
	}
}


int RzutKostka()
{
	//losowanie kostka
	// kostka mozna wyrzucic: 
	// 1,2,3,4,5,6
	int ret = (rand() % 6) + 1;
	printf("RzutKostka: %i\n", ret);
	return ret;
}
void WyslijStanGryDoWszystkichGraczy()
{
	SPakiet_SK_StanGry pakietStanuGry;
	pakietStanuGry.identyfikator = PSK_STAN_GRY;
	pakietStanuGry.stan = gra;
	for (int i = 0; i < iloscGraczy; i++)
	{
		WyslijPakiet(i, &pakietStanuGry, sizeof(pakietStanuGry));
	}
}
void UstawPionkiGraczyNaPolachStartowych()
{
	for (int i = 0; i < iloscGraczy; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			gra.domki[i][j] = i + 1;
		}
	}
}
void ustawNumerNastepnegoGracza()
{
	ruchGracza++;
	if (ruchGracza >= iloscGraczy)
		ruchGracza = 0;
	while (gracze[ruchGracza].wszystkiePionkiNaMecie || gracze[ruchGracza].odlaczony)
	{
		ruchGracza++;
		if (ruchGracza >= iloscGraczy)
			ruchGracza = 0;
	}
}
void ObsluzPakietGracza(int gracz, void *dane, int dlugosc)
{
	SPakiet *p = (SPakiet*)dane;
	if (p->identyfikator == PKS_CZY_MOZNA_DOLACZYC)
	{
		printf("Klient %i pyta czy mozna dolaczyc\n", gracz);
		if (gra.stanGry == GRA_OCZEKUJENAGRACZY)
		{
			printf(".. pozwalam mu dolaczyc\n");
			SPakiet_SK_AkceptacjaGracza odpowiedzAkceptacja;
			odpowiedzAkceptacja.identyfikator = PSK_AKCEPTACJA_DOLACZENIA;
			odpowiedzAkceptacja.numerGracza = gracz;
			WyslijPakiet(gracz, &odpowiedzAkceptacja, sizeof(odpowiedzAkceptacja));
		}
		else
		{
			printf(".. odmawiam mu dolaczenia bo gra juz trwa\n");
			WyslijPakiet4Bajtowy(gracz, PSK_ODMOWA_DOLACZENIA);
		}
	}
	else if (p->identyfikator == PKS_LOSUJ_LICZBE)
	{
		int liczba = RzutKostka();
		printf("Klient %i wylosowal %i\n", gracz, liczba);
		SPakiet_SK_WylosowanoLiczbe odpowiedz;
		odpowiedz.identyfikator = PSK_WYNIK_RZUTU_KOSTKA;
		odpowiedz.liczba = liczba;
		WyslijPakiet(gracz, &odpowiedz, sizeof(odpowiedz));
		gracze[gracz].ostatniaWylosowanaLiczba = liczba;
	}
	else if (p->identyfikator == PKS_RUCH_PIONKIEM)
	{
		SPakiet_KS_RuchPionkiem *pRuch = (SPakiet_KS_RuchPionkiem*)p;
		int ktorePole = pRuch->pole;
		int kostka = gracze[gracz].ostatniaWylosowanaLiczba;
		//kostka = 1;
		printf("odebralem pakiet PKS_RUCH_PIONKIEM, pole to %i, a kostka %i\n", ktorePole, kostka);
		PrzesunPionekZPolaODanaIloscKratek(gracz, ktorePole, kostka);
		// jesli wyrzucil 6, niech rzuca jeszce raz
		if (kostka == 6)
		{
			WyslijPakiet4Bajtowy(gracz, PSK_TWOJ_RUCH);
			printf("Gracz %i rzuca jeszcze raz bo wyrzucil 6\n", ruchGracza);
		}
		else
		{
			if (iloscGraczy > graczeNaMecie)
			{
				ustawNumerNastepnegoGracza();

				WyslijPakiet4Bajtowy(ruchGracza, PSK_TWOJ_RUCH);
				printf("Nastepny ruch ma gracz: %i\n", ruchGracza);
			}
			else
			{
				printf("Wszyscy sa juz na mecie\n");
			}
		}
		WyslijStanGryDoWszystkichGraczy();
	}
	else if (p->identyfikator == PKS_JESTEM_GOTOW)
	{
		gracze[gracz].gotowy = true;
		// sprawdz czy wszyscy gracze sa gotowi
		for (int i = 0; i < iloscGraczy; i++)
		{
			if (gracze[i].gotowy == false)
				return;
		}
		// wszyscy sa gotowi, rozpocznij gry
		printf("Wszyscy gracze (%i) gotowi, rozpoczynam gre!\n", iloscGraczy);
		gra.stanGry = GRA_AKTYWNA;
		UstawPionkiGraczyNaPolachStartowych();

		WyslijStanGryDoWszystkichGraczy();
		// popros pierwszego gracza o ruch
		WyslijPakiet4Bajtowy(0, PSK_TWOJ_RUCH);
	}
	else if (p->identyfikator == PKS_KLIENT_ZAMKNAL_PROGRAM)
	{
		gracze[gracz].odlaczony = true;
		// usun pionki gracza
		for (int i = 0; i < 40; i++)
		{
			if (gra.plansza[i] == gracz)
			{
				gra.plansza[i] = 0;
			}
			memset(gra.domki[gracz], 0, sizeof(int)* 4);
		}
		// sprawdz czy jest wystarczajaco graczy by grac
		int ile = 0;
		for (int i = 0; i < iloscGraczy; i++)
		{
			if (gracze[i].odlaczony == false)
				ile++;
		}
		if (ile < 2)
		{
			for (int i = 0; i < iloscGraczy; i++)
			{
				WyslijPakiet4Bajtowy(i, PSK_SERWER_WYLOCZONY);
			}
			cout << " Nie ma wystarczajaco graczy " << endl;
			cout << "serwer zostaje wylaczony " << endl;
			system("pause");
			exit(0);
			return;
		}
		// jesli gracz mial teraz wykonac ruch 
		if (gracz == ruchGracza)
		{
			ustawNumerNastepnegoGracza();
			WyslijPakiet4Bajtowy(ruchGracza, PSK_TWOJ_RUCH);
		}

	}
}

int main()
{
	cout << "Uruchamian serwer" << endl;

	// inijcuj generator pseudolosowych liczb
	srand(time(0));

	SOCKET server;
	WSADATA wsaData;
	sockaddr_in local;

	// odpal winsocka
	int wsaret = WSAStartup(0x101, &wsaData);

	if (wsaret != 0)
	{
		cout << "Blad winsoacka - WSASTARTUP sie nie powiodlo" << endl;
		system("pause");
		return 0;
	}

	//the socket function creates our SOCKET
	server = socket(AF_INET, SOCK_STREAM, 0);

	//If the socket() function fails we exit
	if (server == INVALID_SOCKET)
	{
		cout << "Blad winsoacka - INVALID_SOCKET" << endl;
		system("pause");
		return 0;
	}

	printf("Rozmiar SGra w bajtach: %i\n", sizeof(SGra));

	// wlacz nie-blockujacy tryb socketa
	unsigned long mode = 1;
	ioctlsocket(server, FIONBIO, &mode);


	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons((u_short)20248);

	if (bind(server, (sockaddr*)&local, sizeof(local)) != 0)
	{
		return 0;
	}

	if (listen(server, 10) != 0)
	{
		return 0;
	}

	InicjujGre();

	// glowna petla programu
	while (1)
	{
		// sprawdz, czy jest jakis nowy klient probujacy podlaczyc sie do serwera
		sockaddr_in nowyKlientAddr;
		int fromlen = sizeof(nowyKlientAddr);
		SOCKET nowyKlient = accept(server,
			(struct sockaddr*)&nowyKlientAddr, &fromlen);
		int error = WSAGetLastError();
		if (error == 0) {
			cout << "Odebralem polaczenie od " << inet_ntoa(nowyKlientAddr.sin_addr) << "\r\n";
			// 
			// wlacz nie-blockujacy tryb socketa
			unsigned long mode = 1;
			ioctlsocket(nowyKlient, FIONBIO, &mode);
			gracze[iloscGraczy].socket = nowyKlient;
			gracze[iloscGraczy].adres = nowyKlientAddr;
			iloscGraczy++;
		}
		else {
			//cout << "Nie ma nowych polaczen " << endl;
		}
		// odbierz pakiety od graczy
		for (int i = 0; i < iloscGraczy; i++)
		{
			char pakiet[512];
			int odebrane = recv(gracze[i].socket, pakiet, sizeof(pakiet), 0);
			error = WSAGetLastError();
			if (error == 0) {
				pakiet[odebrane] = 0;
				ObsluzPakietGracza(i, pakiet, odebrane);
			}
		}
	}


	///    closesocket(client);
	closesocket(server);

	WSACleanup();
	system("PAUSE");

	return 0;
}

