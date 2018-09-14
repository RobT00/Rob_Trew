#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int SIZE = 70;
ifstream data;

void x();
void numbers(int nums[], int& maxi, int& mini);
void table (const int nums[], int counter, int maxi, int mini);

int main()
{
	int i, counter = 0, maxi, mini;
	int nums[SIZE];

	ifstream data;
	data.open ("\\Google Drive\\JF\\1E3\\Coding\\Lab\\Lab 9\\P9adata.txt");

	for (i = 0; i < SIZE; i++)
        data >> nums[i];

    numbers(nums, maxi, mini);

    cout << endl;
    cout << "TABLE: "<< endl;
    cout << setfill('-') << setw(SIZE+7) << "-" << endl;
    cout << setfill(' ');

    table(nums, counter, maxi, mini);
    x();

    cout << endl;
    cout << setfill('-') << setw(SIZE+7) << "-" << endl;
    cout << setfill(' ');
    cout << endl;
    data.close();

	return 0;
}

void numbers(int nums[], int& maxi, int& mini)
{
    int i = 0;
    maxi = nums[0];
    mini = nums[0];

    for (; i < SIZE; i++)
    {
        if (nums[i] > maxi)
            maxi = nums[i];
        else if (nums[i] < mini)
            mini = nums[i];
    }
}
void x()
{
    cout << "----|";
        for (int i = 0; i < SIZE/10; i++) //x-axis
            cout << "----+----|";
    cout << " |";
}

void table (const int nums[], int counter, int maxi, int mini)
{
    for (int i = maxi; i >= mini; i--) //y-axis
    {
        if (i == 0)
            break;
        cout << setw(2) << right << i << "  |";
//       cout << setw(4) << right;
//use setw(4) or "  |"
        for (int j = 0; j < SIZE; j++)
        {
            if (nums[j] >= i)
                cout << "*";
            else if (nums[j] == 0)
                cout << " ";
            else
                cout << " ";
        }
        cout << " |" << endl;
    }
}
