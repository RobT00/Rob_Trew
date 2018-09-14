#include "play.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int Play::score = 0;
int Play::lines = 0;

Play::Play() {
	quiz.open("Questions.txt");
	if (quiz.is_open()) {
		while (getline(quiz, line)) 
			lines++;
		lines = lines / 2;
		quiz.close();
		questions = new string[lines];
		answers = new string[lines];
		quiz.open("Questions.txt");
		for (int i = 0; i < lines; i++) {
			getline(quiz, line);
			questions[i] = line;
			getline(quiz, line);
			answers[i] = line;
		}
	}
	quiz.close();
}

void Play::printQ() {
	for (int i = 0; i < lines; i++)
		cout << questions[i] << endl;
}

void Play::printA() {
	for (int i = 0; i < lines; i++)
		cout << answers[i] << endl;
}

void Play::game() {
	int x = 1;
	string action = "";
	cout << "The quiz will now begin, please enter 'EXIT' to leave the game, otherwise the game will end after all questions are finished" << endl;
	for (x; x < lines+1; x++) {
		cout << "Question " << x << ":" << endl;
		cout << questions[x - 1] << endl;
		cin >> action;
		if (action == "EXIT")
			break;
		if (compare(action, answers[x - 1])) {
			cout << "Correct!" << endl;
			score += 1;
			cout << "Score: " << score << endl;
		}
		else {
			cout << "Incorrect!" << endl;
			cout << "Correct answer: " << endl;
			cout << answers[x - 1] << endl;
		}
		cout << endl;
	}
}

void Play::end() {
	cout << "\nThe Quiz has ended! Thanks for playing" << endl;
	cout << "Your final score was: " << score << "/" << lines << endl;
}