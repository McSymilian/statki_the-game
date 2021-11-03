#include "statki.h"

int main() {
	Setup setup;
	Player one(setup);
	Player two(setup);

	bool winner = false;
	while (true) {
		one.shootAt(two);
		if (two.isDestroyed())
			break;

		two.shootAt(one);
		if (one.isDestroyed()) {
			winner = true;
			break;
		}
	}
	system("cls");

	winner ? (one.shootAll(), one.showMap()) : (two.shootAll(), two.showMap());

	std::cout << "Wygral gracz " << (winner ? two.getName() : one.getName());
	
}
