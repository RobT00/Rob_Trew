#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

void readToSentinel (std::string words[]);
void count (std::string words[], int i);
void maxpos ();

using namespace std;

ifstream text ("H:\\Google Drive\\1E3\\Coding\\Lab\\Lab 10\\test.txt");
const int SIZE = 1000;

int main()
{
    ifstream text;
    //text.open();
    string words[SIZE];

    readToSentinel (words);


    //text.close();
    return 0;
}

void readToSentinel (string words[])
{
    int i = 0;
    text >> words[i];
    while (words[i] != "XXX")
    {
        count (words, i);
        i++;
        text >> words[i];
    }
}

void count (string words[], int i)
{

}

void maxpos ()
{

}
