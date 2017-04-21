/*
 * Point.h
 *
 *  Created on: Mar 19, 2017
 *      Author: patrick
 */

#ifndef PATHFINDER_POINT_H_
#define PATHFINDER_POINT_H_

class Point
{
public:
	Point();
	Point(int x, int y);
	Point(const Point& point);

	virtual ~Point();

	int GetX() const;
	int GetY() const;
	bool operator==(const Point& other) const;

private:
	int _x, _y;
};

#endif /* PATHFINDER_POINT_H_ */
