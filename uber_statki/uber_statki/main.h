#define _WINSOCKAPI_
#include "siec.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctime>
#include "glm/glm.hpp"
#include <string>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "targa.h"
#include "objloader.hpp"
#define MINISZER 58
#define MINIWYS 28
#define MINIX 0
#define MINIY 570
#define ODSX 58+5
#define ODSY 25
#define GR2 900

// tratwa
std::vector<glm::vec3> vertices;
std::vector<glm::vec2> uvs;
std::vector<glm::vec3> normals;

// lodka
std::vector<glm::vec3> vertices2;
std::vector<glm::vec2> uvs2;
std::vector<glm::vec3> normals2;

// hybryda
std::vector<glm::vec3> vertices3;
std::vector<glm::vec2> uvs3;
std::vector<glm::vec3> normals3;

// statek
std::vector<glm::vec3> vertices4;
std::vector<glm::vec2> uvs4;
std::vector<glm::vec3> normals4;

enum
{
	JEDNOMASZTOWCE,
	DWUMASZTOWCE,
	TRZYMASZTOWCE,
	CZTEROMASZTOWCE,
	POZIOMO,
	PIONOWO,
	ZEROWANIE,
	START
};
bool res, res2, res3, res4;
Siec *siec = new Siec();
bool czyStrzal = false, ustawianie = false;
int kto;
float xpos = 220, ypos = 230, zpos = 290, xrot = 48, yrot = 0, angle = 0.0;
GLuint tekstura[10];
clock_t start, finish;
double czas;
int w = 1000;
int h = 600;
/////
int xstatek = 10;//do statkow
int zstatek = 10;
int tex[11] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
int texprzeciwnika[11] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
int tex2 = 2, tex3 = 3;
int xgreen = 0;//pozycja zielonego kwadratu
int zgreen = 0;

int skok = 20;//odleglosc miedzy statkami
int granica1 = 200;//rozmiar pola gry

int indexi = 0;//index aktualnej pozycji(zalezy od xgreen)
int indexj = 0;
int trafiony = 0;//1-pudlo, 2-trafiony, 3-trafiony zatopiony

/////
int ktoStrzela = 0;//0-ja strzelam, 1-on strzela
int liczbaMasztow = 4;//liczba masztow ustawianego statku
int poziom = 1;//czy statki stawiane poziomo czy pionowo
int koniecUstawiania = 0;//dla wartosci 1 ustawianie zakonczone
float positionz[10];
float positionx[10];
int mojalista;
GLuint tex_sciany[2];
GLuint tex_podloga[2];
int mojeStatki[10][10] =
{
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },//0-statek nieustawiony, 1-ustawiony 1masztowiec
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },//2-ustawiony 2 masztowiec, dla 3 i 4 analogicznie
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },//-1 to pudlo przeciwnika, 11- trafiony 1masztowiec
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },//12-trafiony 2masztowiec, dla 13 i 14 analogicznie i 22,23,24,25
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

int statkiPrzeciwnika[10][10] =
{
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },//tablica nie bedzie uzywana dla gry sieciowej miedzy 2 graczami(chyba :P )?????
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
int odkrytePrzeciwnika[10][10] =
{
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },//0-jeszcze tu nie strzelilem  -1: spudlowalem
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },//1, 2, 3, 4 trafilem w 1, 2, 3 albo 4masztowiec????????????????
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
int maszty[4] = { 4, 3, 2, 1 };
int masztyPrzeciwnika[4] = { 4, 3, 2, 1 };
int rodzajStatku = 0;
int zajete[10][10] =
{
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },//0- moge tu postawic statek
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },//1- nie moge tu postawic statku bo obok jest statek
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },//5- nie moge tu postawic statku bo tu juz jest statek
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

// oświetlenie
GLfloat amb[] = { 0.3, 0.3, 0.3, 1.0 };
GLfloat dif[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat kol[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat pos[] = { 90.0, 10, 95, 0.0 };

//Pozycje szeœcianów


void rysujStatekTex(int pozx, int pozy, int tex);
void okrazanieZatopionych(int x, int y, int rodzaj);
int strzalPrzeciwnika();
void enable(void);
bool sprawdzStatek(int wiersz, int kolumna, int amaszty, int apoziom);
void ustawStatek(int wiersz, int kolumna, int amaszty, int apoziom);
void ustawStatekPrzeciwnika(int wiersz, int kolumna, int amaszty, int apoziom);
void camera(void);
void pokazStatki();
void strzalki();
void zerujStatki();
void zerujZajete();
void grid();
void display(void);
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void MouseMotion(int x, int y);
void SpecialKeys(int key, int x, int y);
void Menu(int value);
void oznaczStatekPrzeciwnika();
void okrazanieZatopionychPrzeciwnika(int x, int y);
void oznaczTrafieniePrzeciwnika(int x, int y);
void ustawStatki();
void wyswietlModel(GLuint teksturka, GLdouble skala, GLfloat transX, GLfloat transY, GLfloat transZ, GLfloat rotAngle, GLfloat rotX, GLfloat rotY, GLfloat rotZ, std::vector<glm::vec3> vertices111, std::vector<glm::vec2> uvs111, std::vector<glm::vec3> normals111);

