#ifndef Vector2h
#define Vector2h

#include<sstream>

class Vector2 {
public:
	double x , y;

	Vector2( double X = 0 , double Y = 0) : x( X ) , y( Y ) {}

	friend Vector2 operator + ( const Vector2& , const Vector2& );
	friend Vector2 operator - ( const Vector2& , const Vector2& );
	friend Vector2 operator * ( const Vector2& , const double& );
	friend Vector2 operator / ( const Vector2& , const double& );
	friend Vector2& operator += ( Vector2& , const Vector2& );
	friend Vector2& operator -= ( Vector2& , const Vector2& );
	friend Vector2& operator *= ( Vector2& , const double& );
	friend Vector2& operator /= ( Vector2& , const double& );
	friend Vector2 operator - ( const Vector2& );
	double Dot( const Vector2& ); //相乘 
	double Module2();//求模的平方 
	double Module();//求模 
	Vector2 GetUnitVector();//单位化 
	bool IsZeroVector();//判断是否是零向量 
};

#endif
