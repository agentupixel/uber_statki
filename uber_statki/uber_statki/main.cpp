#include "wspolny_naglowek.h"
#include"siec.h"

int main(void){
	Logika *logika = new Logika();
	logika->ustawStatki();
	Siec *siec = new Siec();
	siec->connection();
	system("pause");

	return 0;



}