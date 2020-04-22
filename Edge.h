#ifndef Edge_h
#define Edge_h

#include "Point.h"
#include <iostream>

/*
	A class that stores an edge in Voronoi diagram

	start		: pointer to start point
	end			: pointer to end point
	left		: pointer to Voronoi place on the left side of edge
	right		: pointer to Voronoi place on the right side of edge

	neighbour	: some edges consist of two parts, so we add the pointer to another part to connect them at the end of an algorithm

	direction	: directional vector, from "start", points to "end", normal of |left, right|
	f, g		: directional coeffitients satisfying equation y = f*x + g (edge lies on this line)
*/

class Edge
{
public:

	Point* start;
	Point* end;
	Point* direction;
	Point* left;
	Point* right;

	double		f;
	double		g;

	Edge* neighbour;

	/*
		Constructor of the class

		s		: pointer to start
		a		: pointer to left place
		b		: pointer to right place
	*/

	Edge(Point* s, Point* a, Point* b)
	{
		start = s;
		left = a;
		right = b;
		neighbour = 0;
		end = 0;

		f = (b->x - a->x) / (a->y - b->y);
		g = s->y - f * s->x;
		direction = new Point(b->y - a->y, -(b->x - a->x));
	}

	/*
		Destructor of the class
		direction belongs only to the current edge, other pointers can be shared by other edges
	*/

	~Edge()
	{
		delete direction;
	}

};

#endif