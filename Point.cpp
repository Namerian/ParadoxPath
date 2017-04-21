/*
 * Point.cpp
 *
 *  Created on: Mar 19, 2017
 *      Author: patrick
 */

#include "Point.h"

Point::Point()
{
	_x = 0;
	_y = 0;
}

Point::Point(int x, int y)
{
	_x = x;
	_y = y;
}

Point::Point(const Point& point)
{
	_x = point._x;
	_y = point._y;
}

Point::~Point()
{
}

int Point::GetX() const
{
	return _x;
}

int Point::GetY() const
{
	return _y;
}

bool Point::operator==(const Point& other) const
{
	return (this->_x == other._x && this->_y == other._y);
}
