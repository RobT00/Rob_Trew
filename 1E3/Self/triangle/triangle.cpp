#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

int triangleType(double x1, double y1, double x2, double y2, double x3, double y3);
double distance(double x1, double x2, double y1, double y2);
bool veryClose(double x, double y);

int main()
{
    double x1, y1, x2, y2, x3, y3;
    int type = 0, yes = 0;
    cout << "Enter x and y coordinates of first vertex (separated by a space): ";
    cin >> x1 >> y1;
    cout << "Enter x and y coordinates of second vertex: ";
    cin >> x2 >> y2;
    cout << "Enter x and y coordinates of third vertex: ";
    cin >> x3 >> y3;

    cout << endl;

    type = triangleType(x1, y1, x2, y2, x3, y3);
    cout << std::fixed << setprecision(0);
    if (type == 3)
       cout << "The triangle is an Equilateral Triangle" << endl;
    else if (type == 2)
       cout << "The triangle is an Isosceles Triangle" << endl;
    else
       cout << "The triangle is a Scalene Triangle" << endl;

    return 0;
}

double distance(double x1, double x2, double y1, double y2) {
    double step1_x = pow((x2-x1),2);
    double step1_y = pow((y2-y1), 2);
    double step2 = sqrt(step1_x + step1_y);

    return step2;
}

bool veryClose(double d1, double d2) {
    return (fabs (d1-d2) < 0.3);
}

int triangleType(double x1, double y1, double x2, double y2, double x3, double y3){
    int yes = 0;
    double d1, d2, d3;

    d1 = distance(x1, y1, x2, y2);
    d2 = distance(x2, y2, x3, y3);
    d3 = distance(x1, y1, x3, y3);

    if (veryClose (d1, d2))
        yes++;

    if (veryClose (d2, d3))
        yes++;

    if (veryClose (d1, d3))
        yes++;

    if (yes == 2)
        return 2;
        //isosceles
    else if (yes == 3)
        return 3;
        //equilateral
    else
        return 0;
        //scalene
}
