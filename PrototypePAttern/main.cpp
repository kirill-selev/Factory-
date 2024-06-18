#include<iostream>
#include<string>
#include<map>
#include<memory>


#define delimetr "\n------------------------------------------------\n"
using namespace std;

class Player  {


	
public:
	virtual unique_ptr<Player> clone()const = 0;
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

	unique_ptr<Player> clone()const override {
		return make_unique<CarPlayer>(*this);
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

	unique_ptr<Player> clone()const override {
		
		return make_unique<BikePlayer>(*this);
	}


};


enum PlayerType {
	CAR,BIKE
};

class PlayerFactory {

	static std::map<PlayerType, unique_ptr<Player>>players;


	static void Init() {

		/*players[CAR] = new CarPlayer("BMW", 735);
		players[BIKE] = new BikePlayer("Harley davidson", 200);*/
		if(players.find(CAR)==players.end())players[CAR] = make_unique< CarPlayer>(CarPlayer("BMW", 735));
		if (players.find(BIKE) == players.end())players[BIKE] = make_unique< BikePlayer>(BikePlayer("Harley davidson", 200));
	}
public:
	/*~PlayerFactory()
	{
		delete players[CAR];
		delete players[BIKE];
	}*/

	static unique_ptr<Player> CreatePlayer(PlayerType type) {
		Init();
		return players[type]->clone();
	}


};



	

//#define PROBLEM
//#define SOLUTION_0
#define SOLUTION_1
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

	
#ifdef SOLUTION_0
		PlayerFactory factory;
		cout << delimetr << endl;

		unique_ptr<Player> car_player = factory.CreatePlayer(CAR);
		car_player->print();
		cout << delimetr << endl;



		unique_ptr<Player> bike_player = factory.CreatePlayer(BIKE);
		bike_player->print();
		


		
#endif // SOLUTION_0


#ifdef SOLUTION_1


		cout << delimetr;
		std::unique_ptr<Player> car_player = PlayerFactory::CreatePlayer(CAR);
		car_player->print();
		cout << delimetr; 
		std::unique_ptr<Player> bike_player = PlayerFactory::CreatePlayer(BIKE);



#endif // SOLUTION_1

}