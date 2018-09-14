#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

void readToSentinel (std::string words[]);
void count (std::string words[], int counter[], int i, std::string key_words[]);
void maxpos (int counter[], int i, std::string key_words[]);

using namespace std;

ifstream text ("test.txt");
const int SIZE = 1000;

int main()
{
    ifstream text;
    //text.open();
    string words[SIZE] = {"array", "compute", "declare", "define", "for", "function", "if", "loop", "variable", "while"};

    readToSentinel (words);

    //text.close();
    return 0;
}

void readToSentinel (string words[])
{
    int i = 0, counter[SIZE];
    string key_words[SIZE];
    text >> words[i];
    while (words[i] != "XXX")
    {
        if (words[i] == "array")
        {
            key_words[0] = words[i];
        }
        else if (words[i] == "compute")
        {
            key_words[1] = words[i];
        }
        else if (words[i] == "declare")
        {
            key_words[2] = words[i];
        }
        else if (words[i] ==  "define")
        {
            key_words[3] = words[i];
        }
        else if (words[i] == "for")
        {
            key_words[4] = words[i];
        }
        else if (words[i] == "function")
        {
            key_words[5] = words[i];
        }
        else if (words[i] == "if")
        {
            key_words[6] = words[i];
        }
        else if (words[i] == "loop")
        {
            key_words[7] = words[i];
        }
        else if (words[i] == "variable")
        {
            key_words[8] = words[i];
        }
        else if (words[i] == "while")
        {
            key_words[9]= words[i];
        }
        i++;
        text >> words[i];
    }
    count (words, counter, i, key_words);
}

void count (string words[], int counter[], int i, string key_words[])
{
    counter[0] = counter[1] = counter[2] = counter[3] = counter[4] = counter[5] = counter[6] =counter[7] = counter[8] = counter[9] = 0;
    for (int j = 0; j < i; j++)
    {
        if (words[j] == "array")
        {
            counter[0]++;
        }
        else if (words[j] == "compute")
        {
            counter[1]++;
        }
        else if (words[j] == "declare")
        {
            counter[2]++;
        }
        else if (words[j] ==  "define")
        {
            counter[3]++;
        }
        else if (words[j] == "for")
        {
            counter[4]++;
        }
        else if (words[j] == "function")
        {
            counter[5]++;
        }
        else if (words[j] == "if")
        {
            counter[6]++;
        }
        else if (words[j] == "loop")
        {
            counter[7]++;
        }
        else if (words[j] == "variable")
        {
            counter[8]++;
        }
        else if (words[j] == "while")
        {
            counter[9]++;
        }
    }
    cout << "Array " << counter[0] << endl;
    cout << "Compute " << counter[1] << endl;
    cout << "Declare " << counter[2] << endl;
    cout << "Define " << counter[3] << endl;
    cout << "For " << counter[4] << endl;
    cout << "Function " << counter[5] << endl;
    cout << "If " << counter[6] << endl;
    cout << "Loop " << counter[7] << endl;
    cout << "Variable " << counter[8] << endl;
    cout << "While " << counter[9] << endl;

    maxpos(counter, i, key_words);
}

void maxpos (int counter[], int i, string key_words[])
{
    int maxi = counter[0];
    string maxw;
    for (int j = 0; j < i; j++)
    {
        if (counter[j] >= maxi)
        {
            maxi = counter[j];
            maxw = key_words[j];
        }
    }
    cout << "\nThe term that appeared the most was: ";
    cout << maxw << ", it appeared " << maxi << " times" << endl;
}
