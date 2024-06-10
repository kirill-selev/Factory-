#include<iostream>
#include<string>
#include<map>
#include<memory>


#define delimetr "\n------------------------------------------------\n"
using namespace std;

class Player  {


	
public:
	virtual Player* clone()const = 0;
	/*Player(const std::string&name,int id):name(name),id(id){}\*/

	virtual~Player() {}

	virtual void print()const = 0;
	
};


class CarPlayer :public Player {

	string name;
	int id;
public:
	CarPlayer(const const std::string& name, int id) :name(name) ,id(id){
		cout << "car_constructor"<<this<<endl;
	}
	~CarPlayer() {
		cout<< "car_destructor" << this << endl;
	}

	void print()const override {
		cout << this << ":\t" << name << " " << id << endl;
	}

	Player* clone()const override {
		return new CarPlayer(*this);
	}
};


class BikePlayer :public Player {



	std::string name;
	int id;
public:
	BikePlayer(const const std::string& name, int id) :name(name), id(id) {
		cout << "bike_constructor" << this << endl;
	}
	~BikePlayer() { 
		cout << "bike_destructor" << this << endl;
	}
	void print()const override {
		cout << this << ":\t" << name << " " << id << endl;
	}

	Player* clone()const override {
		return new BikePlayer(*this);
	}


};


enum PlayerType {
	CAR,BIKE
};

class PlayerFactory {

	std::map<PlayerType, Player*>players;

public:
	PlayerFactory() {

		players[CAR] = new CarPlayer("BMW", 735);
		players[BIKE] = new BikePlayer("Harley davidson", 200);
	}
	~PlayerFactory()
	{
		delete players[CAR];
		delete players[BIKE];
	}

	Player* CreatePlayer(PlayerType type) {

		return players[type]->clone();
	}


};
//#define PROBLEM
#define SOLUTION
void main() {

	setlocale(LC_ALL, "");
#ifdef PROBLEM 
	Player car_player_template("car player", 100);
		Player bike_player_template("bike player", 200);
		car_player_template.print();
		bike_player_template.print();



		Player car_player = car_player_template;
		car_player.print();

		Player bike_player = bike_player_template;
		bike_player.print();
#endif // PROBLEM

	
#ifdef SOLUTION
		PlayerFactory factory;
		cout << delimetr << endl;

		Player* car_player = factory.CreatePlayer(CAR);
		car_player->print();
		cout << delimetr << endl;



		Player* bike_player = factory.CreatePlayer(BIKE);
		bike_player->print();
		cout << delimetr << endl;
		delete bike_player;
		delete car_player;
		cout << delimetr << endl;


		
#endif // SOLUTION

}