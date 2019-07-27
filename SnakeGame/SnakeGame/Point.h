#pragma once

class Point {
public:
	int x, y;

	Point(int inX = 0, int inY = 0
	
	) {
		x = inX;
		y = inY;
	}

	bool operator == (const Point& in) const { return x == in.x && y == in.y; }
	bool operator != (const Point& in) const { return x != in.x || y != in.y; }

	bool operator >  (const Point& in) const { return x + y >  in.x + in.y; }
	bool operator >= (const Point& in) const { return x + y >= in.x + in.y; }

	bool operator <  (const Point& in) const { return x + y <  in.x + in.y; }
	bool operator <= (const Point& in) const { return x + y <= in.x + in.y; }
};

