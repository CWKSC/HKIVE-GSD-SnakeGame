#pragma once

#include <list>

#include "ArrayLoopingMacro.h"
#include "Snake.h"
#include "Point.h"
#include "FoodList.h"

#define GameBoardMaxX 10
#define GameBoardMaxY 10

class GameBoard {
public:
	char board[GameBoardMaxX][GameBoardMaxY];
	std::list<Point> availableSpace;

	void init() {
		loop2d(x, GameBoardMaxX, y, GameBoardMaxY) {
			board[x][y] = ' ';
			availableSpace.push_back({x, y});
			}
		}
	}

	void printBoardBoundary() {
		std::cout << "+ ";
		loop(GameBoardMaxX) {
			std::cout << "- ";
		}
		std::cout << "+";
	}

	void printBoard() {
		printBoardBoundary();
		std::cout << '\n';

		std::cout << "| ";
		loop2d(y, GameBoardMaxY, x, GameBoardMaxX)
			std::cout << board[x][y] << ' ';
		if (y != GameBoardMaxY - 1) { std::cout << "|\n| "; }
		}
	
		std::cout << "| \n";
		printBoardBoundary();
		std::cout << '\n';
	}

	void printAvailableSpace() {
		std::list<Point>::iterator it;
		for (it = availableSpace.begin(); it != availableSpace.end(); ++it){
			std::cout << '(' << it->x << ", " << it->y << ')';
		}
	}

	void addToBoard(char ch, Point point) {
		board[point.x][point.y] = ch;
		availableSpace.remove({ point.x, point.y });
	}

	
	void addSnakeToBoard(Snake snake) {
		addToBoard('O', snake.snakeBody.front());
		
		std::list<Point>::iterator i;
		for (i = ++snake.snakeBody.begin(); i != snake.snakeBody.end(); ++i){
			addToBoard('o', *i);
		}
	}

	void addFoodListToBoard(FoodList foodList) {
		std::list<FoodNode>::iterator i;
		for (i = foodList.begin(); i != foodList.end(); ++i) {
			addToBoard(i->food, i->point);
		}
	}
	

	void removeToBoard(Point point) {
		board[point.x][point.y] = ' ';
		availableSpace.push_back({ point.x, point.y });
	}

	void removeAvailableSpace(Point point) {
		availableSpace.remove(point);
	}

};


