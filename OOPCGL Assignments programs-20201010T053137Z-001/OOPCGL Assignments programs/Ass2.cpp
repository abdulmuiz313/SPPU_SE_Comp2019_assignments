#include <iostream>
#include <graphics.h>
using namespace std;

static int LEFT=1,RIGHT=2,BOTTOM=4,TOP=8,xmin,xmax,ymin,ymax;
int getcode(int x,int y){
	int code = 0;
	//Perform Bitwise OR to get outcode
	if(y > ymax) code |=TOP;
	if(y < ymin) code |=BOTTOM;
	if(x < xmin) code |=LEFT;
	if(x > xmax) code |=RIGHT;
	return code;
}
int main()
{	
	int gd=DETECT,gm;
	initgraph(&gd,&gm,NULL);
	setcolor(RED);
	int x1,x2,y1,y2;
	cout<<"Enter window boundaries:";
	cout<<"Enter bottom left coordinates respectively:";
	cin>>xmin>>ymax;
	cout<<"Enter top right coordinates respectively:";
	cin>>xmax>>ymin;
	rectangle(xmin,ymin,xmax,ymax);
	cout<<"Enter x1,y1 respectively:";
	cin>>x1>>y1;
	cout<<"Enter x2,y2 respectively:";
	cin>>x2>>y2;
	line(x1,y1,x2,y2);
	delay(5000);
	int outcode1=getcode(x1,y1), outcode2=getcode(x2,y2);
	int accept = 0; 
	while(1){
		float m =(float)(y2-y1)/(x2-x1);
		//Both points inside. Accept line
		if(outcode1==0 && outcode2==0){ 
			accept = 1;
			break;
		}
		//AND of both codes != 0.Line is outside. Reject line
		else if((outcode1 & outcode2)!=0){
			break;
		}else{
			int x,y;
			int temp;
			//Decide if point1 is inside, if not, calculate intersection
			if(outcode1==0) 
				temp = outcode2;
			else 
				temp = outcode1;
			//Line clips top edge
			if(temp & TOP){
				x = x1+ (ymax-y1)/m;
				y = ymax;
			}
			else if(temp & BOTTOM){ 	//Line clips bottom edge
				x = x1+ (ymin-y1)/m;
				y = ymin;
			}else if(temp & LEFT){ 	//Line clips left edge
				x = xmin;
				y = y1+ m*(xmin-x1);
			}else if(temp & RIGHT){ 	//Line clips right edge
				x = xmax;
				y = y1+ m*(xmax-x1);
			}	
			//Check which point we had selected earlier as temp, and replace its co-ordinates
			if(temp == outcode1){ 
				x1 = x;
				y1 = y;
				outcode1 = getcode(x1,y1);
			}else{
				x2 = x;
				y2 = y;
				outcode2 = getcode(x2,y2);
			}
		}
	}
	cleardevice();
	cout<<"After clipping:";
	if(accept){
		line(x1,y1,x2,y2);
		rectangle(xmin,ymin,xmax,ymax);
		delay(5000);
		}
	getch();
	closegraph();
	return 0;
}
/*TEST COORDINATE
200
400
400
200
40
40
350
250*/
