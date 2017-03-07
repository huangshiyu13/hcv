#include"color.h"
#include<sstream>

Color operator + ( const Color& A , const Color& B ) {
	return Color( A.r + B.r , A.g + B.g , A.b + B.b );
}

Color operator - ( const Color& A , const Color& B ) {
	return Color( A.r - B.r , A.g - B.g , A.b - B.b );
}

Color operator * ( const Color& A , const Color& B ) {
	return Color( A.r * B.r , A.g * B.g , A.b * B.b );
}

bool operator == ( const Color& A, const Color& B){
	return (A.r==B.r && A.b==B.b && A.g==B.g)?true:false;
}

bool operator != ( const Color& A, const Color& B){
	return 	A==B?false:true;
}

Color operator * ( const Color& A , const double& k ) {
	return Color( A.r * k , A.g * k , A.b * k );
}

Color operator / ( const Color& A , const double& k ) {
	return Color( A.r / k , A.g / k , A.b / k );
}

Color& operator += ( Color& A , const Color& B ) {
	A = A + B;
	return A;
}

Color& operator -= ( Color& A , const Color& B ) {
	A = A - B;
	return A;
}

Color& operator *= ( Color& A , const double& k ) {
	A = A * k;
	return A;
}

Color& operator /= ( Color& A , const double& k ) {
	A = A / k;
	return A;
}

Color Color::lerpColor(Color& l , Color& h , double a ){
	if (a > 1 ) a = 1;
	if (a < 0 ) a = 0;
	Color tmp;
	tmp = h-l;
	tmp = tmp*a;
	tmp = tmp + l;
	return tmp;
}

Color Color::lerpColor( Color& h, double a ){
	Color l = *this;
	return lerpColor(l , h , a );
}

void Color::Confine() {
	if ( r > 1 ) r = 1;
	if ( g > 1 ) g = 1;
	if ( b > 1 ) b = 1;
}

void Color::Input( std::stringstream& fin ) {
	fin >> r >> g >> b;
}
