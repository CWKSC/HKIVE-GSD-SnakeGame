#pragma once

#include <list>

#include "Point.h"

enum Food {
	LeftBracket = '(',  // (
	RightBracket = ')', // )

	LeftMidBracket = '[',  // [
	RightMidBracket = ']', // ]

	LeftBigBracket = '{',  // {
	RightBigBracket = '}', // }

	SingleQuotes = '\'', // '
	DoubleQuotes = '\"', // "

	ErrorFood = 'E' // it mean Error
};

class FoodNode {
public:
	Food food;
	Point point;
};

typedef std::list<FoodNode> FoodList;


