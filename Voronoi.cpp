
#include "Voronoi.h"
#include <iostream>
#include <algorithm>
#include <set>

using namespace vor;

Voronoi::Voronoi()
{
	edges = 0;
}

Edges* Voronoi::GetEdges(Vertices* v, int w, int h)
{
	places = v;
	width = w;
	height = h;
	root = 0;

	if (!edges) edges = new Edges();
	else
	{
		for (Vertices::iterator i = points.begin(); i != points.end(); ++i) delete (*i);
		for (Edges::iterator i = edges->begin(); i != edges->end(); ++i) delete (*i);
		points.clear();
		edges->clear();
	}

	for (Vertices::iterator i = places->begin(); i != places->end(); ++i)
	{
		queue.push(new Event(*i, true));
	}

	Event* e;
	while (!queue.empty())
	{
		e = queue.top();
		queue.pop();
		ly = e->point->y;
		if (deleted.find(e) != deleted.end()) { delete(e); deleted.erase(e); continue; }
		if (e->pe) InsertParabola(e->point);
		else RemoveParabola(e);
		delete(e);
	}

	FinishEdge(root);

	for (Edges::iterator i = edges->begin(); i != edges->end(); ++i)
	{
		if ((*i)->neighbour)
		{
			(*i)->start = (*i)->neighbour->end;
			delete (*i)->neighbour;
		}
	}

	return edges;
}

void	Voronoi::InsertParabola(Point* p)
{
	if (!root) { root = new Beachline(p); return; }

	if (root->isLeaf && root->site->y - p->y < 1) // degenerovaný pøípad - obì spodní místa ve stejné výšce
	{
		Point* fp = root->site;
		root->isLeaf = false;
		root->SetLeft(new Beachline(fp));
		root->SetRight(new Beachline(p));
		Point* s = new Point((p->x + fp->x) / 2, height); // zaèátek hrany uprostøed míst
		points.push_back(s);
		if (p->x > fp->x) root->edge = new Edge(s, fp, p); // rozhodnu, který vlevo, který vpravo
		else root->edge = new Edge(s, p, fp);
		edges->push_back(root->edge);
		return;
	}

	Beachline* par = GetParabolaByX(p->x);

	if (par->cEvent)
	{
		deleted.insert(par->cEvent);
		par->cEvent = 0;
	}

	Point* start = new Point(p->x, GetY(par->site, p->x));
	points.push_back(start);

	Edge* el = new Edge(start, par->site, p);
	Edge* er = new Edge(start, p, par->site);

	el->neighbour = er;
	edges->push_back(el);

	// pøestavuju strom .. vkládám novou parabolu
	par->edge = er;
	par->isLeaf = false;

	Beachline* p0 = new Beachline(par->site);
	Beachline* p1 = new Beachline(p);
	Beachline* p2 = new Beachline(par->site);

	par->SetRight(p2);
	par->SetLeft(new Beachline());
	par->Left()->edge = el;

	par->Left()->SetLeft(p0);
	par->Left()->SetRight(p1);

	CheckCircle(p0);
	CheckCircle(p2);
}

void	Voronoi::RemoveParabola(Event* e)
{
	Beachline* p1 = e->arch;

	Beachline* xl = Beachline::GetLeftParent(p1);
	Beachline* xr = Beachline::GetRightParent(p1);

	Beachline* p0 = Beachline::GetLeftChild(xl);
	Beachline* p2 = Beachline::GetRightChild(xr);

	if (p0 == p2) std::cout << "chyba - pravá a levá parabola má stejné ohnisko!\n";

	if (p0->cEvent) { deleted.insert(p0->cEvent); p0->cEvent = 0; }
	if (p2->cEvent) { deleted.insert(p2->cEvent); p2->cEvent = 0; }

	Point* p = new Point(e->point->x, GetY(p1->site, e->point->x));
	points.push_back(p);

	xl->edge->end = p;
	xr->edge->end = p;

	Beachline* higher;
	Beachline* par = p1;
	while (par != root)
	{
		par = par->parent;
		if (par == xl) higher = xl;
		if (par == xr) higher = xr;
	}
	higher->edge = new Edge(p, p0->site, p2->site);
	edges->push_back(higher->edge);

	Beachline* gparent = p1->parent->parent;
	if (p1->parent->Left() == p1)
	{
		if (gparent->Left() == p1->parent) gparent->SetLeft(p1->parent->Right());
		if (gparent->Right() == p1->parent) gparent->SetRight(p1->parent->Right());
	}
	else
	{
		if (gparent->Left() == p1->parent) gparent->SetLeft(p1->parent->Left());
		if (gparent->Right() == p1->parent) gparent->SetRight(p1->parent->Left());
	}

	delete p1->parent;
	delete p1;

	CheckCircle(p0);
	CheckCircle(p2);
}

void	Voronoi::FinishEdge(Beachline* n)
{
	if (n->isLeaf) { delete n; return; }
	double mx;
	if (n->edge->direction->x > 0.0)	mx = std::max(width, n->edge->start->x + 10);
	else							mx = std::min(0.0, n->edge->start->x - 10);

	Point* end = new Point(mx, mx * n->edge->f + n->edge->g);
	n->edge->end = end;
	points.push_back(end);

	FinishEdge(n->Left());
	FinishEdge(n->Right());
	delete n;
}

double	Voronoi::GetXOfEdge(Beachline* par, double y)
{
	Beachline* left = Beachline::GetLeftChild(par);
	Beachline* right = Beachline::GetRightChild(par);

	Point* p = left->site;
	Point* r = right->site;

	double dp = 2.0 * (p->y - y);
	double a1 = 1.0 / dp;
	double b1 = -2.0 * p->x / dp;
	double c1 = y + dp / 4 + p->x * p->x / dp;

	dp = 2.0 * (r->y - y);
	double a2 = 1.0 / dp;
	double b2 = -2.0 * r->x / dp;
	double c2 = ly + dp / 4 + r->x * r->x / dp;

	double a = a1 - a2;
	double b = b1 - b2;
	double c = c1 - c2;

	double disc = b * b - 4 * a * c;
	double x1 = (-b + std::sqrt(disc)) / (2 * a);
	double x2 = (-b - std::sqrt(disc)) / (2 * a);

	double ry;
	if (p->y < r->y) ry = std::max(x1, x2);
	else ry = std::min(x1, x2);

	return ry;
}

Beachline* Voronoi::GetParabolaByX(double xx)
{
	Beachline* par = root;
	double x = 0.0;

	while (!par->isLeaf) // projdu stromem dokud nenarazím na vhodný list
	{
		x = GetXOfEdge(par, ly);
		if (x > xx) par = par->Left();
		else par = par->Right();
	}
	return par;
}

double	Voronoi::GetY(Point* p, double x) // ohnisko, x-souøadnice
{
	double dp = 2 * (p->y - ly);
	double a1 = 1 / dp;
	double b1 = -2 * p->x / dp;
	double c1 = ly + dp / 4 + p->x * p->x / dp;

	return(a1 * x * x + b1 * x + c1);
}

void	Voronoi::CheckCircle(Beachline* b)
{
	Beachline* lp = Beachline::GetLeftParent(b);
	Beachline* rp = Beachline::GetRightParent(b);

	Beachline* a = Beachline::GetLeftChild(lp);
	Beachline* c = Beachline::GetRightChild(rp);

	if (!a || !c || a->site == c->site) return;

	Point* s = 0;
	s = GetEdgeIntersection(lp->edge, rp->edge);
	if (s == 0) return;

	double dx = a->site->x - s->x;
	double dy = a->site->y - s->y;

	double d = std::sqrt((dx * dx) + (dy * dy));

	if (s->y - d >= ly) { return; }

	Event* e = new Event(new Point(s->x, s->y - d), false);
	points.push_back(e->point);
	b->cEvent = e;
	e->arch = b;
	queue.push(e);
}

Point* Voronoi::GetEdgeIntersection(Edge* a, Edge* b)
{
	double x = (b->g - a->g) / (a->f - b->f);
	double y = a->f * x + a->g;

	if ((x - a->start->x) / a->direction->x < 0) return 0;
	if ((y - a->start->y) / a->direction->y < 0) return 0;

	if ((x - b->start->x) / b->direction->x < 0) return 0;
	if ((y - b->start->y) / b->direction->y < 0) return 0;

	Point* p = new Point(x, y);
	points.push_back(p);
	return p;
}


