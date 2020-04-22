#ifndef Event_h
#define Event_h

#include <iostream>
#include "Point.h"
#include "Beachline.h"

/*
	The class for storing place / circle event in event queue.

	point		: the point at which current event occurs (top circle point for circle event, focus point for place event)
	pe			: whether it is a place event or not
	y			: y coordinate of "point", events are sorted by this "y"
	arch		: if "pe", it is an arch above which the event occurs
*/

class Event
{
public:
	Point* point;
	bool		pe;
	double		y;
	Beachline* arch;

	/*
		Constructor for the class

		p		: point, at which the event occurs
		pev		: whether it is a place event or not
	*/

	Event(Point* p, bool pev)
	{
		point = p;
		pe = pev;
		y = p->y;
		arch = 0;
	}

	/*
		function for comparing two events (by "y" property)
	*/

	struct CompareEvent : public std::binary_function<Event*, Event*, bool>
	{
		bool operator()(const Event* l, const Event* r) const { return (l->y < r->y); }
	};
};

#endif
