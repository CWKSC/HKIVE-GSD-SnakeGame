#include <iostream>

#include "SnakeGame.h"

int main() {
	srand((unsigned)time(NULL));
	SnakeGame snakeGame;
	while (1) {
		snakeGame.Draw();
		Point point = snakeGame.Input();
		snakeGame.Logic(point);
		snakeGame.Updata(point);
	}
	system("pause");
	return 0;
}

