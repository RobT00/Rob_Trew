#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

void graph (int values[]);
void x();

const int XSIZE = 70;
const int YSIZE = 20;

int main()
{
	int values[XSIZE]; 
	
	for (int i = 0; i < XSIZE; i++)
	{
		cin >> values[i];
	}
	
	graph(values);
	
	x();
	cout << endl;
	return 0;	
}

void graph (int values[])
{
	int CurYPos = XSIZE;
	int CurXPos;
	
	for (int i = YSIZE; i > 0; i--)
	{
		CurXPos = 0;
		if (i >= 10)
			cout << i << setw(3) << " ";
		else if (i < 10 && i > 0)
			cout << " " << i << setw(3) << " ";
		for (int j = 0; j < XSIZE-1; j++)
		{
			if (values[CurXPos] == 0)
				cout << " ";
			else if (values[CurXPos] >= i)
				cout << "*";
			else 
				cout << " ";
			CurXPos++;
		}
		cout << endl;
	} 
}

void x ()
{
	cout << "----|";
		for (int i = 0; i < XSIZE/10; i++)
			cout << "----+----|";	
}