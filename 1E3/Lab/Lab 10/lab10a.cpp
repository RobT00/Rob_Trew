#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

void readToSentinel (std::string words[]);
void count (std::string words[], int counter[], int i, std::string key_words[]);
void maxpos (int counter[], int i, std::string key_words[]);
const int SIZE = 1000;

int main (){
	
	string words [SIZE];
	readToSentinel (words);
	return 0;
}



void readToSentinel (std::string words[]){
	
	int i = 0, counter[SIZE];
	string key_words[SIZE];
	cin >> words[i];
	while (words[i] != "XXX"){
		
		if (words[i] == "array")
			key_words [0] = words[i];
		if (words[i] == "compute")
			key_words [1] = words[i];
		if (words[i] == "declare")
			key_words [2] = words[i];
		if (words[i] == "define")
			key_words [3] = words[i];
		if (words[i] == "for")
			key_words [4] = words[i];
		if (words[i] == "function")
			key_words [5] = words[i];
		if (words[i] == "if")
			key_words [6] = words[i];
		if (words[i] == "loop")
			key_words [7] = words[i];
		if (words[i] == "variable")
			key_words [8] = words[i];
		if (words[i] == "while")
			key_words [9] = words[i];
		i++;
		cin >> words[i];
	}
	count (words, counter, i, key_words);
}
	

void count (std::string words[], int counter[], int i, std::string key_words[]) {
	
	for (int j = 0; j <= 9; j++)
		counter [j] = 0;
		
	for (int j = 0; j < i; j++) {
		
		if (words[j] == "array")
			counter[0]++;
		if (words[j] == "compute")
			counter[1]++;
		if (words[j] == "declare")
			counter[2]++;
		if (words[j] == "define")
			counter[3]++;
		if (words[j] == "for")
			counter[4]++;
		if (words[j] == "function")
			counter[5]++;
		if (words[j] == "if")
			counter[6]++;
		if (words[j] == "loop")
			counter[7]++;
		if (words[j] == "variable")
			counter[8]++;
		if (words[j] == "while")
			counter[9]++;	
	}
	
	
	cout << "array " << counter[0] << endl; 
	cout << "compute " << counter[1] << endl; 
	cout << "declare " << counter[2] << endl; 
	cout << "define " << counter[3] << endl; 
	cout << "for " << counter[4] << endl; 
	cout << "function " << counter[5] << endl; 
	cout << "if " << counter[6] << endl; 
	cout << "loop " << counter[7] << endl; 
	cout << "variable " << counter[8] << endl; 
	cout << "while " << counter[9] << endl; 
		
	maxpos (counter, i, key_words);
}
		


void maxpos (int counter[], int i, std::string key_words[]) {
	
	int maxi = counter[0];
	string maxw;
	for (int j = 0; j < i; j++){
		if (counter[j] >= maxi){
			maxi = counter[j];
			maxw = key_words[j];
		}
	}
	
	cout <<	"\nThe term that appeared the most was: ";
	cout << maxw << ", it appeared " << maxi << " times" << endl;
}
		
		
		
		



