#ifndef statki_h
#define statki_h
#include <iostream>
enum class Level {
	//difficulty levels
	EASY = 3, MEDIUM = 4, HARD = 5
};

class Setup {
private:
	//defficulty
	Level level;

public:
	Setup();
	Level getLevel();
};

class Player {
private:
	//player name
	std::string name;

	//players map with ships
	int*** map;

	//size of rectangle map
	int size;

	//ships cords set methods
	int set3();
	int set2();
	int set1();

	bool isAvailable(int& x, int& y);

	//shows map with marked every ship
	int showCleanMap();

public:
	Player(Setup& setup);
	//~Player();

	//shows map of taken shots and hits
	int showMap();

	int shootAt(Player nextPlayer);
	int getHit(int& x, int& y);

	bool isDestroyed();

	int shootAll();

	std::string getName();
};
#endif // !1

