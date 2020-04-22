#include "Beachline.h"
#include "Point.h"

/*
	Constructors
*/
Beachline::Beachline()
{
	site = 0;
	isLeaf = false;
	cEvent = 0;
	edge = 0;
	parent = 0;
}

Beachline::Beachline(Point* s)
{
	site = s;
	isLeaf = true;
	cEvent = 0;
	edge = 0;
	parent = 0;
}

/*
	Tree operations (described in the header file)
*/

Beachline* Beachline::GetLeft(Beachline* p)
{
	return GetLeftChild(GetLeftParent(p));
}


Beachline* Beachline::GetRight(Beachline* p)
{
	return GetRightChild(GetRightParent(p));
}

Beachline* Beachline::GetLeftParent(Beachline* p)
{
	Beachline* par = p->parent;
	Beachline* pLast = p;
	while (par->Left() == pLast)
	{
		if (!par->parent) return 0;
		pLast = par;
		par = par->parent;
	}
	return par;
}

Beachline* Beachline::GetRightParent(Beachline* p)
{
	Beachline* par = p->parent;
	Beachline* pLast = p;
	while (par->Right() == pLast)
	{
		if (!par->parent) return 0;
		pLast = par; par = par->parent;
	}
	return par;
}

Beachline* Beachline::GetLeftChild(Beachline* p)
{
	if (!p) return 0;
	Beachline* par = p->Left();
	while (!par->isLeaf) par = par->Right();
	return par;
}

Beachline* Beachline::GetRightChild(Beachline* p)
{
	if (!p) return 0;
	Beachline* par = p->Right();
	while (!par->isLeaf) par = par->Left();
	return par;
}
