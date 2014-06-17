#define _CRT_SECURE_NO_DEPRECATE
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "Targa.h"

GLubyte *LoadTGAImage(char *filename, TARGAINFO *info)
{
	GLubyte	TGAHeader[12] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };	// Nag3ówek TGA bez kompresji
	GLubyte	TGACompare[12];			// Tu sie za3aduje dane z pliku
	GLubyte	Header[6];			// Pierwsze potrzebne 6 bajtów z pliku
	GLubyte *Bits = NULL;	// WskaYnik na bufor z danymi pikseli
	FILE *plik = fopen(filename, "rb");	// warning: deprecated 
	if (plik)
	{
		fread(TGACompare, 1, sizeof(TGACompare), plik);	// Odczytanie nag3ówka pliku
		if (memcmp(TGAHeader, TGACompare, sizeof(TGAHeader)) == 0)	// Nag3ówek identyczny?
		{
			fread(Header, 1, sizeof(Header), plik);	// Odczyt u?ytecznych danych

			// Wy3uskanie informacji o rozmiarach
			info->width = Header[1] * 256 + Header[0];
			info->height = Header[3] * 256 + Header[2];
			info->bpp = Header[4];

			// Sprawdzenie czy rozmiary > 0 oraz czy bitmapa 24 lub 32-bitowa
			if (info->width>0 && info->height>0 && (info->bpp == 24 || info->bpp == 32))
			{
				long ImageSize = info->height * info->width * info->bpp / 8;	// Obliczenie ilooci danych
				Bits = (GLubyte*)malloc(ImageSize);	// Alokacja pamieci na dane

				if (Bits)
				{
					fread(Bits, 1, ImageSize, plik);	// Odczyt w3aociwych danych pikseli z pliku

					// Konwersja BGR -> RGB
					int i;
					GLubyte tmp;	// Miejsce przechowania jednej wartooci koloru

					for (i = 0; i < ImageSize; i += info->bpp / 8)	// Wszystkie wartooci RGB lub RGBA
					{
						tmp = Bits[i];
						Bits[i] = Bits[i + 2];
						Bits[i + 2] = tmp;
					}
				}
			}
		}

		fclose(plik);
	}

	return(Bits);
}

///////////////////////////////////////////////////////////////////////////////
// Procedury na podstawie przekazanych danych 3aduj1
// i tworz1 teksture lub teksture z Mip-Map'ami
bool LoadTGATexture(char *filename)
{
	TARGAINFO info;	// Dane o bitmapie
	GLubyte *bits;	// Dane o pikselach

	// 3adowanie pliku
	bits = LoadTGAImage(filename, &info);	// Próba wczytania tekstury
	if (bits == NULL)	return(FALSE);	// ERROR

	// Ustawienie parametrów tekstury
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	if (info.bpp == 24)	// Bitmapa z danymi RGB
		glTexImage2D(GL_TEXTURE_2D, 0, 3, info.width, info.height, 0, GL_RGB, GL_UNSIGNED_BYTE, bits);
	else	// Bitmapa z danymi RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, 4, info.width, info.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bits);

	free(bits);
	return(TRUE);
}

bool LoadTGAMipmap(char *filename)
{
	TARGAINFO info;	// Dane o bitmapie
	GLubyte *bits;	// Dane o pikselach

	// 3adowanie pliku
	bits = LoadTGAImage(filename, &info);	// Próba wczytania tekstury
	if (bits == NULL)	return(FALSE);	// ERROR

	// Ustawienie parametrów tekstury
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	if (info.bpp == 24)	// Bitmapa z danymi RGB
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, info.width, info.height, GL_RGB, GL_UNSIGNED_BYTE, bits);
	else	// Bitmapa z danymi RGBA
		gluBuild2DMipmaps(GL_TEXTURE_2D, 4, info.width, info.height, GL_RGBA, GL_UNSIGNED_BYTE, bits);

	free(bits);
	return(TRUE);
}