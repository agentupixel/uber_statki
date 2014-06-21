#define _CRT_SECURE_NO_DEPRECATE
#include "main.h"
bool loadOBJ(const char * path, std::vector<glm::vec3> & out_vertices, std::vector<glm::vec2> & out_uvs, std::vector<glm::vec3> & out_normals)
{
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;



	FILE * file = fopen(path, "r");
	if (file == NULL)
	{
		printf("Nie można otworzyc pliku ! \n");
		getchar();
		return false;
	}

	while (1)
	{

		char lineHeader[128];

		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break;

		if (strcmp(lineHeader, "v") == 0)
		{
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y;
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			//printf("%d\n",matches);
			if (matches != 9)
			{
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else
		{
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}


	for (unsigned int i = 0; i<vertexIndices.size(); i++)
	{


		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];


		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		glm::vec3 normal = temp_normals[normalIndex - 1];


		out_vertices.push_back(vertex);
		out_uvs.push_back(uv);
		out_normals.push_back(normal);
	}
	return true;
}
void wyswietlModel(GLuint teksturka, GLdouble skala, GLfloat transX, GLfloat transY, GLfloat transZ, GLfloat rotAngle, GLfloat rotX, GLfloat rotY, GLfloat rotZ, std::vector<glm::vec3> vertices111, std::vector<glm::vec2> uvs111, std::vector<glm::vec3> normals111)
{
	glPushMatrix();
	glColor4f(0.5, 0.5, 0.5, 0.5);
	glDisable(GL_TEXTURE_1D);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, teksturka);
	glScaled(skala, skala, skala);
	glTranslatef(transX, transY, transZ);
	glRotatef(rotAngle, rotX, rotY, rotZ);
	glBegin(GL_TRIANGLES);
	for (unsigned int i = 0; i < vertices111.size(); i++)
	{
		glNormal3f(normals111[i].x, normals111[i].y, normals111[i].z);
		glTexCoord2f(uvs111[i].x, -(uvs111[i].y));
		glVertex3f(vertices111[i].x, vertices111[i].y, vertices111[i].z);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}
void rysujStatekTex(int pozx, int pozy, int tex)
{
	glBindTexture(GL_TEXTURE_2D, tekstura[tex]);
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(pozx, pozy, 0.04);
	glTexCoord2f(0, 1);
	glVertex3f(pozx, pozy + MINIWYS, 0.04);
	glTexCoord2f(1, 1);
	glVertex3f(pozx + MINISZER, pozy + MINIWYS, 0.04);
	glTexCoord2f(1, 0);
	glVertex3f(pozx + MINISZER, pozy, 0.04);
	glEnd();
	glPopMatrix();
}

void okrazanieZatopionychPrzeciwnika(int x, int y)
{
	odkrytePrzeciwnika[x][y] += 10;

	for (int i = 0; i<3; i++)
	{
		for (int j = 0; j<3; j++)
		{
			if ((odkrytePrzeciwnika[x - 1 + i][y - 1 + j] == 1) && ((x - 1 + i) >= 0) && ((x - 1 + i) <= 9) && ((y - 1 + j) >= 0) && ((y - 1 + j) <= 9))
			{
				rodzajStatku++;
				okrazanieZatopionychPrzeciwnika(x - 1 + i, y - 1 + j);
			}
			else if ((odkrytePrzeciwnika[x - 1 + i][y - 1 + j] == 0) && ((x - 1 + i) >= 0) && ((x - 1 + i) <= 9) && ((y - 1 + j) >= 0) && ((y - 1 + j) <= 9))
				odkrytePrzeciwnika[x - 1 + i][y - 1 + j] = -1;
		}
	}
}

void okrazanieZatopionych(int x, int y, int rodzaj)
{
	mojeStatki[x][y] = rodzaj + 10;

	for (int i = 0; i<3; i++)
	{
		for (int j = 0; j<3; j++)
		{
			if ((mojeStatki[x - 1 + i][y - 1 + j] == rodzaj) && ((x - 1 + i) >= 0) && ((x - 1 + i) <= 9) && ((y - 1 + j) >= 0) && ((y - 1 + j) <= 9))
				okrazanieZatopionych(x - 1 + i, y - 1 + j, rodzaj);
			else if ((mojeStatki[x - 1 + i][y - 1 + j] == 0) && ((x - 1 + i) >= 0) && ((x - 1 + i) <= 9) && ((y - 1 + j) >= 0) && ((y - 1 + j) <= 9))
				mojeStatki[x - 1 + i][y - 1 + j] = -1;
		}
	}
}

int strzalPrzeciwnika()
{
	int x = rand() % 10;
	return x;
}

void enable(void)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, kol);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_SPECULAR, kol);




}

bool sprawdzCzyKoniec(){
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (mojeStatki[i][j] == 1 || mojeStatki[i][j] == 2 || mojeStatki[i][j] == 3 || mojeStatki[i][j] == 4)
				return false;
	return true;
}

bool sprawdzStatek(int wiersz, int kolumna, int amaszty, int apoziom)
{
	if (apoziom == 0)
	{
		if (kolumna + amaszty<11)
		{
			for (int i = 0; i<amaszty; i++)
			{
				if (zajete[wiersz][kolumna + i]>0)
				{
					return false;
				}
			}
		}
		else
			return false;
	}
	else if (apoziom == 1)
	{
		if (wiersz + amaszty<11)
		{
			for (int i = 0; i<amaszty; i++)
			{
				if (zajete[wiersz + i][kolumna]>0)
				{
					return false;
				}
			}
		}
		else
			return false;
	}
	return true;

}

void ustawStatek(int wiersz, int kolumna, int amaszty, int apoziom)
{
	int wier2;
	int kol2;
	if (apoziom == 0)
	{
		for (int k = 0; k<amaszty; k++)
		{
			kol2 = kolumna + k;

			if (amaszty == 1)
			{
				mojeStatki[wiersz][kol2] = 1;
				zajete[wiersz][kol2] = 5;
			}
			else if (amaszty == 2)
			{
				mojeStatki[wiersz][kol2] = 2;
				zajete[wiersz][kol2] = 5;
			}
			else if (amaszty == 3)
			{
				mojeStatki[wiersz][kol2] = 3;
				zajete[wiersz][kol2] = 5;
			}
			else if (amaszty == 4)
			{
				mojeStatki[wiersz][kol2] = 4;
				zajete[wiersz][kol2] = 5;
			}


			for (int i = wiersz - 1; i < wiersz + 2; i++)
			{
				for (int j = kol2 - 1; j < kol2 + 2; j++)
				{
					if (i >= 0 && i <= 9 && j >= 0 && j <= 9)
					{
						if (zajete[i][j] != 5)
							zajete[i][j] = 1;
					}
				}
			}
		}
	}
	else
		for (int k = 0; k<amaszty; k++)
		{
			wier2 = wiersz + k;

			if (amaszty == 1)
			{
				mojeStatki[wier2][kolumna] = 1;
				zajete[wier2][kolumna] = 5;
			}
			else if (amaszty == 2)
			{
				mojeStatki[wier2][kolumna] = 2;
				zajete[wier2][kolumna] = 5;
			}
			else if (amaszty == 3)
			{
				mojeStatki[wier2][kolumna] = 3;
				zajete[wier2][kolumna] = 5;
			}
			else if (amaszty == 4)
			{
				mojeStatki[wier2][kolumna] = 4;
				zajete[wier2][kolumna] = 5;
			}


			for (int i = wier2 - 1; i < wier2 + 2; i++)
			{
				for (int j = kolumna - 1; j < kolumna + 2; j++)
				{
					if (i >= 0 && i <= 9 && j >= 0 && j <= 9)
					{
						if (zajete[i][j] != 5)
							zajete[i][j] = 1;
					}
				}
			}
		}
}

void camera(void)
{
	glRotatef(xrot, 1.0, 0.0, 0.0);
	glRotatef(yrot, 0.0, 1.0, 0.0);
	glTranslated(-xpos, -ypos, -zpos);
}
void pokazStatki()
{
	glTranslatef(xstatek, 5, zstatek);
	glPushMatrix();
	//moje -1 :pudlo przeciwnika -2: przecwnik trafil

	// glTranslatef(xstatek,5,zstatek);
	//glutSolidSphere(8,10,10);
	for (int i = 0; i<10; i++)
	{
		for (int j = 0; j<10; j++)
		{
			if (zajete[i][j] == 1)
			{
				glColor3f(0.1, 0.1, 0.1);//USTAWIENIE JEDNOMASZTOWCA
				glutSolidSphere(4, 15, 15);


			}
			//
			//USTAWIENIE DWUMASZTOWCA PIONOWO
			if (((mojeStatki[i][j] == 2) | (mojeStatki[i][j] == 12) | (mojeStatki[i][j] == 22)) &&
				((mojeStatki[i][j + 1] == 2) | (mojeStatki[i][j + 1] == 12) | (mojeStatki[i][j + 1] == 22)))
			{
				wyswietlModel(tekstura[8], 5.5, 2.0f, 0.0f, -4.5f, 90, 0, 1, 0, vertices2, uvs2, normals2);

			}//USTAWIENIE 2MASZTOWCA POZIOMO
			else if (((mojeStatki[i][j] == 2) | (mojeStatki[i][j] == 12) | (mojeStatki[i][j] == 22)) &&
				((mojeStatki[i + 1][j] == 2) | (mojeStatki[i + 1][j] == 12) | (mojeStatki[i + 1][j] == 22)))
			{

				wyswietlModel(tekstura[8], 4, 5.5f, 1.0f, 3.5f, 0, 0, 1, 0, vertices2, uvs2, normals2);
			}
			//USTAWIENIE 3MASZTOWCA PIONOWO
			else if (((mojeStatki[i][j] == 3) | (mojeStatki[i][j] == 13) | (mojeStatki[i][j] == 23)) &&
				((mojeStatki[i][j + 1] == 3) | (mojeStatki[i][j + 1] == 13) | (mojeStatki[i][j + 1] == 23)) &&
				((mojeStatki[i][j + 2] == 3) | (mojeStatki[i][j + 2] == 13) | (mojeStatki[i][j + 2] == 23)))

			{
				wyswietlModel(tekstura[7], 1, 15.5f, 0.0f, 0.5f, 90, 0, 90, 0, vertices3, uvs3, normals3);
			}

			//USTAWIENIE 3MASZTOWCA POZIOMO
			else if (((mojeStatki[i][j] == 3) | (mojeStatki[i][j] == 13) | (mojeStatki[i][j] == 23)) &&
				((mojeStatki[i + 1][j] == 3) | (mojeStatki[i + 1][j] == 13) | (mojeStatki[i + 1][j] == 23)) &&
				((mojeStatki[i + 2][j] == 3) | (mojeStatki[i + 2][j] == 13) | (mojeStatki[i + 2][j] == 23)))
			{
				wyswietlModel(tekstura[7], 1, 0.5f, 0.0f, 20.5f, 0, 0, 1, 0, vertices3, uvs3, normals3);
			}
			//USTAWIENIE 4MASZTOWCA PIONOWO
			else if (((mojeStatki[i][j] == 4) | (mojeStatki[i][j] == 14) | (mojeStatki[i][j] == 24)) &&
				((mojeStatki[i][j + 1] == 4) | (mojeStatki[i][j + 1] == 14) | (mojeStatki[i][j + 1] == 24)) &&
				((mojeStatki[i][j + 2] == 4) | (mojeStatki[i][j + 2] == 14) | (mojeStatki[i][j + 2] == 24)) &&
				((mojeStatki[i][j + 3] == 4) | (mojeStatki[i][j + 3] == 14) | (mojeStatki[i][j + 3] == 24)))
			{
				wyswietlModel(tekstura[9], 2.5, 13.5f, 0.0f, 7.5f, 0, 0, 1, 0, vertices4, uvs4, normals4);
			}//USTAWIENIE 4MASZTOWCA POZIOMO
			else if (((mojeStatki[i][j] == 4) | (mojeStatki[i][j] == 14) | (mojeStatki[i][j] == 24)) &&
				((mojeStatki[i + 1][j] == 4) | (mojeStatki[i + 1][j] == 14) | (mojeStatki[i + 1][j] == 24)) &&
				((mojeStatki[i + 2][j] == 4) | (mojeStatki[i + 2][j] == 14) | (mojeStatki[i + 2][j] == 24)) &&
				((mojeStatki[i + 3][j] == 4) | (mojeStatki[i + 3][j] == 14) | (mojeStatki[i + 3][j] == 24)))
			{


				glColor3f(0, 1, 1);
				glDisable(GL_TEXTURE_1D);
				glEnable(GL_TEXTURE_2D);
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
				glBindTexture(GL_TEXTURE_2D, tekstura[9]);

				glPushMatrix();
				glColor3f(1.0, 0.0, 0.0);
				glScaled(2.6, 2.6, 2.6);

				glTranslatef(0.5f, 10.0f, 0.5f);
				glRotatef(90, 0, 1, 0);

				glPushMatrix();
				glTranslatef(-12.0, -15.0, 4.0);
				glBegin(GL_TRIANGLES);
				for (unsigned int i = 0; i < vertices4.size(); i++)
				{
					glNormal3f(normals4[i].x, normals4[i].y, normals4[i].z);
					glTexCoord2f(uvs4[i].x, -(uvs4[i].y));
					glVertex3f(vertices4[i].x, vertices4[i].y, vertices4[i].z);
				}
				glEnd();
				glPopMatrix();
				glDisable(GL_TEXTURE_2D);
				glPopMatrix();

			}

			switch (mojeStatki[i][j])
			{
			case 1:
				wyswietlModel(tekstura[6], 4.8, 0.5f, 0.0f, 0.5f, 90, 0, 1, 0, vertices, uvs, normals);
				break;
			case -1:
				glColor3f(0.1, 0.1, 0.1);
				glutSolidCube(13);
				break;
			case 11:
			case 21:
				glColor3f(0, 1, 0);
				glutSolidCube(13);
				break;
			case 12:
			case 22:
				glColor3f(0, 0, 1);
				glutSolidCube(13);
				break;
			case 13:
			case 23:
				glColor3f(0, 1, 1);
				glutSolidCube(13);
				break;
			case 14:
			case 24:
				glColor3f(1, 1, 0);
				glutSolidCube(13);
				break;
			}


			glTranslatef(skok, 0, 0);
		}
		glTranslatef(-10 * skok, 0, skok);
	}
	///przeciwnika
	glTranslatef(granica1 + 40, 0, -(granica1));
	for (int i = 0; i<10; i++)
	{
		for (int j = 0; j<10; j++)
		{
			if (odkrytePrzeciwnika[i][j] == -1)
			{
				glColor3f(0.1, 0.1, 0.1);
				glutSolidSphere(4, 10, 10);
			}
			if (odkrytePrzeciwnika[i][j] == 1)
			{
				glColor3f(0, 1, 0);
				glutSolidTeapot(6);
			}
			if (odkrytePrzeciwnika[i][j] == 2)
			{
				glColor3f(0, 0, 1);
				glutSolidTeapot(6);
			}
			if (odkrytePrzeciwnika[i][j] == 3)
			{
				glColor3f(0, 1, 1);
				glutSolidTeapot(6);
			}
			if (odkrytePrzeciwnika[i][j] == 4)
			{
				glColor3f(1, 1, 0);
				glutSolidTeapot(6);
			}
			glTranslatef(skok, 0, 0);
		}
		glTranslatef(-10 * skok, 0, skok);
	}
	glTranslated(-(granica1 + 40), 0, (granica1));
	glPopMatrix();
}///////////

void strzalki()
{
	glPushMatrix();
	glTranslatef(-10, -5, -10 * skok - 10);
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);
	glVertex3f(xgreen, 0, zgreen);
	glVertex3f(xgreen, 0, zgreen + skok);
	glVertex3f(xgreen + skok, 0, zgreen + skok);
	glVertex3f(xgreen + skok, 0, zgreen);
	glEnd();
	glPopMatrix();
}

void zerujStatki()
{
	for (int i = 0; i<10; i++)
	{
		for (int j = 0; j<10; j++)
		{
			mojeStatki[i][j] = 0;
			zajete[i][j] = 0;
		}
	}
}

void zerujZajete()
{
	for (int i = 0; i<10; i++)
	{
		for (int j = 0; j<10; j++)
		{
			zajete[i][j] = 0;
		}
	}
}

void grid()
{

	glBegin(GL_LINES);
	for (int i = 0; i <= granica1; i = i + skok)
	{
		if (i == 0)
		{
			glColor3f(0, 0, 0);
		}
		else
		{
			glColor3f(0, 0, 0);
		};
		glVertex3f(i, 0, 0);
		glVertex3f(i, 0, granica1);
		if (i == 0)
		{
			glColor3f(0, 0, 0);
		}
		else
		{
			glColor3f(0, 0, 0);
		};
		glVertex3f(0, 0, i);
		glVertex3f(granica1, 0, i);
	};


	glEnd();
}

void display(void)
{
	glClearColor(0.05, 0.97, 0.9, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	camera();
	enable();
	start = clock();

	glDisable(GL_TEXTURE_1D);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, tekstura[5]);
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0.1, 0.1, 0.9);
	glTexCoord2f(0, 0);
	glVertex3f(-400, -5, -200);
	glTexCoord2f(0, 1);
	glVertex3f(-400, -5, 900);
	glTexCoord2f(1, 1);
	glVertex3f(900, -5, 900);
	glTexCoord2f(1, 0);
	glVertex3f(900, -5, -200);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glTranslated(granica1 + 40, 0, 0);
	grid();
	glTranslated(-(granica1 + 40), 0, 0);
	grid();

	finish = clock();
	czas = (double)(finish - start) / CLOCKS_PER_SEC;

	//  printf("x i z: %.2f   %.2f \n", xpos,zpos);


	pokazStatki();
	if (trafiony == 4)
	{
		glPushMatrix();
		glTranslated(granica1 + 150, 0, 50);
		glColor3f(0, 1, 0);
		glutSolidCube(120);
		glPopMatrix();
	}
	if (koniecUstawiania == 0)
	{
		glTranslated(0, 0, granica1);
		strzalki();
		indexj = xgreen / skok;
		indexi = zgreen / skok;
		glTranslated(0, 0, -(granica1));
	}
	else
	{
		glTranslated(granica1 + 40, 0, granica1);
		strzalki();
		indexj = xgreen / skok;
		indexi = zgreen / skok;
		glTranslated(-(granica1 + 40), 0, -(granica1));
	}


	glLoadIdentity();
	glOrtho(0, 1000, 0, 600, 0, 0.1);
	glDisable(GL_TEXTURE_1D);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, tekstura[0]);
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-430, 500, 0.05);
	glTexCoord2f(0, 1);
	glVertex3f(-430, 640, 0.05);
	glTexCoord2f(1, 1);
	glVertex3f(420, 640, 0.05);
	glTexCoord2f(1, 0);
	glVertex3f(420, 500, 0.05);
	glEnd();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tekstura[0]);
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(550, 500, 0.05);
	glTexCoord2f(0, 1);
	glVertex3f(550, 640, 0.05);
	glTexCoord2f(1, 1);
	glVertex3f(1400, 640, 0.05);
	glTexCoord2f(1, 0);
	glVertex3f(1400, 500, 0.05);
	glEnd();
	glPopMatrix();
	switch (maszty[0])
	{
	case 0:
		tex[0] = 3;
		tex[1] = 3;
		tex[2] = 3;
		tex[3] = 3;
		break;
	case 1:
		tex[0] = tex3;
		tex[1] = tex3;
		tex[2] = tex3;
		tex[3] = tex2;
		break;
	case 2:
		tex[0] = tex3;
		tex[1] = tex3;
		tex[2] = tex2;
		tex[3] = tex2;
		break;
	case 3:
		tex[0] = tex3;
		tex[1] = tex2;
		tex[2] = tex2;
		tex[3] = tex2;
		break;
	case 4:
		tex[0] = tex2;
		tex[1] = tex2;
		tex[2] = tex2;
		tex[3] = tex2;
		break;
	}
	switch (maszty[1])
	{
	case 0:
		tex[4] = tex3;
		tex[5] = tex3;
		tex[6] = tex3;
		break;
	case 1:
		tex[4] = tex3;
		tex[5] = tex3;
		tex[6] = tex2;
		break;
	case 2:
		tex[4] = tex3;
		tex[5] = tex2;
		tex[6] = tex2;
		break;
	case 3:
		tex[4] = tex2;
		tex[5] = tex2;
		tex[6] = tex2;
		break;
	}
	switch (maszty[2])
	{
	case 0:
		tex[7] = tex3;
		tex[8] = tex3;

		break;
	case 1:
		tex[7] = tex3;
		tex[8] = tex2;
		break;
	case 2:
		tex[7] = tex2;
		tex[8] = tex2;
		break;
	}
	switch (maszty[3])
	{
	case 0:
		tex[9] = tex3;
		break;
	case 1:
		tex[9] = tex2;
		break;
	}
	////////////

	switch (masztyPrzeciwnika[0])
	{
	case 0:
		texprzeciwnika[0] = 3;
		texprzeciwnika[1] = 3;
		texprzeciwnika[2] = 3;
		texprzeciwnika[3] = 3;
		break;
	case 1:
		texprzeciwnika[0] = tex3;
		texprzeciwnika[1] = tex3;
		texprzeciwnika[2] = tex3;
		texprzeciwnika[3] = tex2;
		break;
	case 2:
		texprzeciwnika[0] = tex3;
		texprzeciwnika[1] = tex3;
		texprzeciwnika[2] = tex2;
		texprzeciwnika[3] = tex2;
		break;
	case 3:
		texprzeciwnika[0] = tex3;
		texprzeciwnika[1] = tex2;
		texprzeciwnika[2] = tex2;
		texprzeciwnika[3] = tex2;
		break;
	case 4:
		texprzeciwnika[0] = tex2;
		texprzeciwnika[1] = tex2;
		texprzeciwnika[2] = tex2;
		texprzeciwnika[3] = tex2;
		break;
	}
	switch (masztyPrzeciwnika[1])
	{
	case 0:
		texprzeciwnika[4] = tex3;
		texprzeciwnika[5] = tex3;
		texprzeciwnika[6] = tex3;
		break;
	case 1:
		texprzeciwnika[4] = tex3;
		texprzeciwnika[5] = tex3;
		texprzeciwnika[6] = tex2;
		break;
	case 2:
		texprzeciwnika[4] = tex3;
		texprzeciwnika[5] = tex2;
		texprzeciwnika[6] = tex2;
		break;
	case 3:
		texprzeciwnika[4] = tex2;
		texprzeciwnika[5] = tex2;
		texprzeciwnika[6] = tex2;
		break;
	}
	switch (masztyPrzeciwnika[2])
	{
	case 0:
		texprzeciwnika[7] = tex3;
		texprzeciwnika[8] = tex3;

		break;
	case 1:
		texprzeciwnika[7] = tex3;
		texprzeciwnika[8] = tex2;
		break;
	case 2:
		texprzeciwnika[7] = tex2;
		texprzeciwnika[8] = tex2;
		break;
	}
	switch (masztyPrzeciwnika[3])
	{
	case 0:
		texprzeciwnika[9] = tex3;
		break;
	case 1:
		texprzeciwnika[9] = tex2;
		break;
	}
	rysujStatekTex(MINIX, MINIY, tex[0]);
	rysujStatekTex(MINIX + ODSX, MINIY, tex[1]);
	rysujStatekTex(2 * MINIX + 2.1*ODSX, MINIY, tex[2]);
	rysujStatekTex(3 * MINIX + 3.2*ODSX, MINIY, tex[3]);

	rysujStatekTex(MINIX, MINIY - ODSY, tex[4]);
	rysujStatekTex(MINIX + ODSX, MINIY - ODSY, tex[5]);
	rysujStatekTex(2 * MINIX + 2.1*ODSX, MINIY - ODSY, tex[6]);

	rysujStatekTex(MINIX, MINIY - 2 * ODSY, tex[7]);
	rysujStatekTex(MINIX + ODSX, MINIY - 2 * ODSY, tex[8]);

	rysujStatekTex(MINIX, MINIY - 3 * ODSY, tex[9]);




	rysujStatekTex(GR2 + MINIX, MINIY, texprzeciwnika[0]);
	rysujStatekTex(GR2 + MINIX + ODSX, MINIY, texprzeciwnika[1]);
	rysujStatekTex(GR2 + 2 * MINIX + 2.1*ODSX, MINIY, texprzeciwnika[2]);
	rysujStatekTex(GR2 + 3 * MINIX + 3.2*ODSX, MINIY, texprzeciwnika[3]);

	rysujStatekTex(GR2 + MINIX, MINIY - ODSY, texprzeciwnika[4]);
	rysujStatekTex(GR2 + MINIX + ODSX, MINIY - ODSY, texprzeciwnika[5]);
	rysujStatekTex(GR2 + 2 * MINIX + 2.1*ODSX, MINIY - ODSY, texprzeciwnika[6]);

	rysujStatekTex(GR2 + MINIX, MINIY - 2 * ODSY, texprzeciwnika[7]);
	rysujStatekTex(GR2 + MINIX + ODSX, MINIY - 2 * ODSY, texprzeciwnika[8]);

	rysujStatekTex(GR2 + MINIX, MINIY - 3 * ODSY, texprzeciwnika[9]);

	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();

	if (koniecUstawiania == 1)
	{
		if (kto == 0)
		{
			siec->connection();
			indexi = siec->exportx();
			indexj = siec->exporty();
			oznaczTrafieniePrzeciwnika(indexi, indexj);
			if (sprawdzCzyKoniec()){
				siec->importShoot('l');
				std::cout << "przegrana!" << std::endl;
			}
			siec->connection2();
			kto = siec->exportShoot();
			std::cout << "kto " << kto << std::endl;
			czyStrzal = false;
		}
		if ((kto == 1 || kto == 2) && czyStrzal)
		{
			siec->importx(indexi);
			siec->importy(indexj);
			siec->connection();
			siec->connection2();
			oznaczStatekPrzeciwnika();
			kto = siec->exportShoot();
			if (kto == 3){
				std::cout << "wygrana!" << std::endl;
			}
			std::cout << "kto " << kto << std::endl;
			czyStrzal = false;
		}
	}


}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	display();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 'q')
	{
		xrot += 1;
		if (xrot >360)
			xrot -= 360;
	}

	if (key == 'z')
	{
		xrot -= 1;
		if (xrot < -360)
			xrot += 360;
	}

	if (key == 'w')
	{
		float xrotrad, yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xrotrad = (xrot / 180 * 3.141592654f);
		xpos += float(4 * sin(yrotrad));
		zpos -= float(4 * cos(yrotrad));
		ypos -= float(4 * sin(xrotrad));
	}

	if (key == 's')
	{
		float xrotrad, yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xrotrad = (xrot / 180 * 3.141592654f);
		xpos -= float(4 * sin(yrotrad));
		zpos += float(4 * cos(yrotrad));
		ypos += float(4 * sin(xrotrad));
	}

	if (key == 'd')
	{
		yrot += 1;
		if (yrot >360)
			yrot -= 360;

	}

	if (key == 'a')
	{
		yrot -= 1;
		if (yrot < -360)
			yrot += 360;

	}
	if (key == 27)
	{
		if ((kto == 1 || kto == 2))
			siec->sendEnd();
		exit(0);
	}

	if (key == 't')
	{

	}

	if (key == 'y')
	{
		glDisable(GL_TEXTURE_2D);
	}
	if (key == 'o')//ja strzelam
	{
		if ((koniecUstawiania == 1) && (odkrytePrzeciwnika[indexi][indexj] == 0))
			czyStrzal = true;
	}
	if (key == 'p')
	{
		if (koniecUstawiania == 0)
		{

			if (maszty[liczbaMasztow - 1]>0)
			{
				if (sprawdzStatek(indexi, indexj, liczbaMasztow, poziom) == true)
				{
					ustawStatek(indexi, indexj, liczbaMasztow, poziom);
					switch (liczbaMasztow)
					{
					case 1:
						maszty[0]--;
						break;

					case 2:
						maszty[1]--;
						break;

					case 3:
						maszty[2]--;
						break;

					case 4:
						maszty[3]--;
						break;
					}
					if ((maszty[liczbaMasztow - 1] == 0)&(liczbaMasztow != -1))
						liczbaMasztow--;
				}
			}
		}
	}
	if (key == 'i')
	{
		for (int i = 0; i<10; i++)
		{
			for (int j = 0; j<10; j++)
			{
				printf("%d, ", odkrytePrzeciwnika[i][j]);
			}
			printf("\n");
		}
		printf("WWWWWWWWWWWWWWWWWWWodkryteprzeciwnikaWWWWWWWWWWWWWWWWWWWWWWWWW\n");
	}
	if (key == 'k')
	{
		for (int i = 0; i<10; i++)
		{
			for (int j = 0; j<10; j++)
			{
				printf("%d, ", zajete[i][j]);
			}
			printf("\n");
		}
		printf("WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\n");
	}
	display();
}

void MouseMotion(int x, int y)
{
	static int m1 = w / 2;
	static int m2 = h / 2;


	yrot += (x - m1) / 10.f;
	xrot += (y - m2) / 4.f;

	glutWarpPointer(w / 2, h / 2);
	reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		zgreen -= skok;
		if (zgreen<0)
			zgreen = 0;
		break;

	case GLUT_KEY_RIGHT:
		xgreen += skok;
		if (xgreen>granica1 - skok)
			xgreen = granica1 - skok;
		break;

	case GLUT_KEY_DOWN:
		zgreen += skok;
		if (zgreen>granica1 - skok)
			zgreen = granica1 - skok;
		break;

	case GLUT_KEY_LEFT:
		xgreen -= skok;
		if (xgreen<0)
			xgreen = 0;
		break;
	}
}

void oznaczStatekPrzeciwnika()
{
	if ((koniecUstawiania == 1) && (odkrytePrzeciwnika[indexi][indexj] == 0))
	{
		int temp;
		if ((temp = siec->exportShoot()) == 0)
			odkrytePrzeciwnika[indexi][indexj] = -1;
		else if ((temp = siec->exportShoot()) == 1)
		{
			odkrytePrzeciwnika[indexi][indexj] = 1;
		}
		else if ((temp = siec->exportShoot()) == 2 || (temp = siec->exportShoot()) == 3)
		{
			odkrytePrzeciwnika[indexi][indexj] = 1;
			okrazanieZatopionychPrzeciwnika(indexi, indexj);
		}
	}
}

void oznaczTrafieniePrzeciwnika(int x, int y)
{


	if (mojeStatki[x][y] == 0)
	{
		mojeStatki[x][y] = -1;
		siec->importShoot('p');
		siec->importDrawn('n');
		trafiony = 1;
	}
	else if (mojeStatki[x][y] == 1)
	{
		siec->importShoot('t');
		siec->importDrawn('z');
		trafiony = 3;//wywylam wiadomosc ze trafiony zatopiony
		maszty[0]++;
		//z tego wynika ze

		for (int i = 0; i<3; i++)
		{
			for (int j = 0; j<3; j++)
			{
				if (((x - 1 + i) >= 0) && ((x - 1 + i) <= 9) && ((y - 1 + j) >= 0) && ((y - 1 + j) <= 9))
				{
					if (mojeStatki[x - 1 + i][y - 1 + j] != 1)
						mojeStatki[x - 1 + i][y - 1 + j] = -1;
				}
			}
		}
		mojeStatki[x][y] = 11;
	}
	else if (mojeStatki[x][y] == 2)
	{
		mojeStatki[x][y] = 12;
		if ((mojeStatki[x - 1][y] == 12) || ((mojeStatki[x + 1][y] == 12) || (mojeStatki[x][y - 1] == 12)) || (mojeStatki[x][y + 1] == 12))
		{
			siec->importShoot('t');
			siec->importDrawn('z');
			trafiony = 3;//wywylam wiadomosc ze trafiony zatopiony
			maszty[1]++;
			okrazanieZatopionych(x, y, 12);
		}
		else
		{
			trafiony = 2;
			siec->importShoot('t');
			siec->importDrawn('n');
		}
	}

	else if (mojeStatki[x][y] == 3)
	{
		mojeStatki[x][y] = 13;
		if (((mojeStatki[x - 2][y] == 13) && (mojeStatki[x - 1][y] == 13)) || ((mojeStatki[x - 1][y] == 13) && (mojeStatki[x + 1][y] == 13)) || ((mojeStatki[x + 1][y] == 13) && (mojeStatki[x + 2][y] == 13)) ||
			((mojeStatki[x][y - 2] == 13) && (mojeStatki[x][y - 1] == 13)) || ((mojeStatki[x][y - 1] == 13) && (mojeStatki[x][y + 1] == 13)) || ((mojeStatki[x][y + 1] == 13) && (mojeStatki[x][y + 2] == 13)))
		{
			siec->importShoot('t');
			siec->importDrawn('z');
			trafiony = 3;
			maszty[2]++;
			okrazanieZatopionych(x, y, 13);
		}
		else
		{
			siec->importShoot('t');
			siec->importDrawn('n');
			trafiony = 2;
		}
	}
	else if (mojeStatki[x][y] == 4)
	{
		mojeStatki[x][y] = 14;
		if (((mojeStatki[x - 3][y] == 14) && (mojeStatki[x - 2][y] == 14) && (mojeStatki[x - 1][y] == 14)) ||
			((mojeStatki[x - 2][y] == 14) && (mojeStatki[x - 1][y] == 14) && (mojeStatki[x + 1][y] == 14)) ||
			((mojeStatki[x - 1][y] == 14) && (mojeStatki[x + 1][y] == 14) && (mojeStatki[x + 2][y] == 14)) ||
			((mojeStatki[x + 1][y] == 14) && (mojeStatki[x + 2][y] == 14) && (mojeStatki[x + 3][y] == 14)) ||
			((mojeStatki[x][y - 3] == 14) && (mojeStatki[x][y - 2] == 14) && (mojeStatki[x][y - 1] == 14)) ||
			((mojeStatki[x][y - 2] == 14) && (mojeStatki[x][y - 1] == 14) && (mojeStatki[x][y + 1] == 14)) ||
			((mojeStatki[x][y - 1] == 14) && (mojeStatki[x][y + 1] == 14) && (mojeStatki[x][y + 2] == 14)) ||
			((mojeStatki[x][y + 1] == 14) && (mojeStatki[x][y + 2] == 14) && (mojeStatki[x][y + 3] == 14)))

		{
			siec->importShoot('t');
			siec->importDrawn('z');
			trafiony = 3;
			maszty[3]++;
			okrazanieZatopionych(x, y, 14);
		}
		else
		{
			siec->importShoot('t');
			siec->importDrawn('n');
			trafiony = 2;
		}
	}
}

void Menu(int value)
{
	switch (value)
	{
	case JEDNOMASZTOWCE:
		liczbaMasztow = 1;
		break;
	case DWUMASZTOWCE:
		liczbaMasztow = 2;
		break;
	case TRZYMASZTOWCE:
		liczbaMasztow = 3;
		break;
	case CZTEROMASZTOWCE:
		liczbaMasztow = 4;
		break;
	case POZIOMO:
		poziom = 0;
		break;
	case PIONOWO:
		poziom = 1;
		break;
	case ZEROWANIE:
		if (koniecUstawiania == 0)
		{
			zerujStatki();
			for (int i = 0; i<4; i++)
				maszty[i] = 4 - i;
		}
		break;
	case START:
		if ((maszty[0] == 0)&(maszty[1] == 0)&(maszty[2] == 0)&(maszty[3] == 0))
		{
			koniecUstawiania = 1;
			zerujZajete();
			tex2 = 4;

			zerujZajete();

			///////////////////////////////
		}
		break;


	}
}

int main(int argc, char **argv)
{
	std::cout << "podaj adres ip serwera" << std::endl;
	std::string addr;
	std::cin >> addr;
	siec = new Siec(addr);
	srand(time(0));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(w, h);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);

	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(SpecialKeys);
	// obs³uga ruchu kursora myszki
	// glutFullScreen();

	//glutMotionFunc(MouseMotion);
	ShowCursor(1);
	glutCreateMenu(Menu);
	kto = siec->firstConn();
	std::cout << kto << std::endl;
	glutAddMenuEntry("1- masztowce", JEDNOMASZTOWCE);
	glutAddMenuEntry("2- masztowce", DWUMASZTOWCE);
	glutAddMenuEntry("3- masztowce", TRZYMASZTOWCE);
	glutAddMenuEntry("4- masztowce", CZTEROMASZTOWCE);
	glutAddMenuEntry("statek poziomy", POZIOMO);
	glutAddMenuEntry("statek pionowy", PIONOWO);
	glutAddMenuEntry("wyczysc plansze", ZEROWANIE);
	glutAddMenuEntry("zacznij gre", START);

	glGenTextures(1, &tekstura[0]);
	glBindTexture(GL_TEXTURE_2D, tekstura[0]);
	LoadTGATexture((char *)"baner.tga");
	glGenTextures(1, &tekstura[1]);
	glBindTexture(GL_TEXTURE_2D, tekstura[1]);
	LoadTGATexture((char *)"baner2.tga");

	glGenTextures(1, &tekstura[2]);
	glBindTexture(GL_TEXTURE_2D, tekstura[2]);
	LoadTGATexture((char *)"stateknakt.tga");

	glGenTextures(1, &tekstura[3]);
	glBindTexture(GL_TEXTURE_2D, tekstura[3]);
	LoadTGATexture((char *)"statekakt.tga");

	glGenTextures(1, &tekstura[4]);
	glBindTexture(GL_TEXTURE_2D, tekstura[4]);
	LoadTGATexture((char *)"statekskr.tga");

	glGenTextures(1, &tekstura[5]);
	glBindTexture(GL_TEXTURE_2D, tekstura[5]);
	LoadTGATexture((char *)"ocean.tga");

	glGenTextures(1, &tekstura[6]);
	glBindTexture(GL_TEXTURE_2D, tekstura[6]);
	LoadTGATexture((char *)"tratwa.tga");

	glGenTextures(1, &tekstura[7]);
	glBindTexture(GL_TEXTURE_2D, tekstura[7]);
	LoadTGATexture((char *)"hybryda.tga");

	glGenTextures(1, &tekstura[8]);
	glBindTexture(GL_TEXTURE_2D, tekstura[8]);
	LoadTGATexture((char *)"22.tga");


	glGenTextures(1, &tekstura[9]);
	glBindTexture(GL_TEXTURE_2D, tekstura[9]);
	LoadTGATexture((char *)"statek12.tga");


	res = loadOBJ("tratwa.obj", vertices, uvs, normals);
	res2 = loadOBJ("statekEnd.obj", vertices4, uvs4, normals4);
	res3 = loadOBJ("hybryda.obj", vertices3, uvs3, normals3);
	res4 = loadOBJ("lodkaEnd.obj", vertices2, uvs2, normals2);


	//glutAddSubMenu("Aspekt obrazu", MenuAspect);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}

