#include "Battle.h"
#include <random>
#include <math.h>
using namespace std;

//constructors
Battle::Battle() {
	player;
	monster;
}
Battle::Battle(Room*& room, Player _player, Monster _monster) {
	roomPointer = room;
	player = _player;
	monster = _monster;
}

// Mutator Functions -- Functions that will be allowed to change private variables
void Battle::setPlayer(Player _player) {
	player = _player;
}
void Battle::setMonster(Monster _monster) {
	monster = _monster;
}
void Battle::setRoom(Room*& room){
	roomPointer = room;
}

// Accessor Functions -- Functions that will return values of private functions
Player Battle::getPlayer() {
	return player;
}
Monster Battle::getMonster() {
	return monster;
}

Room Battle::getRoom()
{
	return *roomPointer;
}

void Battle::displayOpeningLine() {
	cout << endl << player.getName() << " is now going into battle with " << monster.getName() << endl << endl;
}

void Battle::runBattle() {
	vector <string> keyWords = {"q", "quit", "punch", "kick", "bow", "bite"};

	GameUI console;
	
	bool battleLoop = true;
	string input = "";
	Health tempHealth;

	int damage = 0;
	int newHealth = 0;

	// ToDo: This is hardcoded. make a new function that asks what you would like to do
	// and then displays the attacks the user can use
	string prompt = "Current Usable Attacks\n";

	// Display the battle opening line of the player versus the monster
	displayOpeningLine();

	// Main battle loop
	while (battleLoop == true) {
		// Get input from the user continuously until a correct
		// key word is entered
		do {
			cout << prompt; 
			roomPointer->getPlayer().getAttacks().displayattacks();
			cout << endl;
			input = console.getUserInput("What would you like to do: ");
		} while (validateInput(keyWords, input) == false);

		// If the user enter's `q`, then break the main loop and end the game.
		if (input == "q" || input == "quit") {
			cout << "You are ending battle." << endl;
			break;
		}
		else if (input == "punch") {
			cout << "\nPlayer has used: " << player.getAttacks().getWeapon(input).getAttackName() << endl;

			// Attack hits, make monster take damage
			if (hitOrMiss(player.getAttacks().getWeapon(input).getHitChance()) == true) {
				damage = player.getAttacks().getWeapon(input).getAttackDamage();
				newHealth = monster.getHealth().getHealth() + damage;
				tempHealth.setHealth(newHealth);
				tempHealth.setMaxHealth(monster.getHealth().getMaxHealth());
				monster.setHealth(tempHealth);
				roomPointer->setMonster(monster);
				cout << "The attack hit!!\n";
				if (monster.getHealth().getHealth() < 1) {
					cout << "Monster New Health: 0" << endl;
				}
				else {
					cout << "Monster New Health: " << monster.getHealth().getHealth() << endl;
				}
			}
			// Attack misses, do nothing to the monster. Display that the attack missed.
			else {
				cout << "The attack missed!! The " << monster.getName() << " took no damage." << endl;
			}

			//Determines if the monster is defeated and if it was then the battle ends 
			//and displays a victory message to the player
			if (monsterDefeated() == true) {
				cout << "Well done " << player.getName() << " you have defeated the "
					<< monster.getName() << "!! You can now continue exploring the Devils Mansion.\n\n";
				tempHealth.setHealth(-1);
				monster.setHealth(tempHealth);
				roomPointer->setMonster(monster);
				break;
			}

			// Monster attacks back and has random chance to hit the player
			if (hitOrMiss(monster.getAttacks().getMonsterWeapon().getHitChance()) == true) {
				// Monster Attack Stuff
				cout << "\nMonster has used: " << monster.getAttacks().getMonsterWeapon().getAttackName() << endl;
				damage = monster.getAttacks().getMonsterWeapon().getAttackDamage();
				newHealth = player.getPlayerHealth().getHealth() + damage;
				tempHealth.setHealth(newHealth);
				tempHealth.setMaxHealth(player.getPlayerHealth().getMaxHealth());
				player.setPlayerHealth(tempHealth);
				roomPointer->setPlayer(player);
				cout << "The attack hit!!\n";
				if (player.getPlayerHealth().getHealth() < 1) {
					cout << "Player New Health: 0" << endl;
				}
				else {
					cout << "Player New Health: " << player.getPlayerHealth().getHealth() << endl << endl;
				}
			}
			// Attack misses, do nothing to the player. Display that the attack missed.
			else {
				cout << "\nMonster has used: " << monster.getAttacks().getMonsterWeapon().getAttackName() << endl;
				cout << "The attack missed!! " << player.getName() << " took no damage." << endl << endl;
			}
			
			//Determines if the player is defeated and if they are the battle ends 
			//and displays a death message to the player
			if (playerDefeated() == true) {
				cout << "You have died ... once again, it seems you are not very good at this thing called life.\n"
					<< "So I am sending you to the depths of hell for all of eternity.\n\n";
				break;
			}
		}
		else if (input == "kick") {
			cout << "\nPlayer has used: " << player.getAttacks().getWeapon(input).getAttackName() << endl;

			// Attack hits, make monster take damage
			if (hitOrMiss(player.getAttacks().getWeapon(input).getHitChance()) == true) {
				damage = player.getAttacks().getWeapon(input).getAttackDamage();
				newHealth = monster.getHealth().getHealth() + damage;
				tempHealth.setHealth(newHealth);
				tempHealth.setMaxHealth(monster.getHealth().getMaxHealth());
				monster.setHealth(tempHealth);
				roomPointer->setMonster(monster);
				roomPointer->getMonster().getInventory().displayMonsterInventory();
				cout << "The attack hit!!\n";
				if (monster.getHealth().getHealth() < 1) {
					cout << "Monster New Health: 0" << endl;
				}
				else {
					cout << "Monster New Health: " << monster.getHealth().getHealth() << endl;
				}
			}
			// Attack misses, do nothing to the monster. Display that the attack missed.
			else {
				cout << "The attack missed!! The " << monster.getName() << " took no damage." << endl;
			}

			//Determines if the monster is defeated and if it was then the battle ends 
			//and displays a victory message to the player
			if (monsterDefeated() == true) {
				cout << "Well done " << player.getName() << " you have defeated the "
					<< monster.getName() << "!! You can now continue exploring the Devils Mansion.\n\n";
				tempHealth.setHealth(-1);
				monster.setHealth(tempHealth);
				roomPointer->setMonster(monster);
				break;
			}
			// Monster attacks back and has random chance to hit the player
			if (hitOrMiss(monster.getAttacks().getMonsterWeapon().getHitChance()) == true) {
				// Monster Attack Stuff
				cout << "\nMonster has used: " << monster.getAttacks().getMonsterWeapon().getAttackName() << endl;
				damage = monster.getAttacks().getMonsterWeapon().getAttackDamage();
				newHealth = player.getPlayerHealth().getHealth() + damage;
				tempHealth.setHealth(newHealth);
				tempHealth.setMaxHealth(player.getPlayerHealth().getMaxHealth());
				player.setPlayerHealth(tempHealth);
				roomPointer->setPlayer(player);
				cout << "The attack hit!!\n";
				if (player.getPlayerHealth().getHealth() < 1) {
					cout << "Player New Health: 0" << endl;
				}
				else {
					cout << "Player New Health: " << player.getPlayerHealth().getHealth() << endl << endl;
				}
			}
			// Attack misses, do nothing to the player. Display that the attack missed.
			else {
				cout << "\nMonster has used: " << monster.getAttacks().getMonsterWeapon().getAttackName() << endl;
				cout << "The attack missed!! " << player.getName() << " took no damage." << endl << endl;
			}			
			
			//Determines if the player is defeated and if they are the battle ends 
			//and displays a death message to the player
			if (playerDefeated() == true) {
				cout << "You have died ... once again, it seems you are not very good at this thing called life.\n"
					<<"So I am sending you to the depths of hell for all of eternity.\n\n";
				break;
			}
		}
		else if (input == "bow") {
			cout << "\nPlayer has used: " << player.getAttacks().getWeapon(input).getAttackName() << endl;

			// Attack hits, make monster take damage
			if (hitOrMiss(player.getAttacks().getWeapon(input).getHitChance()) == true) {
				damage = player.getAttacks().getWeapon(input).getAttackDamage();
				newHealth = monster.getHealth().getHealth() + damage;
				tempHealth.setHealth(newHealth);
				tempHealth.setMaxHealth(monster.getHealth().getMaxHealth());
				monster.setHealth(tempHealth);
				roomPointer->setMonster(monster);
				cout << "The attack hit!!\n";
				if (monster.getHealth().getHealth() < 1) {
					cout << "Monster New Health: 0" << endl;
				}
				else {
					cout << "Monster New Health: " << monster.getHealth().getHealth() << endl;
				}
			}
			// Attack misses, do nothing to the monster. Display that the attack missed.
			else {
				cout << "The attack missed!! The " << monster.getName() << " took no damage." << endl;
			}

			//Determines if the monster is defeated and if it was then the battle ends 
			//and displays a victory message to the player
			if (monsterDefeated() == true) {
				cout << "Well done " << player.getName() << " you have defeated the "
					<< monster.getName() << "!! You can now continue exploring the Devils Mansion.\n\n";
				tempHealth.setHealth(-1);
				monster.setHealth(tempHealth);
				roomPointer->setMonster(monster);
				break;
			}
			// Monster attacks back and has random chance to hit the player
			if (hitOrMiss(monster.getAttacks().getMonsterWeapon().getHitChance()) == true) {
				// Monster Attack Stuff
				cout << "\nMonster has used: " << monster.getAttacks().getMonsterWeapon().getAttackName() << endl;
				damage = monster.getAttacks().getMonsterWeapon().getAttackDamage();
				newHealth = player.getPlayerHealth().getHealth() + damage;
				tempHealth.setHealth(newHealth);
				tempHealth.setMaxHealth(player.getPlayerHealth().getMaxHealth());
				player.setPlayerHealth(tempHealth);
				roomPointer->setPlayer(player);
				cout << "The attack hit!!\n";
				if (player.getPlayerHealth().getHealth() < 1) {
					cout << "Player New Health: 0" << endl;
				}
				else {
					cout << "Player New Health: " << player.getPlayerHealth().getHealth() << endl << endl;
				}
			}
			// Attack misses, do nothing to the player. Display that the attack missed.
			else {
				cout << "\nMonster has used: " << monster.getAttacks().getMonsterWeapon().getAttackName() << endl;
				cout << "The attack missed!! " << player.getName() << " took no damage." << endl << endl;
			}

			//Determines if the player is defeated and if they are the battle ends 
			//and displays a death message to the player
			if (playerDefeated() == true) {
				cout << "You have died ... once again, it seems you are not very good at this thing called life.\n"
					<< "So I am sending you to the depths of hell for all of eternity.\n\n";
				break;
			}
		}
		else if (input == "bite") {
			cout << "\nPlayer has used: " << player.getAttacks().getWeapon(input).getAttackName() << endl;

			// Attack hits, make monster take damage
			if (hitOrMiss(player.getAttacks().getWeapon(input).getHitChance()) == true) {
				damage = player.getAttacks().getWeapon(input).getAttackDamage();
				newHealth = monster.getHealth().getHealth() + damage;
				tempHealth.setHealth(newHealth);
				tempHealth.setMaxHealth(monster.getHealth().getMaxHealth());
				monster.setHealth(tempHealth);
				roomPointer->setMonster(monster);
				cout << "The attack hit!!\n";
				if (monster.getHealth().getHealth() < 1) {
					cout << "Monster New Health: 0" << endl;
				}
				else {
					cout << "Monster New Health: " << monster.getHealth().getHealth() << endl;
				}
			}
			// Attack misses, do nothing to the monster. Display that the attack missed.
			else {
				cout << "The attack missed!! The " << monster.getName() << " took no damage." << endl;
			}

			//Determines if the monster is defeated and if it was then the battle ends 
			//and displays a victory message to the player
			if (monsterDefeated() == true) {
				cout << "Well done " << player.getName() << " you have defeated the "
					<< monster.getName() << "!! You can now continue exploring the Devils Mansion.\n\n";
				tempHealth.setHealth(-1);
				monster.setHealth(tempHealth);
				roomPointer->setMonster(monster);
				break;
			}
			// Monster attacks back and has random chance to hit the player
			if (hitOrMiss(monster.getAttacks().getMonsterWeapon().getHitChance()) == true) {
				// Monster Attack Stuff
				cout << "\nMonster has used: " << monster.getAttacks().getMonsterWeapon().getAttackName() << endl;
				damage = monster.getAttacks().getMonsterWeapon().getAttackDamage();
				newHealth = player.getPlayerHealth().getHealth() + damage;
				tempHealth.setHealth(newHealth);
				tempHealth.setMaxHealth(player.getPlayerHealth().getMaxHealth());
				player.setPlayerHealth(tempHealth);
				roomPointer->setPlayer(player);
				cout << "The attack hit!!\n";
				if (player.getPlayerHealth().getHealth() < 1) {
					cout << "Player New Health: 0" << endl;
				}
				else {
					cout << "Player New Health: " << player.getPlayerHealth().getHealth() << endl << endl;
				}
			}
			// Attack misses, do nothing to the player. Display that the attack missed.
			else {
				cout << "\nMonster has used: " << monster.getAttacks().getMonsterWeapon().getAttackName() << endl;
				cout << "The attack missed!! " << player.getName() << " took no damage." << endl << endl;
			}

			//Determines if the player is defeated and if they are the battle ends 
			//and displays a death message to the player
			if (playerDefeated() == true) {
				cout << "You have died ... once again, it seems you are not very good at this thing called life.\n"
					<< "So I am sending you to the depths of hell for all of eternity.\n\n";
				break;
			}
		}
	}
}

// Validate that the input from the user is a correct command.
// Correct commands will be in the keyWords vector.
bool Battle:: validateInput(vector<string>& vect, string sentence) {
	for (int i = 0; i < vect.size(); i++) {
		if (vect.at(i) == sentence) {
			return true;
		}
	}
	return false;
}

bool Battle::hitOrMiss(int hitChance) {
	// Used for generating a random number
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(1.0, 100.0);

	// Variable to hold the randomly generated number
	int number = 0;
	number = dist(mt);

	// Check if the random number is less than the hitChance
	// If it is, then the attack will hit and the monster will be affected.
	// If the number is higher than hitChance then the monster will be
	// left unaffected by the hit
	if (number <= hitChance) {
		return true;
	}
	return false;

}

bool Battle::monsterDefeated() {
	if (monster.getHealth().getHealth() > 1)
		return false;
	else
		return true;
}

bool Battle::playerDefeated() {
	if (player.getPlayerHealth().getHealth() > 1)
		return false;
	else
		return true;
}