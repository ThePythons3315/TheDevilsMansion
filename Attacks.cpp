#include "Attacks.h"
using namespace std;

Attacks::Attacks(){
	attacks = {};
}

void Attacks::addAttack(Weapon weapon){
	attacks.push_back(weapon);
}

void Attacks::displayattacks(){
	if (attacks.size() == 0) {
		cout << "-There are no attacks.\n";
	}
	else {
		cout << "Attack list: " << endl;
		for (int i = 0; i < attacks.size(); i++) {
			cout << "-" << attacks.at(i).getName() << endl;
		}
	}
}

Weapon Attacks::getWeapon(string _weapon){
	Weapon weapon;
	bool found = false;
	for (int i = 0; i < attacks.size(); i++) {
		if (attacks.at(i).getName() == _weapon) {
			weapon = attacks.at(i);
			found = true;
			break;
		}
	}
	if (found == false)
		cout << "The attack you have entered has not been unlocked yet or does not exist\n";
	return weapon;
}

void Attacks::getAttackStats(string _weapon)
{
	Weapon weapon;
	if (_weapon == getWeapon(_weapon).getName()) {
		weapon = getWeapon(_weapon);
		cout << weapon.getAttackName() << " stats:\n";
		cout << "\t- Attack damage \t-> " << weapon.getAttackDamage() << "% health points\n";
		cout << "\t- Attack hit chance \t-> " << weapon.getHitChance() << "% hit chance\n";
	}
}

Weapon Attacks::getMonsterWeapon()
{
	return attacks.at(0);
}

int Attacks::getSize(){
	return attacks.size();
}

vector<Weapon> Attacks::getAttacks(){
	return attacks;
}

void Attacks::removeItem(int index){
	attacks.erase(attacks.begin() + index);
}
