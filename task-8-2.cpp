#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
using namespace std;

//weapon class
class Weapon {
protected:
    string name;
    int damage;
    int accuracy; 
public:
    Weapon(string n, int d, int a) : name(n), damage(d), accuracy(a) {}
    virtual ~Weapon() {}
    virtual void useWeapon(string attackerName, int &opponentHealth) {
        int roll = rand() % 100 + 1; //roll between 1 and 100 for accuracy check
        cout << attackerName << " attacks with " << name << " and he ";
        if (roll <= accuracy) {
            opponentHealth -= damage;
            cout << "hit! Damage: " << damage << ". Opponent health: " << max(0, opponentHealth) << endl;
        } else {
            cout << "missed!" << endl;
        }
    }
};

// Character base class
class Character {
protected:
    string name;
    int health;
    vector<unique_ptr<Weapon>> weapons;
public:
    Character(string n) : name(n), health(100) {}
    virtual ~Character() {}
    virtual void attack(Character &opponent) {
        int choice = rand() % weapons.size(); //random weapon
        weapons[choice]->useWeapon(name, opponent.health);
    }
    bool isAlive() { return health > 0; }// function to check if alive
    string getName() { return name; } //function to get the name
    int getHealth() { return health; } //function to get current health
};

//the 2 characters fighting 
class OptimusPrime : public Character {
public:
    OptimusPrime() : Character("Optimus Prime") {
        weapons.push_back(make_unique<Weapon>("Ion Rifle", 6, 100));
        weapons.push_back(make_unique<Weapon>("Energon Swords", 12, 80));
        weapons.push_back(make_unique<Weapon>("Shoulder Cannon", 45, 25));
    }
};

class Megatron : public Character {
public:
    Megatron() : Character("Megatron") {
        weapons.push_back(make_unique<Weapon>("Fusion Cannon", 9, 90));
        weapons.push_back(make_unique<Weapon>("Fusion Sword", 18, 70));
        weapons.push_back(make_unique<Weapon>("Tank Mode", 60, 15));
    }
};


//main fight loop
int main() {
    srand(time(0)); //random seed, so we get different results each time
    OptimusPrime optimus;
    Megatron megatron;

    cout << "The big fight: Optimus Prime vs Megatron\n" << endl;

    bool optimusTurn = true;

    while (optimus.isAlive() && megatron.isAlive()) {
        if (optimusTurn) {
            optimus.attack(megatron);
        } else {
            megatron.attack(optimus);
        }
        optimusTurn = !optimusTurn; //change turn
    }

    cout << "\nBattle Over! ";
    if (optimus.isAlive())
        cout << "winner is " << optimus.getName() << " with " << optimus.getHealth() << " health left" << endl;
    else
        cout << "winner is " << megatron.getName() << " with " << megatron.getHealth() << " health left" << endl;

    return 0;
}
