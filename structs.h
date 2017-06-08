#ifndef STRUCTS_H
#define STRUCTS_H

////////////////////////////////////////////////////////////////////////////////////////////////////
//						Formato PPM
////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct {
	unsigned char R;
	unsigned char G;
	unsigned char B;
}pixel;

typedef struct {
	char id[3];
	unsigned int largura;
	unsigned int altura;
	unsigned int max;
	pixel **pixelMap;
}imgPPM;

////////////////////////////////////////////////////////////////////////////////////////////////////
//						Formato BMP
////////////////////////////////////////////////////////////////////////////////////////////////////

#define bfTYPE 19778
#define biSIZE 40

typedef struct {
	unsigned short int fileType;
	unsigned int fileSize;
	unsigned short int fileReserved1;
	unsigned short int fileReserved2;
	unsigned int fileOffBits;
}fileHeaderBMP;

typedef struct {
	unsigned int biSize;
	unsigned int biWidth;
	unsigned int biHeight;
	unsigned short int biPlanes;
	unsigned short int biBitCount;
	unsigned int biCompression;		// RLE	= bi_RGB = 0, bi_RGB8 = 1, bi_RGB4 = 2;
	unsigned int biSizeImage;
	unsigned int biXpelsPerMeter;
	unsigned int biYpelsPerMeter;
	unsigned int biClrUsed;
	unsigned int biClrImportant;
}infoHeaderBMP;

typedef struct {
	unsigned char B;
	unsigned char G;
	unsigned char R;
	//unsigned char Reserved;
}RGBSquad;

typedef struct {
	unsigned char P1;
	unsigned char P2;
}pading;


typedef struct {
	infoHeaderBMP header;
	//RGBSquad *colors;
}infoBMP;

typedef struct {
	fileHeaderBMP header;
	infoBMP info;
	RGBSquad **pixelMap;
	pading *padRow;
}imgBMP;

////////////////////////////////////////////////////////////////////////////////////////////////////
//						Formato ???
////////////////////////////////////////////////////////////////////////////////////////////////////
#endif