#include "logika.h"

using namespace std;

Logika::Logika(){
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++){
			plansza[i][j] = 0;
			planszaPrzeciwnik[i][j] = 0;
		}

}

Logika::Logika(){

}

void Logika::pokazPlansze(){
	for (int i = 0; i < 10; i++){
		cout << "|";
		for (int j = 0; j < 10; j++)
			cout << plansza[i][j];
		cout << "|" << endl;
	}
}

void Logika::pokazPlanszePrzeciwnik(){
	for (int i = 0; i < 10; i++){
		cout << "|";
		for (int j = 0; j < 10; j++)
			cout << planszaPrzeciwnik[i][j];
		cout << "|" << endl;
	}
}

void Logika::pozycjonowanie(int ktoryStatek){
	int x, y;
	char temp[10][10];
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 0; j++)
			temp[i][j] = 0;
	for (int i = 0; i < ktoryStatek; i++){
		cin >> x;
		while (x<1 || x>10){
			cout << "wspó³rzêdne nie mieszcz¹ siê w tablicy";
			cin >> x;
		}


		cin >> y;
		while (y<1 || y>10){
			cout << "wspó³rzêdne nie mieszcz¹ siê w tablicy";
			cin >> y;
		}
		x--;
		y--;
		if (plansza[y][x] != 0 || temp[y][x] != 0){
			cout << "ups, coœ ju¿ tu jest!";
			i--;
		}
		else{
			if (plansza[y - 1][x - 1] != 0 && x > 0 && y > 0
				|| plansza[y - 1][x] != 0 && y > 0
				|| plansza[y + 1][x] != 0 && y < 9
				|| plansza[y + 1][x + 1] != 0 && y < 9 && x < 9
				|| plansza[y - 1][x + 1] != 0 && y > 0 && x < 9
				|| plansza[y][x + 1] && x < 9
				|| plansza[y][x - 1] && x > 0
				|| plansza[y + 1][x - 1] != 0 && y < 9 && x > 0){
				cout << "nie mog¹ siê stykaæ";
				i--;
			}
			else
				if (temp[y - 1][x] != ktoryStatek 
					&& temp[y + 1][x] != ktoryStatek
					&& temp[y][x + 1] != ktoryStatek
					&& temp[y][x - 1] != ktoryStatek){
					cout << "ej¿e, urwisie, tworzysz w³aœnie " << ktoryStatek << "-masztowiec, jeszcze go nie skoñczy³eœ!" << endl;
					i--;
				}
				else
					temp[y][x] = ktoryStatek;
		}
	}
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 0; j++)
			if (temp[i][j] != 0)
				plansza[i][j] = temp[i][j];
}

void Logika::ustawStatki(){
	
	cout << "witaj w grze STATKI v 0.1" << endl << "ustaw statki, od najwiêkszego do najmniejszego"
		<< endl << "podaj wspó³rzêdne 4-masztowca, ka¿d¹ zatwierdzaj ENTER, x,y 4 razy" << endl;

	pozycjonowanie(4);
	pozycjonowanie(3);
	pozycjonowanie(3);
	pozycjonowanie(2);
	pozycjonowanie(2);
	pozycjonowanie(2);
	pozycjonowanie(1);
	pozycjonowanie(1);
	pozycjonowanie(1);
	pozycjonowanie(1);
	pokazPlansze();
}

char Logika::oznaczCzyTrafiony(char p, int x, int y){
	if (p =='t'){
		planszaPrzeciwnik[y][x] = 'x';
		cout << "Trafiony!";
		return 't';
	}
	else{
		planszaPrzeciwnik[y][x] = '0';
		cout << "Pudlo!" << endl << endl;
		return 'p';
	}
}

void Logika::oznaczCzyZatopiony(char p, int x, int y){
	if (p == 'z')
	{
		plansza[y - 1][x - 1] = '0';
		plansza[y + 1][x + 1] = '0';
		plansza[y - 1][x + 1] = '0';
		if (plansza[y - 1][x] != 0){
			if (plansza[y - 2][x] != 0){
				if (plansza[y - 3][x] != 0){
					plansza[y - 4][x] = '0';
					plansza[y - 4][x - 1] = '0';
					plansza[y - 4][x +1 ] = '0';
				}
			}
			else{
			
			
			}

		}
			plansza[y + 1][x] != 0 && y < 9
		
		plansza[y][x + 1] && x < 9
			plansza[y][x - 1] && x > 0
		plansza[y + 1][x - 1] = '0';
	}

}
char Logika::czyPrzeciwnikTrafil(int x, int y){
	return 't';
}
	else{

		return 'p';
	}
}
char Logika::czyPrzeciwnikZatopil(int x, int y){
	return 't';
}
	else{

		return 'p';
	}
}