#include <iostream>
#include <string>
#include <ctime>
#include<chrono>
#include <thread>
#include "story.h"
#include "Screen.h"

using namespace std::chrono_literals;
using namespace std::this_thread;
using std::chrono::milliseconds;

int Story::kills = 0;
bool Story::dead = false;
bool Story::win = false;

Story::Story() {
	
}

void Story::TellStory(Player user, NPC npc_1, NPC npc_2, NPC npc_3, Inventory bag) {
	cout << "Your adventure begins..." << endl;
	screen << "Your adventure begins..." << endl;
	cout << "You are: " << endl;
	screen << "You are: " << endl;
	user.printRace();
	screen << user.getRace() << endl;
	sleep_for(20ms);

	cout << "\nYou have: " << endl;
	screen << "\nYou have: " << endl;
	bag.print();

	cout << "\nYou may encounter: " << endl;
	screen << "\nYou may encounter: " << endl;
	cout << "NPC 1: " << endl;
	screen << "NPC 1: " << endl;
	npc_1.printRace();
	screen << npc_1.getRace() << endl;
	sleep_for(10ms);
	cout << "\nNPC 2: " << endl;
	screen << "\nNPC 2: " << endl;
	npc_2.printRace();
	screen << npc_2.getRace() << endl;
	sleep_for(10ms);
	cout << "\nNPC 3: " << endl;
	screen << "\nNPC 3: " << endl;
	npc_3.printRace();
	screen << npc_3.getRace() << endl;
	cout << endl;
	sleep_for(20ms);
	output.open ("Intro.txt");
	if (output.is_open())
		printText(output, user);

	cin >> action;
	screen << action;
	while ((action != "left") && (action != "right") && (action != "ahead")) {
		cout << "Please enter a valid choice: ";
		screen << "Please enter a valid choice: ";
		cin >> action;
		screen << action;
	}
	output.close();
	int chance = user.getRand(3);
	if (chance == 1) {
		if (action == "left")
			Scenario1(user, npc_1, bag);
		if (dead)
			return;
		if (action == "right")
			Scenario2(user, npc_1, bag);
		if (dead)
			return;
		if (action == "ahead")
			Scenario3(user, npc_2, npc_3, bag, success);
		}
	else if (chance == 2) {
		if (action == "left")
			Scenario1(user, npc_2, bag);
		if (dead)
			return;
		if (action == "right")
			Scenario2(user, npc_2, bag);
		if (dead)
			return;
		if (action == "ahead")
			Scenario3(user, npc_1, npc_3, bag, success);
		}
	else {
		if (action == "left")
			Scenario1(user, npc_3, bag);
		if (dead)
			return;
		if (action == "right")
			Scenario2(user, npc_3, bag);
		if (dead)
			return;
		if (action == "ahead")
			Scenario3(user, npc_2, npc_1, bag, success);
		}
}

void Story::Scenario1(Player& user, NPC& npc_1, Inventory& bag) {
	output.open ("Scenario1//1A.txt");
	
	if (output.is_open())
		printText(output, user);

	cout << "You see the " << npc_1.getRace() << " standing there" << endl;
	screen << "You see the " << npc_1.getRace() << " standing there" << endl;
	cout << "What do you do? ";
	screen << "What do you do? ";
	cin >> action;
	screen << action;
	while ((action != "attack") && (action != "talk")) {
		cout << "What do you do? ";
		screen << "What do you do? ";
		cin >> action;
		screen << action;
	}
	output.close();

	if (action == "talk") {
		talk(user, npc_1, success, bag);
		if (checkDead()) {
			endGame(user, bag);
			return;
		}
	}

	if (action == "attack") {
		battle(user, npc_1, bag);
		if (checkDead()) {
			endGame(user, bag);
			return;
		}
		output.open("Scenario1//1B.txt");
		if (output.is_open()) {
			while (getline(output, line)) {
				cout << line << endl;
				sleep_for(200ms);
			}
		}
		output.close();
		cin >> action;
		screen << action;
		while ((action != "right") && (action != "ahead")) {
			if (action == "left") {
				cout << "You have already gone this way!" << endl;
				screen << "You have already gone this way!" << endl;
			}
			cout << "Please enter a valid choice: ";
			screen << "Please enter a valid choice: ";
			cin >> action;
			screen << action;
		}
		return;
	}
	output.open("Scenario1//1C.txt");
	if (output.is_open()) {
		cout << "You follow the " << npc_1.getRace() << " back the way you came." << endl;
		screen << "You follow the " << npc_1.getRace() << " back the way you came." << endl;
		printText(output, user);
	}
	output.close();
	action = "ahead";
	if (user.getRace() == "Wizard") {
		bag.foundStaff();
		bag.addGold(5);
		bag.addPotion(1);
	}
	else if (user.getRace() == "Elf") {
		bag.foundBow();
		bag.addGold(5);
		bag.addPotion(1);
	}
	else if (user.getRace() == "Human") {
		bag.foundSword();
		bag.addGold(10);
		bag.addPotion(2);
	}
	else {
		bag.foundSword();
		bag.addGold(5);
		bag.addPotion(1);
	}
	return;
}

void Story::Scenario2(Player& user, NPC& npc_1, Inventory& bag) {
	output.open("Scenario2//2A.txt");
	if (output.is_open()) 
		printText(output, user);

	output.close();
	cin >> action;
	screen << action;
	while ((action != "backtrack") && (action != "continue")) {
		cout << "Please enter a valid choice: ";
		screen << "Please enter a valid choice: ";
		cin >> action;
		screen << action;
	}
	if (action == "backtrack") {
		output.open("Scenario2//2C.txt");
		if (output.is_open()) 
			printText(output, user);
	
		output.close();
		cout << "You decide that there is no point to go down the left path, over the body of the " << npc_1.getRace() << endl;
		screen << "You decide that there is no point to go down the left path, over the body of the " << npc_1.getRace() << endl;
		cout << "You find a potion on the body" << endl;
		screen << "You find a potion on the body" << endl;
		cout << "You go into the cave, down the centre path, that lies ahead of you..." << endl;
		screen << "You go into the cave, down the centre path, that lies ahead of you..." << endl;
		bag.addPotion(1);
		action = "ahead";
		return;
	}
	else if (action == "continue") {
		output.open("Scenario2//2B.txt");
		if (output.is_open()) 
			printText(output, user);

		endGame(user, bag);
	}
}

void Story::Scenario3(Player& user, NPC& npc_2, NPC& npc_3, Inventory& bag, bool& success) {
	if (success != true) {
		output.open("Scenario3\\3A.txt");
		if (output.is_open()) 
			printText(output, user);

		cout << "You turn and find yourself face-to-face with the " << npc_2.getRace() << endl;
		screen << "You turn and find yourself face-to-face with the " << npc_2.getRace() << endl;
		cout << "What do you do? ";
		screen << "What do you do? ";
		cin >> action;
		screen << action;
		while ((action != "attack") && (action != "talk")) {
			cout << "What do you do? ";
			screen << "What do you do? ";
			cin >> action;
			screen << action;
		}
		output.close();
		if (action == "talk") {
			talk(user, npc_2, success, bag);
			if (checkDead()) {
				endGame(user, bag);
				return;
			}
		}

		if (action == "attack") {
			battle(user, npc_2, bag);
			if (checkDead()) {
				endGame(user, bag);
				return;
			}
		}
		if (success == true) {
			cout << "The " << npc_2.getRace() << " slowly nods it's head and turns away" << endl;
			screen << "The " << npc_2.getRace() << " slowly nods it's head and turns away" << endl;
			output.open("Scenario3\\3C.txt");
			if (output.is_open()) 
				printText(output, user);

			if (user.getRace() == "Human") {
				cout << "You find a potion and some gold near where you landed" << endl;
				screen << "You find a potion and some gold near where you landed" << endl;
				bag.addGold(5);
				bag.addPotion(1);
			}
			output.close();
		}
		else {
			output.open("Scenario3\\3D.txt");
			if (output.is_open()) 
				printText(output, user);
	
			output.close();
			user.setHealth((user.getHealth() - 10));
			if (user.getHealth() <= 0) {
				dead = true;
				endGame(user, bag);
				return;
			}
			else {
				if (bag.getPotion() > 0)
					heal(user, bag);
			}
		}
	}
	output.open("Scenario3\\3B.txt");
	if (output.is_open()) 
		printText(output, user);

	output.close();
	cout << "As you get closer, you see the " << npc_3.getRace() << " more clearly" << endl;
	screen << "As you get closer, you see the " << npc_3.getRace() << " more clearly" << endl;
	cout << "It appears to be guarding something..." << endl;
	screen << "It appears to be guarding something..." << endl;
	cout << "As you get close, it turns its head and looks at you" << endl;
	screen << "As you get close, it turns its head and looks at you" << endl;
	cout << "What do you do? ";
	screen << "What do you do? ";
	cin >> action;
	screen << action;
	while ((action != "attack") && (action != "talk")) {
		cout << "What do you do? ";
		screen << "What do you do? ";
		cin >> action;
		screen << action;
	}
	if (action == "talk") {
		talk(user, npc_3, success, bag);
		if (checkDead()) {
			endGame(user, bag);
			return;
		}
	}
	if (action == "attack") {
		battle(user, npc_3, bag);
		if (checkDead()) {
			endGame(user, bag);
			return;
		}
		else {
			output.open("Scenario3\\3F.txt");
			if (output.is_open())
				printText(output, user);

			output.close();
		}
	}

	else if (success == true) {
		cout << "The " << npc_3.getRace() << " smiles, almost knowingly...";
		screen << "The " << npc_3.getRace() << " smiles, almost knowingly...";
		output.open ("Scenario3\\3E.txt");
		if (output.is_open()) {
			printText(output, user);
		}
		output.close();
		bag.addGold(10000);
		if (kills == 0) {
			output.open ("Scenario3\\31.txt");
			if (output.is_open()) 
				printText(output, user);

			win = true;
			output.close();
		}
	}

	endGame(user, bag);
	return;
}

void Story::battle(Player& user, NPC& npc, Inventory& bag) {
	int user_attack, npc_attack, user_defend, npc_defend, damage, chance, user_health, npc_health;
	cout << "You rush in to battle the " << npc.getRace() << "!" << endl;
	screen << "You rush in to battle the " << npc.getRace() << "!" << endl;

	while (!checkDead()) {
		cout << "Player Health: " << user.getHealth() << "/100" << endl;
		screen << "Player Health: " << user.getHealth() << "/100" << endl;
		cout << npc.getRace() << " Health: " << npc.getHealth() << "/100" << endl;
		screen << npc.getRace() << " Health: " << npc.getHealth() << "/100" << endl;
		
		if ((user.getHealth() < 50) && (bag.getPotion() > 0))
			heal(user, bag);

		user_health = user.getHealth();
		npc_health = npc.getHealth();

		if (user.getIQ() > npc.getIQ()) { //user attacks first
			user_attack = ((user.getAgility() * 0.2) + (user.getAttack() * 0.6) + (user.getStrength() * 0.2));
			npc_defend = ((npc.getAgility() * 0.55) + (npc.getDefend() * 0.45));
			if ((user.getSpecial() == "Magic") && (bag.checkStaff())) {//User Wizard Staff check
				user_attack += 10;
			}
			else if ((bag.checkBow()) && (user.getSpecial() == "Dodge")) {//User Elf Bow Check
				user_attack += 15;
			}
			else if ((bag.checkSword()) && (user.getRace() == "Human")) {//User Human sword check
				user_attack += 10;
			}
			if (npc.getSpecial() == "Ironskin") {//NPC Troll check
				npc_defend += 5;
				damage = user_attack - (npc_defend * 0.7);
			}
			else if (npc.getSpecial() == "Dodge") { //NPC Elf check
				chance = npc.getRand(100);
				if (chance > 50) {
					damage = user_attack / 4;
				}
				else
					damage = user_attack - (npc_defend * 0.7);
			}
			else
				damage = user_attack - (npc_defend * 0.7);

			//user ATTACK!
			if (damage < 0)
				damage = fabs(damage);

			chance = npc.getRand(50);
			if (chance >= 48)
				npc_health -= (2 * damage);

			else if (chance < 3)
				npc_health -= (0.5 * damage);

			else
				npc_health -= damage;

			cout << "Damage to " << npc.getRace() << ": " << damage << endl;
			screen << "Damage to " << npc.getRace() << ": " << damage << endl;
			npc.setHealth(npc_health);
			if (npc_health <= 0)
				return;

			npc_attack = ((npc.getAgility() * 0.19) + (npc.getAttack() * 0.61) + (npc.getStrength() * 0.2));
			user_defend = ((user.getAgility() * 0.5) + (user.getDefend() * 0.5));
			if ((user.getSpecial() == "Magic") && (bag.checkStaff())) {//User Wizard Staff check
				user_defend += 10;
			}
			else if (user.getSpecial() == "Ironskin") {//User Troll check
				npc_defend += 20;
				damage = npc_attack - (user_defend * 0.8);
			}
			else if (user.getSpecial() == "Dodge") {//User Elf check
				chance = user.getRand(100);
				if (chance > 50)
					damage = user_attack / 4;
			}
			else
				damage = user_attack - (user_defend * 0.8);
			//MPC ATTACK!
			if (damage < 0)
				damage = fabs(damage);

			chance = user.getRand(50);
			if (chance >= 48)
				user_health -= 2 * damage;

			else if (chance < 3)
				user_health -= 0.5* damage;

			else
				user_health -= damage;

			cout << "Damage to user: " << damage << endl;
			screen << "Damage to user: " << damage << endl;
			user.setHealth(user_health);
			if (user.getHealth() <= 0) {
				dead = true;
				return;
			}
		}
		else { //npc attacks first
			npc_attack = ((npc.getAgility() * 0.39) + (npc.getAttack() * 0.61));
			user_defend = ((user.getAgility() * 0.5) + (user.getDefend() * 0.5));

			if ((user.getSpecial() == "Magic") && (bag.checkStaff())) //User Wizard Staff check
				user_defend += 10;

			else if (user.getSpecial() == "Ironskin") {//User Troll check
				user_defend += 20;
				damage = npc_attack - (user_defend * 0.8);
			}
			else if (user.getSpecial() == "Dodge") {//User Elf check
				chance = user.getRand(100);
				if (chance > 50)
					damage = npc_attack / 4;
				else
					damage = npc_attack - (user_defend * 0.8);
			}
			else
				damage = npc_attack - (user_defend * 0.8);
			//MPC ATTACK!
			if (damage < 0)
				damage = fabs(damage);

			chance = user.getRand(50);
			if (chance >= 48)
				user_health -= 2 * damage;

			else if (chance < 3)
				user_health -= 0.5* damage;

			else
				user_health -= damage;

			cout << "Damage to user: " << damage << endl;
			screen << "Damage to user: " << damage << endl;
			user.setHealth(user_health);
			if (user.getHealth() <= 0) {
				dead = true;
				return;
			}

			user_attack = ((user.getAgility() * 0.4) + (user.getAttack() * 0.6));
			npc_defend = ((npc.getAgility() * 0.55) + (npc.getDefend() * 0.45));

			if ((user.getSpecial() == "Magic") && (bag.checkStaff())) //User Wizard Staff check
				user_attack += 10;

			else if ((bag.checkBow()) && (user.getSpecial() == "Dodge")) //User Elf Bow Check
				user_attack += 15;

			else if ((bag.checkSword()) && (user.getRace() == "Human")) //User Human sword check
				user_attack += 10;

			if (npc.getSpecial() == "Ironskin") {//NPC Troll check
				npc_defend += 5;
				damage = user_attack - (npc_defend * 0.7);
			}
			else if (npc.getSpecial() == "Dodge") { //NPC Elf check
				chance = npc.getRand(100);
				if (chance > 50)
					damage = user_attack / 4;
				else
					damage = user_attack - (npc_defend * 0.7);
			}
			else
				damage = user_attack - (npc_defend * 0.7);
			//user ATTACK!
			if (damage < 0)
				damage = fabs(damage);

			chance = npc.getRand(50);
			if (chance >= 48)
				npc_health -= 2 * damage;

			else if (chance < 3)
				npc_health -= 0.5* damage;

			else
				npc_health -= damage;

			cout << "Damage to " << npc.getRace() << ": " << damage << endl;
			screen << "Damage to " << npc.getRace() << ": " << damage << endl;
			npc.setHealth(npc_health);
			if (npc.getHealth() <= 0)
				break;
		}
	}
	kills++;
	cout << "You killed the ";
	screen << "You killed the " << npc.getRace();
	npc.printRace();

	if (bag.getPotion() > 0)
		heal(user, bag);
}

void Story::talk(Player& user, NPC& npc, bool& success, Inventory& bag) {
	int user_talk, npc_talk;
	user_talk = ((user.getIQ() * 0.4) + (user.getCharisma() * 0.6));
	npc_talk = ((npc.getIQ() * 0.8) + (npc.getCharisma() * 0.2));

	cout << "You attempt to talk to the " << npc.getRace() << endl;
	screen << "You attempt to talk to the " << npc.getRace() << endl;

	if ((user_talk - npc_talk) >= 13) {
		success = true;
		return;
	}
	else if ((npc_talk - user_talk) >= 20) {
		success = false;
		cout << "Talking didn't go so well..." << endl;
		screen << "Talking didn't go so well..." << endl;
		cout << "You now find yourself in battle with the " << npc.getRace() << "..." << endl;
		screen << "You now find yourself in battle with the " << npc.getRace() << "..." << endl;
		battle(user, npc, bag);
	}
	else {
		int chance = user.getRand(20);
		if (chance >= 7) {
			success = true;
			return;
		}
		else {
			success = false;
			cout << "Talking didn't go so well..." << endl;
			screen << "Talking didn't go so well..." << endl;
			cout << "You now find yourself in battle with the " << npc.getRace() << "..." << endl;
			screen << "You now find yourself in battle with the " << npc.getRace() << "..." << endl;
			battle(user, npc, bag);
		}
	}
}

void Story::printText(ifstream& output, Player a) {
	while (getline(output, line)) {
		int x = 0;
		while (line[x] != '\0') {
			cout << line[x];
			screen << line[x];
			sleep_for(milliseconds(25 + a.getRand(25)));
			x++;
		}
		cout << endl;
		screen << endl;
		sleep_for(milliseconds(40 + a.getRand(15)));
	}
}

void Story::endGame(Player& user, Inventory& bag) {
	sleep_for(3000ms);
	system("cls");
	ofstream end("End.txt");

	if (checkWin()) {
		cout << "Congratulations, YOU WIN!!" << endl;
		screen << "Congratulations, YOU WIN!!" << endl;
		cout << "Race: " << endl;
		screen << "Race: " << endl;
		user.printRace();
		screen << user.getRace() << endl;
		cout << "\nBag: " << endl;
		screen << "\nBag: " << endl;
		bag.print();
		cout << "\nKills: " << endl;
		screen << "\nKills: " << endl;
		cout << getKills() << endl;
		screen << getKills() << endl;
		
		end << "Congratulations, YOU WIN!!" << endl;
		end << "Race: " << endl;
		end << user.getRace() << endl;
		end << "\nBag: " << endl;
		end << "Gold: " << bag.getGold() << endl;
		end << "Potions: " << bag.getPotion() << endl;
		end << "Bow: ";
		if (bag.checkBow())
			end << "Yes" << endl;
		else
			end << "No" << endl;
		end << "Sword: ";
		if (bag.checkSword())
			end << "Yes" << endl;
		else
			end << "No" << endl;
		end << "Staff: ";
		if (bag.checkStaff())
			end << "Yes" << endl;
		else
			end << "No" << endl;
		end << "\nKills: " << endl;
		end << getKills() << endl;
	}

	else if (checkDead()) {
		cout << "YOU DIED!!!" << endl;
		screen << "YOU DIED!!!" << endl;
		cout << "Race: " << endl;
		screen << "Race: " << endl;
		user.printRace();
		screen << user.getRace() << endl;
		cout << "\nBag: " << endl;
		screen << "\nBag: " << endl;
		bag.print();
		cout << "\nKills: " << endl;
		screen << "\nKills: " << endl;
		cout << getKills() << endl;
		screen << getKills() << endl;
		
		end << "YOU DIED!!!" << endl;
		end << "Race: " << endl;
		end << user.getRace() << endl;
		end << "\nBag: " << endl;
		end << "Gold: " << bag.getGold() << endl;
		end << "Potions: " << bag.getPotion() << endl;
		end << "Bow: ";
		if (bag.checkBow())
			end << "Yes" << endl;
		else
			end << "No" << endl;
		end << "Sword: ";
		if (bag.checkSword())
			end << "Yes" << endl;
		else
			end << "No" << endl;
		end << "Staff: ";
		if (bag.checkStaff())
			end << "Yes" << endl;
		else
			end << "No" << endl;
		end << "\nKills: " << endl;
		end << getKills() << endl;
	}
	else {
		cout << "YOU WON!!!....did you...?" << endl;
		screen << "YOU WON!!!....did you...?" << endl;
		cout << "Race: " << endl;
		screen << "Race: " << endl;
		user.printRace();
		screen << user.getRace() << endl;
		cout << "\nBag: " << endl;
		screen << "\nBag: " << endl;
		bag.print();
		cout << "\nKills: " << endl;
		screen << "\nKills: " << endl;
		cout << getKills() << endl;
		screen << getKills() << endl;
		
		end << "YOU WON!!!....did you...?" << endl;
		end << "Race: " << endl;
		end << user.getRace() << endl;
		end << "\nBag: " << endl;
		end << "Gold: " << bag.getGold() << endl;
		end << "Potions: " << bag.getPotion() << endl;
		end << "Bow: ";
		if (bag.checkBow())
			end << "Yes" << endl;
		else
			end << "No" << endl;
		end << "Sword: ";
		if (bag.checkSword())
			end << "Yes" << endl;
		else
			end << "No" << endl;
		end << "Staff: ";
		if (bag.checkStaff())
			end << "Yes" << endl;
		else
			end << "No" << endl;
		end << "\nKills: " << endl;
		end << getKills() << endl;
	}
	end.close();
}

void Story::heal(Player& user, Inventory& bag) {
	cout << "Your health is currently: " << user.getHealth() << "/100" << endl;
	screen << "Your health is currently: " << user.getHealth() << "/100" << endl;
	cout << "You currently have " << bag.getPotion() << " potion(s)" << endl;
	screen << "You currently have " << bag.getPotion() << " potion(s)" << endl;
	cout << "A potion will heal you to full health, would you like to use one? ";
	screen << "A potion will heal you to full health, would you like to use one? ";
	cin >> action;
	screen << action;
	while ((action != "yes") && (action != "no")) {
		cout << "Would you like to use one? ";
		screen << "Would you like to use one? ";
		cin >> action;
		screen << action;
	}
	if (action == "yes") {
		user.takePotion(bag);
		cout << "Potion used" << endl;
		screen << "Potion used" << endl;
		cout << "Health: " << user.getHealth() << endl;
		screen << "Health: " << user.getHealth() << endl;
	}
	else {
		cout << "No potion used" << endl;
		screen << "No potion used" << endl;
		cout << "Health: " << user.getHealth() << endl;
		screen << "Health: " << user.getHealth() << endl;
	}
}