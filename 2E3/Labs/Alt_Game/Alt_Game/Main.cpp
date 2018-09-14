#include <iostream>
#include <string>
#include "play.h"

using namespace std;

void main() {
	cout << "Welcom to the Quiz!" << endl;
	
	Play game;

	game.game();

	game.end();
}