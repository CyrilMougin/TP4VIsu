#include <iostream>
#include <algorithm>
#include <set>
#include <math.h>

#include "voronoi.h"

using namespace vor;

Voronoi::Voronoi() {
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
		if (e->is_a_site_event) InsertParabola(e->point);
		else RemoveParabola(e);
		delete(e);
	}

	FinishEdge(root);

	for (Edges::iterator i = edges->begin(); i != edges->end(); ++i)
	{
		if ((*i)->neighbour)
		{
			(*i)->start = (*i)->neighbour->finish;
			delete (*i)->neighbour;
		}
	}

	return edges;
}

void	Voronoi::InsertParabola(Point* p)
{
	if (!root) { root = new BeachLine(p); return; }

	if (root->is_a_leaf && root->site->y - p->y < 1) // degenerovaný pøípad - obì spodní místa ve stejné výšce
	{
		Point* fp = root->site;
		root->is_a_leaf = false;
		root->SetLeft(new BeachLine(fp));
		root->SetRight(new BeachLine(p));
		Point* s = new Point((p->x + fp->x) / 2, height); // zaèátek hrany uprostøed míst
		points.push_back(s);
		if (p->x > fp->x) root->edge = new Edge(s, fp, p); // rozhodnu, který vlevo, který vpravo
		else root->edge = new Edge(s, p, fp);
		edges->push_back(root->edge);
		return;
	}

	BeachLine* par = GetParabolaByX(p->x);

	if (par->circle_event)
	{
		deleted.insert(par->circle_event);
		par->circle_event = 0;
	}

	Point* start = new Point(p->x, GetY(par->site, p->x));
	points.push_back(start);

	Edge* el = new Edge(start, par->site, p);
	Edge* er = new Edge(start, p, par->site);

	el->neighbour = er;
	edges->push_back(el);

	// pøestavuju strom .. vkládám novou parabolu
	par->edge = er;
	par->is_a_leaf = false;

	BeachLine* p0 = new BeachLine(par->site);
	BeachLine* p1 = new BeachLine(p);
	BeachLine* p2 = new BeachLine(par->site);

	par->SetRight(p2);
	par->SetLeft(new BeachLine());
	par->Left()->edge = el;

	par->Left()->SetLeft(p0);
	par->Left()->SetRight(p1);

	CheckCircle(p0);
	CheckCircle(p2);
}

void	Voronoi::RemoveParabola(Event* e)
{
	BeachLine* p1 = e->parable;

	BeachLine* xl = BeachLine::get_left_parent(p1);
	BeachLine* xr = BeachLine::get_right_parent(p1);

	BeachLine* p0 = BeachLine::get_left_child(xl);
	BeachLine* p2 = BeachLine::get_right_child(xr);

	if (p0 == p2) std::cout << "chyba - pravá a levá parabola má stejné ohnisko!\n";

	if (p0->circle_event) { deleted.insert(p0->circle_event); p0->circle_event = 0; }
	if (p2->circle_event) { deleted.insert(p2->circle_event); p2->circle_event = 0; }

	Point* p = new Point(e->point->x, GetY(p1->site, e->point->x));
	points.push_back(p);

	xl->edge->finish = p;
	xr->edge->finish = p;

	BeachLine* higher;
	BeachLine* par = p1;
	while (par != root)
	{
		par = par->parent;
		if (par == xl) higher = xl;
		if (par == xr) higher = xr;
	}
	higher->edge = new Edge(p, p0->site, p2->site);
	edges->push_back(higher->edge);

	BeachLine* gparent = p1->parent->parent;
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

void Voronoi::FinishEdge(BeachLine* line) {
	if (line->is_a_leaf) {
		delete line;
		return;
	}

	double mx;
	
	if(line->edge->direction->x > 0.0) {
		mx = std::max(width, line->edge->start->x + 10);
	}else {
		mx = std::min(0., line->edge->start->x - 10);
	}

	Point* finish = new Point(mx, mx * line->edge->a + line->edge->b);
	
	line->edge->finish = finish;
	points.push_back(finish);

	FinishEdge(line->Left());
	FinishEdge(line->Right());
	
	delete line;
}

double	Voronoi::GetXOfEdge(BeachLine* par, double y)
{
	BeachLine* left = BeachLine::get_left_child(par);
	BeachLine* right = BeachLine::get_right_child(par);

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

BeachLine* Voronoi::GetParabolaByX(double xx)
{
	BeachLine* par = root;
	double x = 0.0;

	while (!par->is_a_leaf) // projdu stromem dokud nenarazím na vhodný list
	{
		x = GetXOfEdge(par, ly);
		if (x > xx) par = par->Left();
		else par = par->Right();
	}
	return par;
}

double	Voronoi::GetY(Point* p, double x) {
	// Retourne la valeur de 'y' vis a vis de l'equation de la parabole

	double length = p->y - ly;

	double a = 1 / (2 * length);
	double b = -p->x / length;
	double c = ly + 2 * length / 4 + p->x * p->x / (2 * length);

	// De la forme ax² + bx + c
	return a * pow(x, 2) + b * x + c; 
}

void	Voronoi::CheckCircle(BeachLine* b)
{
	BeachLine* lp = BeachLine::get_left_parent(b);
	BeachLine* rp = BeachLine::get_right_parent(b);

	BeachLine* a = BeachLine::get_left_child(lp);
	BeachLine* c = BeachLine::get_right_child(rp);

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
	b->circle_event = e;
	e->parable = b;
	queue.push(e);
}

Point* Voronoi::GetEdgeIntersection(Edge* a, Edge* b) {
	// Cas ou les droites sont paralleles
	if (a->a == b->a) {
		return 0;
	}

	// Calculer les coordonnes du point d'intersection
	double x = (b->b - a->b) / (a->a - b->a);
	double y = a->a * x + a->b;

	if ((x - a->start->x) / a->direction->x < 0 || (y - a->start->y) / a->direction->y < 0) {
		return 0;
	}

	if ((x - b->start->x) / b->direction->x < 0 || (y - b->start->y) / b->direction->y < 0) {
		return 0;
	}

	Point* p = new Point(x, y);
	points.push_back(p);
	
	return p;
}