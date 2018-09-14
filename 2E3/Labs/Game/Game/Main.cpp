//This is a text based game in which you can be one of four races. You may encounter the other three.
//Each race has it's own stats that give it advantages/disadvantages.
//The end conditions are; death, escape, killing the final npc, only killing the first npc and killing no npcs (this is the "preferred" ending)
//Players can choose the path they take and what to do when they encounter an npc, as well as using a potion when below 50/100 health.
//The races are added to a linked list and then transferred to either the "player" or "npc" linked list.
//Each race has inheritance from the "races" class.
//The player inherits data from the inventory
//The scenarios are in the "Story" class and files are read in here.
#include <iostream>
#include<chrono>
#include <thread>
#include "character.h"
#include "npc.h"
#include "inventory.h"
#include "story.h"
#include "player.h"
#include "Screen.h"

using namespace std::chrono_literals; 
using namespace std::this_thread;
using std::chrono::system_clock;

int checkChoice(string);

void main() {
	screen.is_open();
	string choice;
	Character List;
	Inventory bag;
	Story tale;

	cout << "There are four races: " << endl;
	screen << "There are four races: " << endl;
	cout << "Elf \nHuman \nTroll \nWizard" << endl;
	screen << "Elf \nHuman \nTroll \nWizard" << endl;
	cout << "Please enter what race you would like to be: ";
	screen << "Please enter what race you would like to be: ";
	cin >> choice;
	screen << choice;
	while (checkChoice(choice) == -10) {
		cout << "Please enter a race: ";
		screen << "Please enter a race: ";
		cin >> choice;
		screen << choice;
	}
	if (checkChoice(choice) == 2) {
		cout << "You are an " << choice << "!" << endl;
		screen << "You are an " << choice << "!" << endl;
	}
	else {
		cout << "You are a " << choice << "!" << endl;
		screen << "You are a " << choice << "!" << endl;
	}
	Player user(choice, List.getHead());
	List.remove1(choice);

	NPC npc_1(List);
	List.remove2(List.getHead());
	
	NPC npc_2(List);
	List.remove2(List.getHead());
	
	NPC npc_3(List);
	List.remove2(List.getHead());

	sleep_for(1000ms);
	cout << "PLEASE NOTE!!" << endl;
	screen << "PLEASE NOTE!!" << endl;
	cout << "This game is case sensitive, from now on please use lowercase only!" << endl;
	screen << "This game is case sensitive, from now on please use lowercase only!" << endl;
	cout << "If you are asked for input again, you didn't enter a valid choice. Be creative!" << endl;
	screen << "If you are asked for input again, you didn't enter a valid choice. Be creative!" << endl;
	sleep_for(2000ms);
	cout << "GOOD LUCK!" << endl << endl;
	screen << "GOOD LUCK!" << endl << endl;

	tale.TellStory(user, npc_1, npc_2, npc_3, bag);

	cout << "END" << endl;
	screen << "END" << endl;

	screen.close();
	system("pause");
}

int checkChoice(string choice) {
	if (choice == "Human" || choice == "Troll" || choice == "Wizard")
		return 1;
	else if (choice == "Elf")
		return 2;
	else
		return -10;
}