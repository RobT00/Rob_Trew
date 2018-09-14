#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void separate (string name[], int w_speed[], int j, string cat[]);
void counting (string cat[], int j);
string strongest (string name[], int w_speed[], int j);

const int SIZE = 100;
ifstream data;

int main()
{
    data.open ("H:\\Google Drive\\1E3\\Coding\\Lab\\Lab 8\\Storms.txt");

    string name[SIZE], cat[SIZE], strong;
    int i, j, w_speed[SIZE];

    j = 0;
    data >> name[j];
    while (name[j] != "XXX")
    {
        data >> w_speed[j];
        j++;
        data >> name[j];
    }
    separate(name, w_speed, j, cat);

    for (i = 0; i < j; i++)
    {
        if (name[i] != "0" && w_speed != 0)
            cout << name[i] << " " << w_speed[i] << " " << cat[i] << endl;
    }
    cout << endl;

    counting (cat, j);

    cout << endl;
    strong = strongest(name, w_speed, j);
    cout << "Strongest Storm: " << strong << endl;

    data.close();
    return 0;
}

void separate (string name[], int w_speed[], int j, string cat[])
{

    for (int i = 0; i < j; i++)
    {
        if (w_speed[i] < 178)
        {
            name[i] = "0";
            w_speed[i] = 0;
        }
        else if (w_speed[i] >= 178 && w_speed[i] < 210)
        {
            cat[i] = "Cat 3";
        }
        else if (w_speed[i] >= 210 && w_speed[i] < 250)
        {
            cat[i] = "Cat 4";
        }
        else if (w_speed[i] >= 250)
        {
            cat[i] ="Cat 5";
        }
    }
}

void counting (string cat[], int j)
{
    int cat_3, cat_4, cat_5;
    cat_3 = cat_4 = cat_5 = 0;
    for (int i = 0; i < j; i++)
    {
        if (cat[i] == "Cat 3")
            cat_3++;
        else if (cat[i] == "Cat 4")
            cat_4++;
        else if (cat[i] == "Cat 5")
            cat_5++;
    }
    cout << cat_3 << " Category 3 Storms" << endl;
    cout << cat_4 << " Category 4 Storms" << endl;
    cout << cat_5 << " Category 5 Storms" << endl;
}

string strongest (string name[], int w_speed[], int j)
{
    int str = w_speed[0];
    string strong;
    for (int i = 1; i < j; i++)
    {
        if (w_speed[i] > str)
        {
            str = w_speed[i];
            strong = name[i];
        }
    }
    return strong;
}
