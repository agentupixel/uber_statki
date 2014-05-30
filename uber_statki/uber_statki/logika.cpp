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
	int temp[10][10];
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
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
			{
				if (temp[y - 1][x] != ktoryStatek
					&& temp[y + 1][x] != ktoryStatek
					&& temp[y][x + 1] != ktoryStatek
					&& temp[y][x - 1] != ktoryStatek){
					if (i != 0){
						cout << "ej¿e, urwisie, tworzysz w³aœnie " << ktoryStatek << "-masztowiec, jeszcze go nie skoñczy³eœ!" << endl;
						i--;
					}
				}
				else{
					temp[y][x] = ktoryStatek;
					cout << "ustawione na " << y << " " << x;
				}
			}
		}
		temp[y][x] = ktoryStatek;
		cout << "ustawione na " << y << " " << x << endl;
	}
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++){
			if (plansza[i][j] == 0){
				plansza[i][j] = temp[i][j];
			}
		}
	for (int i = 0; i < 10; i++){
		cout << "|";
		for (int j = 0; j < 10; j++)
			cout << temp[i][j];
		cout << "|" << endl ;
	}
	cout << endl;
}

void Logika::ustawStatki(){
	
	cout << "witaj w grze STATKI v 0.1" << endl << "ustaw statki, od najwiêkszego do najmniejszego"
		<< endl << "podaj wspó³rzêdne 4-masztowca, ka¿d¹ zatwierdzaj ENTER, x,y 4 razy" << endl;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++){
			plansza[i][j] = 0;
			planszaPrzeciwnik[i][j] = 0;
		}
	//pozycjonowanie(1);
//	pokazPlansze();
	/*pozycjonowanie(4);
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
	pokazPlansze();*/
	plansza[0][0] = 4;
	plansza[0][1] = 4;
	plansza[0][2] = 4;
	plansza[0][3] = 4;
	plansza[2][0] = 3;
	plansza[2][1] = 3;
	plansza[2][2] = 3;
	plansza[2][4] = 3;
	plansza[2][5] = 3;
	plansza[2][6] = 3;
	plansza[2][8] = 2;
	plansza[2][9] = 2;
	plansza[0][6] = 2;
	plansza[0][7] = 2;
	plansza[4][0] = 2;
	plansza[4][1] = 2;
	plansza[6][1] = 1;
	plansza[8][1] = 1;
	plansza[8][3] = 1;
	plansza[9][5] = 1;
	pokazPlansze();
}

char Logika::oznaczCzyTrafiony(char p, int x, int y){
	if (p =='t'){
		planszaPrzeciwnik[y][x] = 9;
		cout << "Trafiony!" << endl;
		return 't';
	}
	else{
		planszaPrzeciwnik[y][x] = 0;
		cout << "Pudlo!" << endl << endl;
		return 'p';
	}
}

void Logika::oznaczCzyZatopiony(char p, int x, int y){
	if (p == 'z')
	{
		cout << " Zatopiony!" << endl;;
		plansza[y - 1][x - 1] = 0;
		plansza[y + 1][x + 1] = 0;
		plansza[y - 1][x + 1] = 0;
		plansza[y + 1][x - 1] = 0;
		if (plansza[y - 1][x] != 0){
			if (plansza[y - 2][x] != 0){
				if (plansza[y - 3][x] != 0){
					plansza[y - 4][x] = 0;
					plansza[y - 4][x - 1] = 0;
					plansza[y - 4][x + 1] = 0;
					plansza[y - 3][x - 1] = 0;
					plansza[y - 3][x + 1] = 0;
					plansza[y - 2][x - 1] = 0;
					plansza[y - 2][x + 1] = 0;
					plansza[y - 1][x - 1] = 0;
					plansza[y - 1][x + 1] = 0;
					plansza[y][x - 1] = 0;
					plansza[y][x + 1] = 0;
				}
				else{
					plansza[y - 3][x] = 0;
					plansza[y - 3][x - 1] = 0;
					plansza[y - 3][x + 1] = 0;
					plansza[y - 2][x - 1] = 0;
					plansza[y - 2][x + 1] = 0;
					plansza[y - 1][x - 1] = 0;
					plansza[y - 1][x + 1] = 0;
					plansza[y][x - 1] = 0;
					plansza[y][x + 1] = 0;
				}
			}
			else{
				plansza[y - 2][x] = 0;
				plansza[y - 2][x - 1] = 0;
				plansza[y - 2][x + 1] = 0;
				plansza[y - 1][x - 1] = 0;
				plansza[y - 1][x + 1] = 0;
				plansza[y][x - 1] = 0;
				plansza[y][x + 1] = 0;
			}
		}
		else{
			plansza[y - 1][x] = 0;
			plansza[y - 1][x - 1] = 0;
			plansza[y - 1][x + 1] = 0;
			if (plansza[y + 1][x] != 0){
				if (plansza[y + 2][x] != 0){
					if (plansza[y + 3][x] != 0){
						plansza[y + 4][x] = 0;
						plansza[y + 4][x - 1] = 0;
						plansza[y + 4][x + 1] = 0;
						plansza[y + 3][x - 1] = 0;
						plansza[y + 3][x + 1] = 0;
						plansza[y + 2][x - 1] = 0;
						plansza[y + 2][x + 1] = 0;
						plansza[y + 1][x - 1] = 0;
						plansza[y + 1][x + 1] = 0;
						plansza[y][x - 1] = 0;
						plansza[y][x + 1] = 0;
					}
					else{
						plansza[y + 3][x] = 0;
						plansza[y + 3][x - 1] = 0;
						plansza[y + 3][x + 1] = 0;
						plansza[y + 2][x - 1] = 0;
						plansza[y + 2][x + 1] = 0;
						plansza[y + 1][x - 1] = 0;
						plansza[y + 1][x + 1] = 0;
						plansza[y][x - 1] = 0;
						plansza[y][x + 1] = 0;
					}
				}
				else{
					plansza[y + 2][x] = 0;
					plansza[y + 2][x - 1] = 0;
					plansza[y + 2][x + 1] = 0;
					plansza[y + 1][x - 1] = 0;
					plansza[y + 1][x + 1] = 0;
					plansza[y][x - 1] = 0;
					plansza[y][x + 1] = 0;
				}
		
			}
			else{
				plansza[y + 1][x - 1] = 0;
				plansza[y + 1][x + 1] = 0;
				plansza[y + 1][x] = 0;
			}
				if (plansza[y][x + 1] != 0){
					if (plansza[y][x + 2] != 0){
						if (plansza[y][x + 3] != 0){
							plansza[y][x + 4] = 0;
							plansza[y - 1][x + 4] = 0;
							plansza[y + 1][x + 4] = 0;
							plansza[y + 1][x + 3] = 0;
							plansza[y - 1][x + 3] = 0;
							plansza[y + 1][x + 2] = 0;
							plansza[y - 1][x + 2] = 0;
							plansza[y + 1][x + 1] = 0;
							plansza[y - 1][x + 1] = 0;
							plansza[y - 1][x] = 0;
							plansza[y + 1][x] = 0;
						}
						else{
							plansza[y][x + 3] = 0;
							plansza[y + 1][x + 3] = 0;
							plansza[y - 1][x + 3] = 0;
							plansza[y + 1][x + 2] = 0;
							plansza[y - 1][x + 2] = 0;
							plansza[y + 1][x + 1] = 0;
							plansza[y - 1][x + 1] = 0;
							plansza[y + 1][x] = 0;
							plansza[y - 1][x] = 0;
						}
					}
					else{
						plansza[y][x + 2] = 0;
						plansza[y - 1][x + 2] = 0;
						plansza[y + 1][x + 2] = 0;
						plansza[y - 1][x + 1] = 0;
						plansza[y + 1][x + 1] = 0;
						plansza[y - 1][x] = 0;
						plansza[y + 1][x] = 0;
					}

				}
				else{
					plansza[y - 1][x + 1] = 0;
					plansza[y + 1][x + 1] = 0;
					plansza[y][x + 1] = 0;
				}
				if (plansza[y][x - 1] != 0){
					if (plansza[y][x - 2] != 0){
						if (plansza[y][x - 3] != 0){
							plansza[y][x - 4] = 0;
							plansza[y - 1][x - 4] = 0;
							plansza[y + 1][x - 4] = 0;
							plansza[y + 1][x - 3] = 0;
							plansza[y - 1][x - 3] = 0;
							plansza[y + 1][x - 2] = 0;
							plansza[y - 1][x - 2] = 0;
							plansza[y + 1][x - 1] = 0;
							plansza[y - 1][x - 1] = 0;
							plansza[y - 1][x] = 0;
							plansza[y + 1][x] = 0;
						}
						else{
							plansza[y][x - 3] = 0;
							plansza[y + 1][x - 3] = 0;
							plansza[y - 1][x - 3] = 0;
							plansza[y + 1][x - 2] = 0;
							plansza[y - 1][x - 2] = 0;
							plansza[y + 1][x - 1] = 0;
							plansza[y - 1][x - 1] = 0;
							plansza[y + 1][x] = 0;
							plansza[y - 1][x] = 0;
						}
					}
					else{
						plansza[y][x - 2] = 0;
						plansza[y - 1][x - 2] = 0;
						plansza[y + 1][x - 2] = 0;
						plansza[y - 1][x - 1] = 0;
						plansza[y + 1][x - 1] = 0;
						plansza[y - 1][x] = 0;
						plansza[y + 1][x] = 0;
					}
					}
				else{
					plansza[y - 1][x - 1] = 0;
					plansza[y + 1][x - 1] = 0;
					plansza[y][x - 1] = 0;
				}
			}
		}
	pokazPlanszePrzeciwnik();
}

char Logika::czyPrzeciwnikTrafil(int x, int y){
	if (plansza[y][x] != 0){
		plansza[y][x] = 9;
		cout << "Trafil!" << endl;
		pokazPlansze();
		return 't';
	}
	else{
		plansza[y][x] = 7;
		cout << "Spudlowal!" << endl;
		pokazPlansze();
		return 'p';
	}
}


char Logika::czyPrzeciwnikZatopil(char p, int x, int y){
	if (p == 't'){

		if (plansza[y - 1][x] == 9){
			if (plansza[y - 2][x] == 9){
				if (plansza[y - 3][x] == 9){
					return 'z';
				}
				else
					if (plansza[y - 3][x] == 0)
						if (plansza[y + 1][x] == 9 || plansza[y + 1][x] == 0)
							return 'z';
			}
			else
				if (plansza[y - 2][x] == 0)
					if (plansza[y + 1][x] == 9
						&& (plansza[y + 2][x] == 9 || plansza[y + 2][x] == 0)
						|| plansza[y + 1][x] == 0)
						return 'z';
		}
		else{
			if (plansza[y - 1][x] == 0){
				if (plansza[y + 1][x] == 9 && ((plansza[y + 2][x] == 9 && (plansza[y + 3][x] == 9 || plansza[y + 3][x] == 0)
					|| plansza[y + 2][x] == 0))
					|| plansza[y + 1][x] == 0){
					if (plansza[y][x - 1] == 9){
						if (plansza[y][x - 2] == 9){
							if (plansza[y][x - 3] == 9){
								return 'z';
							}
							else
								if (plansza[y][x - 3] == 0)
									if (plansza[y][x + 1] == 9 || plansza[y][x + 1] == 0)
										return 'z';
						}
						else
							if (plansza[y][x - 2] == 0)
								if (plansza[y][x + 1] == 9
									&& (plansza[y][x + 2] == 9 || plansza[y][x + 2] == 0)
									|| plansza[y][x + 1] == 0)
									return 'z';
					}
					else{
						if (plansza[y][x - 1] == 0)
							if (plansza[y][x + 1] == 9 && ((plansza[y][x + 2] == 9 && (plansza[y][x + 3] == 9 || plansza[y][x + 3] == 0)
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

void Logika::czyPrzegral(){
	char temp;
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			if (plansza[i][j] == 0 || plansza[i][j] == 9)
				temp = 'a';
		}
	}
}