#include "logika.h"

using namespace std;

Logika::Logika(){
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++){
			plansza[i][j] = 0;
			planszaPrzeciwnik[i][j] = 0;
		}

}

Logika::~Logika(){

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
			cout << "ups, coœ ju¿ tu jest! " << plansza[y][x] << " " << temp[y][x] << endl;
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
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 0; j++)
			plansza[i][j] = 0;
	pozycjonowanie(4);
	pokazPlansze();
	pozycjonowanie(3);
	pokazPlansze();
	pozycjonowanie(3);
	pokazPlansze();
	pozycjonowanie(2);
	pokazPlansze();
	pozycjonowanie(2);
	pokazPlansze();
	pozycjonowanie(2);
	pokazPlansze();
	pozycjonowanie(1);
	pokazPlansze();
	pozycjonowanie(1);
	pokazPlansze();
	pozycjonowanie(1);
	pokazPlansze();
	pozycjonowanie(1);
	pokazPlansze();
}

char Logika::oznaczCzyTrafiony(char p, int x, int y){
	if (p =='t'){
		planszaPrzeciwnik[y][x] = 'x';
		cout << "Trafiony!" << endl;
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
		cout << " Zatopiony!" << endl;;
		plansza[y - 1][x - 1] = '0';
		plansza[y + 1][x + 1] = '0';
		plansza[y - 1][x + 1] = '0';
		plansza[y + 1][x - 1] = '0';
		if (plansza[y - 1][x] != 0){
			if (plansza[y - 2][x] != 0){
				if (plansza[y - 3][x] != 0){
					plansza[y - 4][x] = '0';
					plansza[y - 4][x - 1] = '0';
					plansza[y - 4][x + 1] = '0';
					plansza[y - 3][x - 1] = '0';
					plansza[y - 3][x + 1] = '0';
					plansza[y - 2][x - 1] = '0';
					plansza[y - 2][x + 1] = '0';
					plansza[y - 1][x - 1] = '0';
					plansza[y - 1][x + 1] = '0';
					plansza[y][x - 1] = '0';
					plansza[y][x + 1] = '0';
				}
				else{
					plansza[y - 3][x] = '0';
					plansza[y - 3][x - 1] = '0';
					plansza[y - 3][x + 1] = '0';
					plansza[y - 2][x - 1] = '0';
					plansza[y - 2][x + 1] = '0';
					plansza[y - 1][x - 1] = '0';
					plansza[y - 1][x + 1] = '0';
					plansza[y][x - 1] = '0';
					plansza[y][x + 1] = '0';
				}
			}
			else{
				plansza[y - 2][x] = '0';
				plansza[y - 2][x - 1] = '0';
				plansza[y - 2][x + 1] = '0';
				plansza[y - 1][x - 1] = '0';
				plansza[y - 1][x + 1] = '0';
				plansza[y][x - 1] = '0';
				plansza[y][x + 1] = '0';
			}
		}
		else{
			plansza[y - 1][x] = '0';
			plansza[y - 1][x - 1] = '0';
			plansza[y - 1][x + 1] = '0';
			if (plansza[y + 1][x] != 0){
				if (plansza[y + 2][x] != 0){
					if (plansza[y + 3][x] != 0){
						plansza[y + 4][x] = '0';
						plansza[y + 4][x - 1] = '0';
						plansza[y + 4][x + 1] = '0';
						plansza[y + 3][x - 1] = '0';
						plansza[y + 3][x + 1] = '0';
						plansza[y + 2][x - 1] = '0';
						plansza[y + 2][x + 1] = '0';
						plansza[y + 1][x - 1] = '0';
						plansza[y + 1][x + 1] = '0';
						plansza[y][x - 1] = '0';
						plansza[y][x + 1] = '0';
					}
					else{
						plansza[y + 3][x] = '0';
						plansza[y + 3][x - 1] = '0';
						plansza[y + 3][x + 1] = '0';
						plansza[y + 2][x - 1] = '0';
						plansza[y + 2][x + 1] = '0';
						plansza[y + 1][x - 1] = '0';
						plansza[y + 1][x + 1] = '0';
						plansza[y][x - 1] = '0';
						plansza[y][x + 1] = '0';
					}
				}
				else{
					plansza[y + 2][x] = '0';
					plansza[y + 2][x - 1] = '0';
					plansza[y + 2][x + 1] = '0';
					plansza[y + 1][x - 1] = '0';
					plansza[y + 1][x + 1] = '0';
					plansza[y][x - 1] = '0';
					plansza[y][x + 1] = '0';
				}
		
			}
			else{
				plansza[y + 1][x - 1] = '0';
				plansza[y + 1][x + 1] = '0';
				plansza[y + 1][x] = '0';
			}
				if (plansza[y][x + 1] != 0){
					if (plansza[y][x + 2] != 0){
						if (plansza[y][x + 3] != 0){
							plansza[y][x + 4] = '0';
							plansza[y - 1][x + 4] = '0';
							plansza[y + 1][x + 4] = '0';
							plansza[y + 1][x + 3] = '0';
							plansza[y - 1][x + 3] = '0';
							plansza[y + 1][x + 2] = '0';
							plansza[y - 1][x + 2] = '0';
							plansza[y + 1][x + 1] = '0';
							plansza[y - 1][x + 1] = '0';
							plansza[y - 1][x] = '0';
							plansza[y + 1][x] = '0';
						}
						else{
							plansza[y][x + 3] = '0';
							plansza[y + 1][x + 3] = '0';
							plansza[y - 1][x + 3] = '0';
							plansza[y + 1][x + 2] = '0';
							plansza[y - 1][x + 2] = '0';
							plansza[y + 1][x + 1] = '0';
							plansza[y - 1][x + 1] = '0';
							plansza[y + 1][x] = '0';
							plansza[y - 1][x] = '0';
						}
					}
					else{
						plansza[y][x + 2] = '0';
						plansza[y - 1][x + 2] = '0';
						plansza[y + 1][x + 2] = '0';
						plansza[y - 1][x + 1] = '0';
						plansza[y + 1][x + 1] = '0';
						plansza[y - 1][x] = '0';
						plansza[y + 1][x] = '0';
					}

				}
				else{
					plansza[y - 1][x + 1] = '0';
					plansza[y + 1][x + 1] = '0';
					plansza[y][x + 1] = '0';
				}
				if (plansza[y][x - 1] != 0){
					if (plansza[y][x - 2] != 0){
						if (plansza[y][x - 3] != 0){
							plansza[y][x - 4] = '0';
							plansza[y - 1][x - 4] = '0';
							plansza[y + 1][x - 4] = '0';
							plansza[y + 1][x - 3] = '0';
							plansza[y - 1][x - 3] = '0';
							plansza[y + 1][x - 2] = '0';
							plansza[y - 1][x - 2] = '0';
							plansza[y + 1][x - 1] = '0';
							plansza[y - 1][x - 1] = '0';
							plansza[y - 1][x] = '0';
							plansza[y + 1][x] = '0';
						}
						else{
							plansza[y][x - 3] = '0';
							plansza[y + 1][x - 3] = '0';
							plansza[y - 1][x - 3] = '0';
							plansza[y + 1][x - 2] = '0';
							plansza[y - 1][x - 2] = '0';
							plansza[y + 1][x - 1] = '0';
							plansza[y - 1][x - 1] = '0';
							plansza[y + 1][x] = '0';
							plansza[y - 1][x] = '0';
						}
					}
					else{
						plansza[y][x - 2] = '0';
						plansza[y - 1][x - 2] = '0';
						plansza[y + 1][x - 2] = '0';
						plansza[y - 1][x - 1] = '0';
						plansza[y + 1][x - 1] = '0';
						plansza[y - 1][x] = '0';
						plansza[y + 1][x] = '0';
					}
					}
				else{
					plansza[y - 1][x - 1] = '0';
					plansza[y + 1][x - 1] = '0';
					plansza[y][x - 1] = '0';
				}
			}
		}
	pokazPlanszePrzeciwnik();
}

char Logika::czyPrzeciwnikTrafil(int x, int y){
	if (plansza[y][x] != 0){
		plansza[y][x] = 'x';
		cout << "Trafil!" << endl;
		pokazPlansze();
		return 't';
	}
	else{
		plansza[y][x] = 'o';
		cout << "Spudlowal!" << endl;
		pokazPlansze();
		return 'p';
	}
}


char Logika::czyPrzeciwnikZatopil(char p, int x, int y){
	if (p == 't'){

		if (plansza[y - 1][x] == 'x'){
			if (plansza[y - 2][x] == 'x'){
				if (plansza[y - 3][x] == 'x'){
					return 'z';
				}
				else
					if (plansza[y - 3][x] == 0)
						if (plansza[y + 1][x] == 'x' || plansza[y + 1][x] == 0)
							return 'z';
			}
			else
				if (plansza[y - 2][x] == 0)
					if (plansza[y + 1][x] == 'x'
						&& (plansza[y + 2][x] == 'x' || plansza[y + 2][x] == 0)
						|| plansza[y + 1][x] == 0)
						return 'z';
		}
		else{
			if (plansza[y - 1][x] == 0){
				if (plansza[y + 1][x] == 'x' && ((plansza[y + 2][x] == 'x' && (plansza[y + 3][x] == 'x' || plansza[y + 3][x] == 0)
					|| plansza[y + 2][x] == 0))
					|| plansza[y + 1][x] == 0){
					if (plansza[y][x - 1] == 'x'){
						if (plansza[y][x - 2] == 'x'){
							if (plansza[y][x - 3] == 'x'){
								return 'z';
							}
							else
								if (plansza[y][x - 3] == 0)
									if (plansza[y][x + 1] == 'x' || plansza[y][x + 1] == 0)
										return 'z';
						}
						else
							if (plansza[y][x - 2] == 0)
								if (plansza[y][x + 1] == 'x'
									&& (plansza[y][x + 2] == 'x' || plansza[y][x + 2] == 0)
									|| plansza[y][x + 1] == 0)
									return 'z';
					}
					else{
						if (plansza[y][x - 1] == 0)
							if (plansza[y][x + 1] == 'x' && ((plansza[y][x + 2] == 'x' && (plansza[y][x + 3] == 'x' || plansza[y][x + 3] == 0)
								|| plansza[y][x + 2] == 0))
								|| plansza[y][x + 1] == 0)
								return 'z';
					}
				}
			}
		}
		return 'n';
	}
}
