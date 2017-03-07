#ifndef BMP_H
#define BMP_H

#include "color.h"
#include "Vector2.h"
#include<string>

const double EPS = 1e-6;

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned int dword;

struct myBITMAPFILEHEADER {
	dword bfSize;
	word bfReserved1;
	word bfReserved2;
	dword bfOffBits;
};

struct myBITMAPINFOHEADER {
	dword biSize;
	long biWidth;
	long biHeight;
	word biPlanes;
	word biBitCount;
	dword biCompression;
	dword biSizeImage;
	long biXPelsPerMeter;
	long biYPelsPerMeter;
	dword biClrUsed;
	dword biClrImportant;
};

struct myRGBQUAD {
	byte rgbBlue;
	byte rgbGreen;
	byte rgbRed;
	byte rgbReserved;
};

struct IMAGEDATA {
	byte red;
	byte green;
	byte blue;
	Color GetColor() {
		return Color( red , green , blue ) / 255;
	}
};

class Bmp {
	myBITMAPFILEHEADER strHead;
	myBITMAPINFOHEADER strInfo;
	bool ima_created;
	IMAGEDATA** ima;
	Color** thisColor;
	void Release();
	
public:
	Bmp( int H = 0 , int W = 0 );
	~Bmp();

	int GetH() { return strInfo.biHeight; }
	int GetW() { return strInfo.biWidth; }
	Color GetColor( int i , int j ) { 
		if (i < 0 ){
			i = 0;
		}
		if (j < 0 ){
			j = 0;
		}
		if (i >= GetH()){
			i = GetH()-1;
		}
		if ( j >= GetW()){
			j = GetW()-1;
		}
		return thisColor[i][j]; 
	}
	void SetColor( int i , int j , Color color = Color(0,0,0) );
	void SetColor( Vector2 O , Color color = Color(0,0,0) );
	void Initialize( int H , int W );
	void Input( std::string file );
	void Output( std::string file );
	Color GetSmoothColor( double u , double v );
};

#endif
