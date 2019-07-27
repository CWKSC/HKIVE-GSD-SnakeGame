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

	// 初始化 //
	void init(Point point = {0, 0}, int mark = 0, int step = 0) {
		this->mark = mark;
		this->step = step;
		snakeBody.push_front(point);
	}

	// 移動並切掉尾巴 //
	void moveTo(Point pt) {
		snakeBody.push_front(pt);
		snakeBody.pop_back();
		step++;
		mark++;
	}

	// 移動，不切掉尾巴，成長 //
	void moveTo_AndGrowUp(Point pt) {
		snakeBody.push_front(pt);
		step++;
		mark++;
	}

	// 打印 mark, step, size
	void print_Mark_Step_Size() {
		std::cout << "Mark: " << mark << '\n';
		std::cout << "Step: " << step << '\n';
		std::cout << "Size: " << snakeBody.size() << '\n';
	}

	// 打印 Stomach
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

	// 配對括弧食物 //
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

	// 配對引號食物 //
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

	// 檢查該位置是否蛇的身體，是否吃到自己 //
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


