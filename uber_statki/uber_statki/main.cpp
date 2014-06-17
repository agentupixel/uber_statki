#include "main.h"

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
			if (odkrytePrzeciwnika[x - 1 + i][y - 1 + j] == 1)
				okrazanieZatopionychPrzeciwnika(x - 1 + i, y - 1 + j);
			else if (odkrytePrzeciwnika[x - 1 + i][y - 1 + j] == 0)
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
			if (mojeStatki[x - 1 + i][y - 1 + j] == rodzaj)
				okrazanieZatopionych(x - 1 + i, y - 1 + j, rodzaj);
			else if (mojeStatki[x - 1 + i][y - 1 + j] == 0)
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

void ustawStatekPrzeciwnika(int wiersz, int kolumna, int amaszty, int apoziom)
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
				statkiPrzeciwnika[wiersz][kol2] = 1;
				zajete[wiersz][kol2] = 5;
			}
			else if (amaszty == 2)
			{
				statkiPrzeciwnika[wiersz][kol2] = 2;
				zajete[wiersz][kol2] = 5;
			}
			else if (amaszty == 3)
			{
				statkiPrzeciwnika[wiersz][kol2] = 3;
				zajete[wiersz][kol2] = 5;
			}
			else if (amaszty == 4)
			{
				statkiPrzeciwnika[wiersz][kol2] = 4;
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
				statkiPrzeciwnika[wier2][kolumna] = 1;
				zajete[wier2][kolumna] = 5;
			}
			else if (amaszty == 2)
			{
				statkiPrzeciwnika[wier2][kolumna] = 2;
				zajete[wier2][kolumna] = 5;
			}
			else if (amaszty == 3)
			{
				statkiPrzeciwnika[wier2][kolumna] = 3;
				zajete[wier2][kolumna] = 5;
			}
			else if (amaszty == 4)
			{
				statkiPrzeciwnika[wier2][kolumna] = 4;
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
				glColor3f(0.1, 0.1, 0.1);
				glutSolidSphere(4, 15, 15);
			}
			//
			switch (mojeStatki[i][j])
			{
			case 1:
				glColor3f(0, 1, 0);
				glutSolidSphere(4, 15, 15);
				break;
			case 2:
				glColor3f(0, 0, 1);
				glutSolidSphere(4, 15, 15);
				break;
			case 3:
				glColor3f(0, 1, 1);
				glutSolidSphere(4, 15, 15);
				break;
			case 4:
				glColor3f(1, 1, 0);
				glutSolidSphere(4, 15, 15);
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
}

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

	rysujStatekTex(GR2 + MINIX, MINIY, tex[0]);
	rysujStatekTex(GR2 + MINIX + ODSX, MINIY, tex[0]);
	rysujStatekTex(GR2 + 2 * MINIX + 2.1*ODSX, MINIY, tex[0]);
	rysujStatekTex(GR2 + 3 * MINIX + 3.2*ODSX, MINIY, tex[0]);

	rysujStatekTex(GR2 + MINIX, MINIY - ODSY, tex[0]);
	rysujStatekTex(GR2 + MINIX + ODSX, MINIY - ODSY, tex[0]);
	rysujStatekTex(GR2 + 2 * MINIX + 2.1*ODSX, MINIY - ODSY, tex[0]);

	rysujStatekTex(GR2 + MINIX, MINIY - 2 * ODSY, tex[0]);
	rysujStatekTex(GR2 + MINIX + ODSX, MINIY - 2 * ODSY, tex[0]);

	rysujStatekTex(GR2 + MINIX, MINIY - 3 * ODSY, tex[0]);

	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();

	if (koniecUstawiania == 1){
		if (kto == 0){
			siec->connection();
			indexi = siec->exportx();
			indexj = siec->exporty();
			oznaczTrafieniePrzeciwnika(indexi, indexj);
			/*todo: 
			za kazdym razem sprawdzac, czy sa jeszcze jakies niezatopione statki, jak nie ma to:
			siec->importShoot('l');*/
			siec->connection2();
			kto = siec->exportShoot();
			std::cout << "kto " << kto << std::endl;
			czyStrzal = false;
		}
		if ((kto == 1 || kto == 2) && czyStrzal){
			siec->importx(indexi);
			siec->importy(indexj);
			siec->connection();
			siec->connection2();
			oznaczStatekPrzeciwnika();
			kto = siec->exportShoot();
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
		if (koniecUstawiania == 1)
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

void oznaczStatekPrzeciwnika(){
	if ((koniecUstawiania == 1) && (odkrytePrzeciwnika[indexi][indexj] == 0))
	{
		int temp;
		if ((temp = siec->exportShoot()) == 0)
			odkrytePrzeciwnika[indexi][indexj] = -1;
		else if ((temp = siec->exportShoot()) == 1)
		{
			odkrytePrzeciwnika[indexi][indexj] = 1;
		}
		else if ((temp = siec->exportShoot()) == 2){
			odkrytePrzeciwnika[indexi][indexj] = 1;
			okrazanieZatopionychPrzeciwnika(indexi, indexj);
		}
	}
}

void oznaczTrafieniePrzeciwnika(int x, int y){


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
					if (((x - 1 + i) >= 0)&&((x - 1 + i) <= 9)&&((y - 1 + j) >= 0)&&((y - 1 + j) <= 9))
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
			else{
				trafiony = 2;
				siec->importShoot('t');
				siec->importDrawn('n');
			}
		}

		else if (mojeStatki[x][y] == 3)
		{
			mojeStatki[x][y] = 13;
			if (((mojeStatki[x - 2][y] == 13)&&(mojeStatki[x - 1][y] == 13)) || ((mojeStatki[x - 1][y] == 13)&&(mojeStatki[x + 1][y] == 13)) || ((mojeStatki[x + 1][y] == 13)&&(mojeStatki[x + 2][y] == 13)) ||
				((mojeStatki[x][y - 2] == 13)&&(mojeStatki[x][y - 1] == 13)) || ((mojeStatki[x][y - 1] == 13)&&(mojeStatki[x][y + 1] == 13)) || ((mojeStatki[x][y + 1] == 13)&&(mojeStatki[x][y + 2] == 13)))
			{
				siec->importShoot('t');
				siec->importDrawn('z');
				trafiony = 3;
				maszty[2]++;
				okrazanieZatopionych(x, y, 13);
			}
			else{
				siec->importShoot('t');
				siec->importDrawn('n');
				trafiony = 2;
			}
		}
		else if (mojeStatki[x][y] == 4)
		{
			mojeStatki[x][y] = 14;
			if (((mojeStatki[x - 3][y] == 14)&&(mojeStatki[x - 2][y] == 14)&&(mojeStatki[x - 1][y] == 14)) ||
				((mojeStatki[x - 2][y] == 14)&&(mojeStatki[x - 1][y] == 14)&&(mojeStatki[x + 1][y] == 14)) ||
				((mojeStatki[x - 1][y] == 14)&&(mojeStatki[x + 1][y] == 14)&&(mojeStatki[x + 2][y] == 14)) ||
				((mojeStatki[x + 1][y] == 14)&&(mojeStatki[x + 2][y] == 14)&&(mojeStatki[x + 3][y] == 14)) ||
				((mojeStatki[x][y - 3] == 14)&&(mojeStatki[x][y - 2] == 14)&&(mojeStatki[x][y - 1] == 14)) ||
				((mojeStatki[x][y - 2] == 14)&&(mojeStatki[x][y - 1] == 14)&&(mojeStatki[x][y + 1] == 14)) ||
				((mojeStatki[x][y - 1] == 14)&&(mojeStatki[x][y + 1] == 14)&&(mojeStatki[x][y + 2] == 14)) ||
				((mojeStatki[x][y + 1] == 14)&&(mojeStatki[x][y + 2] == 14)&&(mojeStatki[x][y + 3] == 14)))

			{
				siec->importShoot('t');
				siec->importDrawn('z');
				trafiony = 3;
				maszty[3]++;
				okrazanieZatopionych(x, y, 14);
			}
			else{
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
			///////////////////////////////

			//
			{
				liczbaMasztow = 4;
				int x = 0;
				int y = 0;

				while (masztyPrzeciwnika[liczbaMasztow - 1]>0)
				{
					printf("helo³%d,%d, poziom %d,licczbamasztow %d\n", x, y, poziom, liczbaMasztow);
					do
					{
						do
						{
							x = strzalPrzeciwnika();
							y = strzalPrzeciwnika();
						} while ((statkiPrzeciwnika[x][y] == -1) | (statkiPrzeciwnika[x][y] == -2));
						poziom = rand() % 2;
						printf("helo³%d,%d, poziom %d,licczbamasztow %d\n", x, y, poziom, liczbaMasztow);
					} while (sprawdzStatek(x, y, liczbaMasztow, poziom) != true);
					ustawStatekPrzeciwnika(x, y, liczbaMasztow, poziom);
					switch (liczbaMasztow)
					{
					case 1:
						masztyPrzeciwnika[0]--;
						break;

					case 2:
						masztyPrzeciwnika[1]--;
						break;

					case 3:
						masztyPrzeciwnika[2]--;
						break;

					case 4:
						masztyPrzeciwnika[3]--;
						break;

					}

					if ((masztyPrzeciwnika[liczbaMasztow - 1] == 0)&(liczbaMasztow != -1))
						liczbaMasztow--;

				}
				zerujZajete();
			}
			///////////////////////////////
		}
		break;


	}
}

int main(int argc, char **argv)
{
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
	glutMotionFunc(MouseMotion);
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
	// glutCreateMenu(Menu);

	glGenTextures(1, &tekstura[0]);
	glBindTexture(GL_TEXTURE_2D, tekstura[0]);
	LoadTGATexture("baner.tga");
	glGenTextures(1, &tekstura[1]);
	glBindTexture(GL_TEXTURE_2D, tekstura[1]);
	LoadTGATexture("baner2.tga");

	glGenTextures(1, &tekstura[2]);
	glBindTexture(GL_TEXTURE_2D, tekstura[2]);
	LoadTGATexture("stateknakt.tga");

	glGenTextures(1, &tekstura[3]);
	glBindTexture(GL_TEXTURE_2D, tekstura[3]);
	LoadTGATexture("statekakt.tga");

	glGenTextures(1, &tekstura[4]);
	glBindTexture(GL_TEXTURE_2D, tekstura[4]);
	LoadTGATexture("statekskr.tga");

	glGenTextures(1, &tekstura[5]);
	glBindTexture(GL_TEXTURE_2D, tekstura[5]);
	LoadTGATexture("ocean.tga");
	//glutAddSubMenu("Aspekt obrazu", MenuAspect);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}

