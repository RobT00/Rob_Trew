#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

double tri_type ( double x1, double y1, double x2, double y2, double x3, double y3);
double dist (double x1, double y1, double x2, double y2);
bool veryClose (double d1, double d2);

int main () {
	int type = 0, yes = 0;
	double x1,y1,x2,y2,x3,y3;
	cout << "Enter Coordinates of First point:";
	cin >> x1 >> y1;
	cout << "Enter Coordinates of Second Point:";
	cin >> x2 >> y2;
	cout << "Enter Coordinates of Third Point:";
	cin >> x3 >> y3;
	
	type=tri_type(x1,y1,x2,y2,x3,y3);
	cout << std::fixed << setprecision(0);
	if (type==3)
		cout << "Equilateral";
	else if (type==2)
		cout << "Isosceles";
	else
		cout << "Scalene";
	cout << endl;		
	return 0;	
}

double dist (double x1, double y1, double x2, double y2){
	double stepx, stepy, tot;
	stepx = pow((x2-x1),2);
	stepy = pow((y2-y1),2);
	tot = sqrt(stepx + stepy);
	return tot;
}

bool veryClose (double d1, double d2){
	return (fabs(d1-d2)<0.0001);
}

double tri_type ( double x1, double y1, double x2, double y2, double x3, double y3){
	double d1, d2, d3;
	int yes=0;
	d1=dist(x1,y1,x2,y2);
	d2=dist(x2,y2,x3,y3);
	d3=dist(x1,y1,x3,y3);
	if (veryClose(d1,d2) && veryClose(d2,d3))
		return 3;
	if (veryClose(d2,d3) || veryClose(d2,d1) || veryClose(d1,d3))
		return 2;
	return 0;
}
		