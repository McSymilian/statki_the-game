#include "statki.h"

Setup::Setup() {
	std::cout << "Wybierz poziom trudnosci:\n" <<
		"1-latwy (plansza " <<static_cast<int>(Level::EASY)<<":"<< static_cast<int>(Level::EASY) << ", statki : 3 za 1)\n" <<
		"2-sredni (plansza " << static_cast<int>(Level::MEDIUM) << ":" << static_cast<int>(Level::MEDIUM) << ", statki: 3 za 1, 2 za 2)\n" <<
		"3-trudny (plansza " << static_cast<int>(Level::HARD) << ":" << static_cast<int>(Level::HARD) << ", statki: 3 za 1, 2 za 2, 1 za 3)\n";
	int input;
input:
	std::cin >> input;
	switch (input) {
	case 1:
		level = Level::EASY;
		break;
	case 2:
		level = Level::MEDIUM;
		break;
	case 3:
		level = Level::HARD;
		break;
	default:
		std::cout << "Podano nieznany tryb\nSprobuj jeszcze raz: ";
		goto input;
	}
}

Level Setup::getLevel() {
	return level;
}