#ifndef LOGIKA_H
#define LOGIKA_H
#include "wspolny_naglowek.h"


class Logika{
public:
	Logika();
	~Logika();
	void ustawStatki();
	char oznaczCzyTrafiony(char p, int x, int y);
	void oznaczCzyZatopiony(char p, int x, int y);
	char czyPrzeciwnikTrafil(int x, int y);
	char czyPrzeciwnikZatopil(int x, int y);
private:
	char plansza[10][10];
	char planszaPrzeciwnik[10][10];
	void pozycjonowanie(int ktoryStatek);
	void pokazPlansze();
	void pokazPlanszePrzeciwnik();


};




#endif