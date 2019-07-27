#pragma once

#include <stack>
#include <list>

#include "Point.h"
#include "FoodList.h"

class Snake {
public:
	int mark, step;
	std::list<Point> snakeBody;
	std::stack<Food> stomach;

	// ��l�� //
	void init(Point point = {0, 0}, int mark = 0, int step = 0) {
		this->mark = mark;
		this->step = step;
		snakeBody.push_front(point);
	}

	// ���ʨä������� //
	void moveTo(Point pt) {
		snakeBody.push_front(pt);
		snakeBody.pop_back();
		step++;
		mark++;
	}

	// ���ʡA���������ڡA���� //
	void moveTo_AndGrowUp(Point pt) {
		snakeBody.push_front(pt);
		step++;
		mark++;
	}

	// ���L mark, step, size
	void print_Mark_Step_Size() {
		std::cout << "Mark: " << mark << '\n';
		std::cout << "Step: " << step << '\n';
		std::cout << "Size: " << snakeBody.size() << '\n';
	}

	// ���L Stomach
	void printStomach() {
		std::cout << "Stomach Stack (" << stomach.size() << "/5) :";
		std::stack<Food> copy = stomach;
		std::stack<Food> reverse;
		loop(stomach.size()) {
			reverse.push(copy.top());
			copy.pop();
		}
		loop(stomach.size()) {
			std::cout << ' ' << (char)reverse.top();
			reverse.pop();
		}
		std::cout << "\nfrom bottom to top \n";
	}

	// �t��A������ //
	bool matchPairOfbrackets(Food stomachTopFood, Food food) {
		switch (stomachTopFood)
		{
		case LeftBracket:
			return food == RightBracket;
		case LeftMidBracket:
			return food == RightMidBracket;
		case LeftBigBracket:
			return food == RightBigBracket;
		}
		return false;
	}

	// �t��޸����� //
	bool matchPairOfQuotes(Food stomachTopFood, Food food) {
		switch (stomachTopFood)
		{
		case SingleQuotes:
			return food == SingleQuotes;
		case DoubleQuotes:
			return food == DoubleQuotes;
		}
		return false;
	}

	// �ˬd�Ӧ�m�O�_�D������A�O�_�Y��ۤv //
	bool isItEatSelf(Point movePoint) {
		std::list<Point>::iterator it = snakeBody.begin();
		for (; it != snakeBody.end(); it++) {
			if (*it == movePoint) {
				return true;
			}
		}
		return false;
	}
	

};


