#include <iostream>
#include <cmath>
#include <ctime>
#include "bmp.h"
#include "Vector2.h"
#include "stack" 
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <windows.h>
#include <stdio.h>
#include <psapi.h>
#include <iomanip>
#pragma comment(lib, "psapi.lib")
using namespace std;

int W = 224,H = 224;//设置图片的宽度和高度 
#define PI 3.1415926
Bmp bmp(H,W); 

void init(){
	for (int i = 0 ; i < H; i ++){
        for (int j = 0 ; j < W ; j++ ){
        	//背景设置为白色 
            bmp.SetColor(i,j,Color(1,1,1)); 
        }
    }
}

//边界填充算法 
void BoundaryFill4(Vector2 seed,Color boundarycolor,Color newcolor);
//扫描线填充算法 
void ScanLineFill4(Vector2 O,Color oldcolor,Color newcolor);
//DDA画线算法 
void DDALine(int x0,int y0 , int x1 , int y1);
// Bresenham画线算法 
void Bresenhamline(int x0,int y0 , int x1 , int y1);
//有宽度的线 
void drawLineWidth(int x0,int y0 , int x1 , int y1,int w = 1); 
//反走样画线 
void antiAliasingLine(int x0,int y0 , int x1 , int y1);
//中点画圆算法 
void circlePoint(int x , int y , Vector2 OriginPoint = Vector2(0,0));
void MidPointCircle(  Vector2 OriginPoint , int r ,bool fill = false); 
//反走样画圆 
void putSymmetricalPixelCircle(Vector2 O , int x , int y , Color newColor , double r ); 
void antiAliasingCircle(Vector2 O, int r , Color value = Color(0,0,0) );

void genPoint(Vector2& v){

	int randx= rand()%W;
	int randy= rand()%H;
	v.x = randx;
	v.y = randy;
}
double calcDegree(Vector2 v1 , Vector2 v2){
	double a[2]={v1.x,v1.y},b[2]={v2.x,v2.y};
	double ab,a1,b1,cosr;
	ab=a[0]*b[0]+a[1]*b[1];
	a1=sqrt(a[0]*a[0]+a[1]*a[1]);
	b1=sqrt(b[0]*b[0]+b[1]*b[1]);
    cosr=ab/a1/b1;
	return acos(cosr)*180/PI;
}
//用于测试效果的函数 
void test(){
	//反走样画线 
	while(true){
		Vector2 pointTop; genPoint(pointTop);
		Vector2 point1  ; genPoint(point1);
		Vector2 point2  ; genPoint(point2);
		Vector2 v1 = point1-pointTop;
		Vector2 v2 = point2-pointTop;
		double dd = calcDegree(v1,v2);
		if(dd <= 20 || dd >= 160 || v1.Module() <= 25 || v2.Module() <= 25){
			continue;
		}
		else{
			antiAliasingLine(pointTop.x,pointTop.y,point1.x,point1.y);
			antiAliasingLine(pointTop.x,pointTop.y,point2.x,point2.y);
			//antiAliasingCircle(pointTop,1,Color(1,0,0));
			//cout << point1.x << " " << point1.y<<" " << point2.x << " " << point2.y<< " " <<dd<<endl;
			return;
		}
	}
}


string numToStr(int numn){
    stringstream ss;
    ss << numn;
    string s2;
    ss>>s2;
    return s2;
} 
int main() { 
	
	srand(time(0));
	
	for(int i =0 ; i < 1000 ; i++){
		if(i%100==0)
		cout << "i="<<i<<endl;
		//初始化 
		init();
		//测试 
		test();
		//输出到文件 
		string fileName="images/";
		fileName = fileName+numToStr(i)+".bmp";
		bmp.Output( fileName);	
	}
	
	return 0;
}

void DDALine(int x0,int y0 , int x1 , int y1){
	if (x0 > x1){
		swap(x0,x1);
		swap(y0,y1);	
	} 
	 float dx = x1-x0;
	 float dy = y1-y0;
	 int m = dx==0 ?1:0;
	 if (m){
	 	for (int i = y0 ; i <= y1 ; i++ ){
	 		bmp.SetColor(x0,i);
	 	}
	 }
	 else{
	 	float k = dy/dx;
	 	float j = y0;
	 	for (int i = x0 ; i <= x1 ; i++ ){
	 		bmp.SetColor(i,int(j+0.5));
	 		j += k;
	 	}
	 }
} 

void Bresenhamline(int x0,int y0 , int x1 , int y1){
	if (x0 > x1){
		swap(x0,x1);
		swap(y0,y1);	
	} 
	float dx = x1-x0;
	float dy = y1-y0;
	 int m = dx==0 ?1:0;
	 if (m){
	 	for (int i = y0 ; i <= y1 ; i++ ){
	 		bmp.SetColor(x0,i);
	 	}
	 }
	 else{
	 	int x = x0,y=y0;
	 	double k = dy/dx;
	 	float e = k-0.5;
	 	int i = 1;
	 	while(i <= dx ){	 		
	 		bmp.SetColor(x,y); 
	 		if (e >= 0){
	 			y++;
	 			e--;
	 		}
	 		else{
	 			i++;
	 			x++;
	 			e += k;
	 		}
	 	}
	 }
}

void circlePoint(int x , int y , Vector2 O){
	int S = 0; 
	bmp.SetColor( x+O.x , y+O.y);
	bmp.SetColor(-x+O.x , y+O.y);
	bmp.SetColor( x+O.x ,-y+O.y);
	bmp.SetColor(-x+O.x ,-y+O.y);
	bmp.SetColor( y+O.x , x+O.y);
	bmp.SetColor(-y+O.x , x+O.y);
	bmp.SetColor( y+O.x ,-x+O.y);
	bmp.SetColor(-y+O.x ,-x+O.y);
	if (S) {
		DDALine( x+O.x , y+O.y,-x+O.x , -y+O.y);
		DDALine( y+O.x , x+O.y,-y+O.x , -x+O.y);
		DDALine(-x+O.x , y+O.y, x+O.x , -y+O.y);
		DDALine( -y+O.x , x+O.y,y+O.x , -x+O.y);
	}
}

void MidPointCircle(  Vector2 O , int r , bool fill){
	if (r < 0) return;
	if (r == 0){
		bmp.SetColor(O.x,O.y);
		return;	
	} 
	int x=0,y=r;
	float d = 1.25 - r;
	circlePoint(x,y,O);
	while(x <= y ){
		if (d < 0){
			d += 2*x+3;
		}
		else{
			d += 2*(x-y)+5;
			y--;
		}
		x++;
		circlePoint(x,y,O);
	}	   
	//填充颜色 
	if (fill) ScanLineFill4(O,Color(1,1,1),Color(0,0,1));
}

void BoundaryFill4(Vector2 O,Color boundarycolor,Color newcolor){ 
	int x = O.x;
	int y = O.y;
	Color color = bmp.GetColor(x,y);
	if(color != newcolor && color != boundarycolor ){ 
  		bmp.SetColor( x , y , newcolor );
    	BoundaryFill4 (Vector2(x,y+1), boundarycolor,newcolor);
    	BoundaryFill4 (Vector2(x,y-1), boundarycolor,newcolor);
	    BoundaryFill4 (Vector2(x-1,y), boundarycolor,newcolor);
    	BoundaryFill4 (Vector2(x+1,y), boundarycolor,newcolor);
	}
}

void ScanLineFill4(Vector2 O,Color oldcolor,Color newcolor){    
	int x,y,xl,xr,i;
	bool spanNeedFill;
	stack <Vector2> stack;
	Vector2 pt;
	stack.push(O); 
	while( !stack.empty() ){  
		pt = stack.top();
		stack.pop();
 		y=pt.y;
   		x=pt.x;
   		//向右填充
   		while(bmp.GetColor(x,y) == oldcolor && x < H) {  
			bmp.SetColor(x,y,newcolor);
     		x++;
  		}
  		xr = x-1;
	  	x = pt.x-1;
  		//向左填充
	  	while(bmp.GetColor(x,y) == oldcolor && x > 0) {  
			bmp.SetColor(x,y,newcolor);
    		x--;
  		}
		xl = x+1;
		//处理上面一条扫描线
		x = xl;
		y = y+1;
		while(x<xr){  
			spanNeedFill=false;
    		while(bmp.GetColor(x,y) == oldcolor && x < H){ 
				spanNeedFill=true;
        		x++;
		    }

    		if(spanNeedFill ){ 
				pt.x=x-1;pt.y=y;
 		    	stack.push(pt);
    			spanNeedFill=false;
    		}
    		while(bmp.GetColor(x,y) != oldcolor && x<xr && x < H) x++;
		}//End of while(i<xr)
		//处理下面一条扫描线，代码与处理上面一条扫描线类似
		x = xl;
		y = y-2;
		while(x<xr){
			spanNeedFill=false;
    		while(bmp.GetColor(x,y) == oldcolor && x < H){ 
				spanNeedFill=true;
        		x++;
		    }

    		if(spanNeedFill ){ 
				pt.x=x-1;pt.y=y;
 		    	stack.push(pt);
    			spanNeedFill=false;
    		}
    		while(bmp.GetColor(x,y) != oldcolor && x<xr && x < H) x++;
		}
	}
}

void drawLineWidth(int x0,int y0 , int x1 , int y1,int w){
	int yAdd = -1,yDe = 0;
	bool add = false;
	while(w>0){
		w--;
		add = !add;
		if (add){
			yAdd++;
			Bresenhamline(x0,y0+yAdd,x1,y1+yAdd);
		} 
		
		else{
			yDe--;
			Bresenhamline(x0,y0+yDe,x1,y1+yDe);
		}
	}
	
} 

void putSymmetricalPixelCircle(Vector2 O , int x , int y , Color newColor , double r ){
	if(r<0)
		r=0;
	if(r>1)
		r=1;
	int cx= O.x,cy = O.y;	
	r = 1-r;
	Color bk=bmp.GetColor(cx+x,cy+y);	bmp.SetColor(cx+x,cy+y,newColor.lerpColor(bk,r));
	bk=bmp.GetColor(cx+y,cy+x);	bmp.SetColor(cx+y,cy+x,newColor.lerpColor(bk,r));
	bk=bmp.GetColor(cx+y,cy-x);	bmp.SetColor(cx+y,cy-x,newColor.lerpColor(bk,r));
	bk=bmp.GetColor(cx+x,cy-y);	bmp.SetColor(cx+x,cy-y,newColor.lerpColor(bk,r));
	bk=bmp.GetColor(cx-x,cy-y);	bmp.SetColor(cx-x,cy-y,newColor.lerpColor(bk,r));
	bk=bmp.GetColor(cx-y,cy-x);	bmp.SetColor(cx-y,cy-x,newColor.lerpColor(bk,r));
	bk=bmp.GetColor(cx-y,cy+x);	bmp.SetColor(cx-y,cy+x,newColor.lerpColor(bk,r));
	bk=bmp.GetColor(cx-x,cy+y);	bmp.SetColor(cx-x,cy+y,newColor.lerpColor(bk,r));
}
 
void antiAliasingCircle(Vector2 O, int r , Color value){	
	int cx = O.x , cy = O.y;
	int x   = 0;
	int y   = r;
	int d   = 1-r;
	int dE  = 3;
	int dSE = -(r<<1)+5;
	int dS  = 0;
	double a= 1.0 / ((r<<1) * 1.41421);
	putSymmetricalPixelCircle(O , x , y   , value , 1.0 );
	putSymmetricalPixelCircle(O , x , y+1 , value , 1-1.2/1.5 ); 
	putSymmetricalPixelCircle(O , x , y-1 , value , 1-1.2/1.5 );
	
	while(x < y-3){
		if(d<0){			
			d  += dE;
			dE += 2;
			dSE+= 2;
		}
		else{
			dS += 1-(y<<1);
			d  += dSE;
			dE += 2;
			dSE+= 4;
			y--;
		}
		dS += 1 + (x<<1);
		x++;
		putSymmetricalPixelCircle(O , x , y  , value , 1-a*abs(dS) );
		putSymmetricalPixelCircle(O , x , y+1, value , 1-a*(dS+(y<<1)+1) );
		putSymmetricalPixelCircle(O , x , y-1, value , 1+a*(dS-(y<<1)+1) );
	}
	// 处理2个八分圆的连接点
	if(d>-1){
		dS += 1-(y<<1);		
		y--;
	}
	dS += 1 + (x<<1);
	x++;
	if(x == y){		
		//四个主连接点
		double temp = a*abs(dS);
		
		Color bk = bmp.GetColor(cx+x , cy+y); 
		bmp.SetColor(Vector2(cx+x , cy+y) , value.lerpColor(bk,temp) );
		
		bk = bmp.GetColor(cx-x,cy+y); 
		bmp.SetColor(Vector2(cx-x , cy+y) , value.lerpColor(bk,temp));
		
		bk = bmp.GetColor(cx-x,cy-y); 
		bmp.SetColor(Vector2(cx-x , cy-y) , value.lerpColor(bk,temp));
		
		bk = bmp.GetColor(cx+x,cy-y); 
		bmp.SetColor(Vector2(cx+x , cy-y) , value.lerpColor(bk,temp));		
	
		putSymmetricalPixelCircle(O , x , y+1, value , 1-a*(dS+(y<<1)+1) );		
	}
	//x==y-1
	else  {
		//四个内圈个连接点
		double temp = 1.0+a*(dS-(y<<1)+1);
		temp = 1-temp; 
		Color bk=bmp.GetColor(cx+x,cy+x);bmp.SetColor(cx+x,cy+x,value.lerpColor(bk,temp));
		bk=bmp.GetColor(cx-x,cy+x);bmp.SetColor(cx-x,cy+x,value.lerpColor(bk,temp));
		bk=bmp.GetColor(cx-x,cy-x);bmp.SetColor(cx-x,cy-x,value.lerpColor(bk,temp));
		bk=bmp.GetColor(cx+x,cy-x);bmp.SetColor(cx+x,cy-x,value.lerpColor(bk,temp));

		//四个外圈连接点
		temp=a*(dS+(x<<1)+1);
		bk=bmp.GetColor(cx+y,cy+y);bmp.SetColor(cx+y,cy+y,value.lerpColor(bk,temp));
		bk=bmp.GetColor(cx+y,cy-y);bmp.SetColor(cx+y,cy-y,value.lerpColor(bk,temp));
		bk=bmp.GetColor(cx-y,cy-y);bmp.SetColor(cx-y,cy-y,value.lerpColor(bk,temp));
		bk=bmp.GetColor(cx-y,cy+y);bmp.SetColor(cx-y,cy+y,value.lerpColor(bk,temp));
		
		putSymmetricalPixelCircle(O , x , y  , value , 1-a*abs(dS) );
		putSymmetricalPixelCircle(O , x , y+1, value , 1-a*(dS+(y<<1)+1) );
	}
}

//反走样画线 
void antiAliasingLine(int x0,int y0 , int x1 , int y1){
	Color newColor = Color(0,0,0);

	if (x0 > x1){
		swap(x0,x1);
		swap(y0,y1);	
	} 
	float dx = x1-x0;
	float dy = y1-y0;
	int m = dx==0 ?1:0;
	
	if (m){
	 	for (int i = y0 ; i <= y1 ; i++ ){
	 		Color bt = bmp.GetColor(x0,i);
	 		bmp.SetColor(x0,i,newColor.lerpColor(bt, 0.1 )); 
	 		bt = bmp.GetColor(x0+1,i);
			bmp.SetColor(x0+1,i,newColor.lerpColor(bt, 0.3 ));
	 		bt = bmp.GetColor(x0-1,i); 
			bmp.SetColor(x0-1,i,newColor.lerpColor(bt,0.3));
	 	}
	}
	else{
	 	int x = x0,y=y0;
	 	float k = (float)dy/(float)dx;
		float e = -0.5;
		if(abs(k)<1){
			for (int i = 0;  i <= dx ; i++){
				float yR = k*(float)i+(float)y0;
				y = int(yR+0.5);
				float xi = abs(yR-y);
				Color bt = bmp.GetColor(x,y);
				
				bmp.SetColor( x , y , newColor );
				
				xi = 0.35*abs(yR-y-1);
				bt = bmp.GetColor(x,y+1);
				bmp.SetColor( x , y+1 , newColor.lerpColor(bt,xi) );
				xi = 0.35*abs(yR-y+1);
				bt = bmp.GetColor(x,y-1);
				bmp.SetColor( x , y-1 , newColor.lerpColor(bt,xi) );
				
				xi = 0.42*abs(yR-y-2);
				bt = bmp.GetColor(x,y+2);
				bmp.SetColor( x , y+2 , newColor.lerpColor(bt,xi) );
				xi = 0.42*abs(yR-y+2);
				bt = bmp.GetColor(x,y-2);
				bmp.SetColor( x , y-2 , newColor.lerpColor(bt,xi) );
				x++;
			}
		}
		else{
			if (y0 > y1){
				swap(x0,x1);
				swap(y0,y1);
				dy = -dy;
				y = y0;
			} 
			for (int i = 0;  i <= dy ; i++){
				float xR = (float)i/k+(float)x0;
				x = int(xR+0.5);
				float yi = abs(xR-x);
				Color bt = bmp.GetColor(x,y);
				
				bmp.SetColor( x , y , newColor );
				
				yi = 0.35*abs(xR-x-1);
				bt = bmp.GetColor(x+1,y);
				bmp.SetColor( x+1 , y , newColor.lerpColor(bt,yi) );
				yi = 0.35*abs(xR-x+1);
				bt = bmp.GetColor(y,x-1);
				bmp.SetColor( x-1 , y , newColor.lerpColor(bt,yi) );
				
				yi = 0.42*abs(xR-x-2);
				bt = bmp.GetColor(x+2,y);
				bmp.SetColor( x+2 , y , newColor.lerpColor(bt,yi) );
				yi = 0.42*abs(xR-x+2);
				bt = bmp.GetColor(x-2,y);
				bmp.SetColor( x-2 , y , newColor.lerpColor(bt,yi) );
				y++;
			}
		}
	 	
	 	
	}
}
