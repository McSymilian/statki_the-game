#include "statki.h"
#include <chrono>
#include <thread>
#include <conio.h>

Player::Player(Setup& setup) {
	system("cls");
	std::cout << "Podaj nazwe gracza: ";
	std::cin >> name;

	//creating map
	size = static_cast<int>(setup.getLevel());
	map = new int** [2];
	map[0] = new int* [size];
	map[1] = new int* [size];
	for (int i = 0; i < size; i++) {
		map[0][i] = new int[size];
		map[1][i] = new int[size];
	}

	//setting clear map;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			map[0][i][j] = 0;
			map[1][i][j] = 0;
		}
	}
	showCleanMap();

	//setting positions of ships
	switch (setup.getLevel()) {
	case Level::HARD:
		//setting position of a ship of lenght 3
		std::cout << "Podaj lokalizacje krancowe statku za 3:\n";
		while (set3() != 0);

	case Level::MEDIUM:
		//setting position of 2 ship of lenght 2
		std::cout << "Podaj lokalizacje statkow za 2:\n";
		for (int i = 0; i < 2;) 
			set2() == 0 ? i++ : i;

	case Level::EASY:
		//setting position of 3 ship of lenght 1
		std::cout << "Podaj lokalizacje statkow za 1:\n";
		for (int i = 0; i < 3;) 
			set1() == 0 ? i++ : i;
	}
	system("cls");
	std::cout << "Gracz " << name << "\n";
	showCleanMap();
	_getch();
}
/*Player::~Player()
{
	for (int j = 0; j <= 1; j++) {
		for (int i = 0; i < size; i++)
			delete[] map[j][i];
		delete[] map[j];
	}
	delete[] map;
}*/
int Player::showMap() {
	//first line
	std::cout << " ";
	for (int i = 1; i <= size; i++) {
		std::cout << " " << i;
	}
	std::cout << '\n';

	//right map
	for (int i = 0; i < size; i++) {
		std::cout << i + 1 <<".";
		for (int j = 0; j < size; j++) {
			std::cout << (map[1][i][j] == 0 ? "#" : (map[0][i][j] == 0 ? "o" : "x")) << " ";
		}
		std::cout << '\n';
	}

	return 0;
}

int Player::shootAt(Player nextPlayer)
{
	system("cls");
	std::cout << "Gracz " << name << " strzela do " << nextPlayer.getName() << "\n";
	nextPlayer.showMap();
	std::cout << "Podaj koordynaty celu\n";
	int x, y;
	std::cin >> x >> y;

	return nextPlayer.getHit(x, y);
}

int Player::getHit(int& x, int& y)
{
	int xVal = x - 1;
	int yVal = y - 1;
	map[1][xVal][yVal] = 1;
	if (!isAvailable(x, y))
		map[0][xVal][yVal] = -1;
	else
		return 1;
	return 0;
}

bool Player::isDestroyed()
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (map[0][i][j] != 0 && map[0][i][j] != -1)
				return false;
		}
	}
	return true;
}

int Player::shootAll()
{
	for (int i = 1; i <= size; i++)
		for (int j = 1; j <= size; j++)
			getHit(i, j);
	return 0;
}

std::string Player::getName()
{
	return name;
}

int Player::showCleanMap() {
	//first line
	std::cout << " ";
	for (int i = 1; i <= size; i++) {
		std::cout << " " << i;
	}
	std::cout << '\n';

	//right map
	for (int i = 0; i < size; i++) {
		std::cout << i + 1 << ".";
		for (int j = 0; j < size; j++) {
			std::cout << map[0][i][j] << " ";
		}
		std::cout << '\n';
	}
	return 0;
}

bool Player::isAvailable(int& x, int& y) {
	if (map[0][x - 1][y - 1] == 0)
		return true;
	return false;
}

int Player::set1() {
	//setting position of a ship of lenght 1
	int x, y;
	std::cin >> x >> y;
	if (x > size || x <= 0 || y > size || y <= 0) {
		std::cout << "Podano bledne koordynaty\n";
		return -1;
	}

	if (!isAvailable(x, y)) {
		std::cout << "Podane koordynaty sa zajete\n";
		return -1;
	}

	map[0][x - 1][y - 1] = 1;
	showCleanMap();
	return 0;
}

int Player::set2() {
	//setting position of a ship of lenght 2
	int x1{ 0 }, y1{ 0 };
	int x2{ 0 }, y2{ 0 };

	std::cin >> x1 >> y1;
	std::cin >> x2 >> y2;

	if ((x1 > size || x1 <= 0 || y1 > size || y1 <= 0) ||
		(x2 > size || x2 <= 0 || y2 > size || y2 <= 0) ||
		(x1 != x2 && y1 != y2) || (x1 == x2 && y1 == y2)) {
		std::cout << "Podano bledne koordynaty\n";
		return -1;
	}

	if (!isAvailable(x1, y1) || !isAvailable(x2, y2)) {
		std::cout << "Podane koordynaty sa zajete\n";
		return -1;
	}

	map[0][x1 - 1][y1 - 1] = 2;
	map[0][x2 - 1][y2 - 1] = 2;
	showCleanMap();
	return 0;
}

int Player::set3() {
	//setting position of a ship of lenght 3
	int x1, y1;
	int x2, y2;

	std::cin >> x1 >> y1;
	std::cin >> x2 >> y2;

	if ((x1 > size || x1 <= 0 || y1 > size || y1 <= 0) ||
		(x2 > size || x2 <= 0 || y2 > size || y2 <= 0)){
		if ((x1 + 2 == x2 && y1 == y2) || (x1 == x2 + 2 && y1 == y2) ||
			(x1 == x2 && y1 + 2 == y2) || (x1 == x2 && y1 == y2 + 2))
			goto save;
		std::cout << "Podano bledne koordynaty\n";
		return -1;
	}

	if (!isAvailable(x1, y1) || !isAvailable(x2, y2)) {
		std::cout << "Podane koordynaty sa zajete\n";
		return -1;
	}

	if (x1 == x2) {
		int y = y1 > y2 ? y2 - 1 : y1 - 1;
		if (!isAvailable(x1, y)) {
			std::cout << "Podane koordynaty sa zajete\n";
			return -1;
		}
	}
	else {
		int x = x1 > x2 ? x2 + 1 : x1 + 1;
		if (!isAvailable(x, y1)) {
			std::cout << "Podane koordynaty sa zajete\n";
			return -1;
		}
	}
save:
	map[0][x1 - 1][y1 - 1] = 3;
	map[0][x2 - 1][y2 - 1] = 3;

	if (x1 == x2) 
		map[0][x1 - 1][y1 > y2 ? y2: y1] = 3;
	else
		map[0][x1 > x2 ? x2 : x1][y2 - 1] = 3;
	showCleanMap();
	return 0;
}