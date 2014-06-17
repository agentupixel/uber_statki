/*
*	Targa.h
*/

typedef struct {
	GLuint bpp;		// ilooa bitów na piksel
	GLuint width;	// rozmiary w pikselach
	GLuint height;
} TARGAINFO;

// Funkcje
GLubyte *LoadTGAImage(char *filename, TARGAINFO *info);
bool LoadTGATexture(char *filename);
bool LoadTGAMipmap(char *filename);