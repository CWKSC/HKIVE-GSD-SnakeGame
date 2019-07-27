#pragma once

#include <conio.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <set>

#include "Point.h"
#include "FoodList.h"

class FoodControl{
public:

	static void removeFormFoodList(FoodList & foodList, Point point) {
		std::list<FoodNode>::iterator it = foodList.begin();
		for (;it != foodList.end(); it++) {
			if (it->point == point) {
				foodList.erase(it);
				return;
			}
		}
		std::cout << "Error, unexpected flow.";
		system("pause");
	}

	static void generateFood(GameBoard & gameBoard, FoodList & foodList) {
		Food food = FoodControl::generateFoodType();
		Point point = FoodControl::generateFoodPosition(gameBoard.availableSpace);
		if (point != Point{ -1, -1 }) {
			foodList.push_back({ food, point });
			gameBoard.removeAvailableSpace(point);
		}
	}

	static Point generateFoodPosition(std::list<Point> & availableSpace) {
		if (availableSpace.empty()) {
			return {-1, -1}; //it mean no space
		}

		int randNum = rand() % availableSpace.size();

		std::list<Point>::iterator it = availableSpace.begin();
		int i = 0;
		for (int i = 0; i != randNum && it != availableSpace.end(); i++, it++);

		return *it;
	}

	static Food generateFoodType() {
		int randNum = rand() % 8;

		switch (randNum) {
		case 0: return LeftBracket;
		case 1: return RightBracket;
		case 2: return LeftMidBracket;
		case 3: return RightMidBracket;
		case 4: return LeftBigBracket;
		case 5: return RightBigBracket;
		case 6: return SingleQuotes;
		case 7: return DoubleQuotes;
		default:
			std::cout << "Error, unexpected switch flow.";
			system("pause");
			return ErrorFood;
		}
	}

	static bool isItFoodOnBoard(GameBoard & gameBoard, Point point) {
		switch (gameBoard.board[point.x][point.y])
		{
		case LeftBracket:
		case RightBracket:
		case LeftMidBracket:
		case RightMidBracket:
		case LeftBigBracket:
		case RightBigBracket:
		case SingleQuotes:
		case DoubleQuotes:
			return true;
		default:
			return false;
		}
	}

	static bool isItTimeToGenerateFood(int step) {

		switch (step) {
		case 0: case 4: case 7: case 10: 
		case 12: case 14: case 16: case 18: case 20:
			return true;
		}

		if (step > 20) {
			return true;
		}
		return false;
	}
};

