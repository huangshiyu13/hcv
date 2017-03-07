#include"vector2.h"
#include<cmath>
#include<sstream>

const double EPS = 1e-6;

Vector2 operator + ( const Vector2& A , const Vector2& B ) {
	return Vector2( A.x + B.x , A.y + B.y);
}

Vector2 operator - ( const Vector2& A , const Vector2& B ) {
	return Vector2( A.x - B.x , A.y - B.y);
}

Vector2 operator * ( const Vector2& A , const double& k ) {
	return Vector2( A.x * k , A.y * k );
}

Vector2 operator / ( const Vector2& A , const double& k ) {
	return Vector2( A.x / k , A.y / k );
}

Vector2& operator += ( Vector2& A , const Vector2& B ) {
	A = A + B;
	return A;
}

Vector2& operator -= ( Vector2& A , const Vector2& B ) {
	A = A - B;
	return A;
}

Vector2& operator *= ( Vector2& A , const double& k ) {
	A = A * k;
	return A;
}

Vector2& operator /= ( Vector2& A , const double& k ) {
	A = A / k;
	return A;
}

Vector2 operator - ( const Vector2& A ) {
	return Vector2( -A.x , -A.y );
}

double Vector2::Dot( const Vector2& term ) {
	return x * term.x + y * term.y;
}

double Vector2::Module2() {
	return x * x + y * y;
}

double Vector2::Module() {
	return sqrt( x * x + y * y );
}

Vector2 Vector2::GetUnitVector() {
	return *this / Module();
}

bool Vector2::IsZeroVector() {
	return fabs( x ) < EPS && fabs( y ) < EPS ;
}
