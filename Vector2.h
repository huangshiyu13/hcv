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
	double Dot( const Vector2& ); //��� 
	double Module2();//��ģ��ƽ�� 
	double Module();//��ģ 
	Vector2 GetUnitVector();//��λ�� 
	bool IsZeroVector();//�ж��Ƿ��������� 
};

#endif
