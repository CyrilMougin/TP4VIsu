#ifndef Beachline_h
#define Beachline_h

#include "Point.h"
#include "Edge.h"

/*
	Parabolas and events have pointers to each other, so we declare class VEvent, which will be defined later.
*/

class Event;

/*
	A class that stores information about an item in beachline sequence (see Fortune's algorithm).
	It can represent an arch of parabola or an intersection between two archs (which defines an edge).
	In my implementation I build a binary tree with them (internal nodes are edges, leaves are archs).
*/

class Beachline
{
public:

	/*
		isLeaf		: flag whether the node is Leaf or internal node
		site		: pointer to the focus point of parabola (when it is parabola)
		edge		: pointer to the edge (when it is an edge)
		cEvent		: pointer to the event, when the arch disappears (circle event)
		parent		: pointer to the parent node in tree
	*/

	bool		isLeaf;
	Point* site;
	Edge* edge;
	Event* cEvent;
	Beachline* parent;

	/*
		Constructors of the class (empty for edge, with focus parameter for an arch).
	*/

	Beachline();
	Beachline(Point* s);

	/*
		Access to the children (in tree).
	*/

	void		SetLeft(Beachline* p) { _left = p; p->parent = this; }
	void		SetRight(Beachline* p) { _right = p; p->parent = this; }

	Beachline* Left() { return _left; }
	Beachline* Right() { return _right; }

	/*
		Some useful tree operations

		GetLeft			: returns the closest left leave of the tree
		GetRight		: returns the closest right leafe of the tree
		GetLeftParent	: returns the closest parent which is on the left
		GetLeftParent	: returns the closest parent which is on the right
		GetLeftChild	: returns the closest leave which is on the left of current node
		GetRightChild	: returns the closest leave which is on the right of current node
	*/

	static Beachline* GetLeft(Beachline* p);
	static Beachline* GetRight(Beachline* p);
	static Beachline* GetLeftParent(Beachline* p);
	static Beachline* GetRightParent(Beachline* p);
	static Beachline* GetLeftChild(Beachline* p);
	static Beachline* GetRightChild(Beachline* p);

private:

	Beachline* _left;
	Beachline* _right;
};

#endif