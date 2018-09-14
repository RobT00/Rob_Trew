#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

void readToSentinel (std::string words[]);
void extractAllTerms (std::string words[], int used, std::string key_words[], int& terms2);
int search (std::string words[], int terms1, std::string key_words[], int terms2);
void count (std::string words[], int used, int counter[], int terms2, std::string key_words[]);
void over (const int counter[], const std::string key_words[], const int terms2);
void alpha (std::string terms[], const int j, int termst[]);
void maxpos (int counter[], int i, std::string key_words[]);

using namespace std;

ifstream text ("test.txt");
const int SIZE = 500;

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
    int used = 0, counter[SIZE], terms2;
    string key_words[SIZE];
    text >> words[used];
    while (words[used] != "XXX" && used < SIZE)
    {
        used++;
        text >> words[used];
    }
    if (used == SIZE)
    {
        cout << "TOO MANY TERMS, ARRAY FULL!!" << endl;
    }
    else
    {
        extractAllTerms (words, used, key_words, terms2);
        //cout << terms2 << endl;
        count (words, used, counter, terms2, key_words);
    }
}

void extractAllTerms (string words[], int used, string key_words[], int& terms2)
{
    int i, terms1;
    terms2 = 0;

    //for (i = 0; i < used; i++)
      //      key_words[i] = words[0];
    //key_words[0] = words[0];
    for (terms1 = 0; terms1 < used; terms1++)
    {
        //cout << key_words[terms2] << endl;
        //cout << words[terms1] << endl;
        if (words[terms1] != key_words[terms2])
        {
            i = search (words, terms1, key_words, terms2);
            //cout << i << endl;
            if (i < 0)
            {
                key_words[terms2] = words[terms1];
                //cout << key_words[terms2] << endl;
                //cout << 99 << endl;
                terms2++;
            }
        }
    }
    //cout << terms2 << endl;
    //cout << key_words[0] << endl << endl;
    //for (i = 0; i < terms2; i++)
    //    cout << key_words[i] << endl;
}

int search (string words[], int terms1, string key_words[], int terms2)
{
    int i = 0;
    //cout << key_words[terms2] << endl;
    //cout << key_words[terms2] << endl;
    while (i < terms2 && key_words[i] != words[terms1])
        i++;
    //cout << i << endl;
    if (i == terms2)
        return -1;
    else
        return 1;
}

void count (string words[], int used, int counter[], int terms2, string key_words[])
{
    int k = 0;
    //cout << used << endl;
    for (int j = 0; j < terms2; j++)
    {
        k = 0;
        //cout << k << endl;
        //cout << j << endl;
        //cout << key_words[j] << endl;
        //cout << "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBB" << endl;
        while (k < used)
        {
            //cout << "a" << endl;
            //cout << k << endl;
            if (key_words[j] == words[k])
                counter[j]++;
                //i = search (words, k, key_words, j);
                //cout << key_words[j] << " k " << endl;
                //cout << words[k] << " w " << endl;
                //cout << i << endl;
                //if (i > 0)
                //{
                //    counter[j]++;
                //    cout << counter[j] << endl;
                //}
            k++;
                //cout << k << endl;

            //cout << k << endl;
        }
        //cout << k << endl;
    }
    over (counter, key_words, terms2);
//    for (int i = 0; i < terms2; i++)
//    {
//        cout << counter[i] << " ";
//        cout << key_words[i] << endl;
//    }
}

void over (const int counter[], const string key_words[], const int terms2)
{
    string terms[terms2];
    int termst[terms2], j = 0;
    for (int i = 0; i < terms2; i++)
    {
        if (counter[i] > 5)
            {
                termst[j] = counter[i];
                terms[j] = key_words[i];
                j++;
            }
    }

    for (int i = 0; i < j; i++)
    {
        cout << terms[i] << " " << termst[i] << endl;
    }
//    alpha (terms, j, termst);
    maxpos (termst, j, terms);
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

void alpha (string terms[], const int j, int termst[])
{
    int k = 0, b[j], z;
    string a[j];
    a[0] = terms[0];
    for (int i = 1; i < j; i++)
    {
        if (terms[i] < terms[i-1])
        {
            a[k] = terms[i];
            b[k] = termst[i];
            k++;
            z = k;
            while (z < j)
            {
                a[z] = terms[z];
                b[z] = termst[z];
                z++;
            }
        }
//        else if (terms[i] > terms[i-1])
//        {
//            a[j-1] = terms[i];
//            b[j-1] = termst[i];
//        }
    }
    cout << endl;
    for (int i = 0; i < j; i++)
    {
        cout << a[i] << " " << b[i] << endl;
    }
}
