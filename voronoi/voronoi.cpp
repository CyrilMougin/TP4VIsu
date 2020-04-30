#include <iostream>
#include <algorithm>
#include <set>
#include <math.h>

#include "voronoi.h"

using namespace vor;

Voronoi::Voronoi() {
	list_edges = 0;
}

Edges* Voronoi::VoronoiDiagram(Points* v, int w, int h) {
	// Corps de l'algorithme de Fortune

	list_sites = v;
	width = w;
	height = h;
	tree = 0;

	// Initialiser la queue Q en fonction des valeurs y (ordre decroissant) 
	for (auto i = list_sites->begin(); i != list_sites->end(); ++i) {
		Point* new_point = *i;

		queue.push(new Event(new_point, true));
	}

	// Initialiser la liste de bords D
	list_edges = new Edges();

	// Recuperer le premier element de la queue et l'enlever de cette derniere
	Event* event;
	
	while (!queue.empty()) {
		// Recuperer le premier element de la queue et l'enlever de cette derniere
		event = queue.top();
		queue.pop();

		beach = event->point->y;

		// Verifier si l'element est un site
		if (event->is_a_site_event) {
            std::cout << "L'element est un site" << std::endl;

			HandleSiteEvent(event->point);

		}else {
			std::cout << "L'element n'est pas un site" << std::endl;

			HandleCircleEvent(event->parable);
		}

		delete(event);
	}

	FinishEdge(tree);

	// "Pour chaque couple de demi-aretes, le debut de l'une est la fin de l'autre"
	// Fixer la fin d'une arete au debut de sa soeur et la supprimer
	for (auto i = list_edges->begin(); i != list_edges->end(); ++i) {
		Edge* new_edge = *i;

		if (new_edge->neighbour) {
			new_edge->start = new_edge->neighbour->finish;
			
			delete new_edge->neighbour;
		}
	}

	return list_edges;
}

void Voronoi::HandleSiteEvent(Point* point) {
	// Si l'abre est vide, on ajoute le site a l'arbre (qui sera donc la racine)
	if (!tree) { 
		tree = new BeachLine(point); 
		
		return; 
	}

	// --- PAS TOUT COMPRIS ----------------------------------
	if (tree->is_a_leaf && tree->site->y - point->y < 1) {
		Point* fp = tree->site;
		tree->is_a_leaf = false;

		tree->SetLeft(new BeachLine(fp));
		tree->SetRight(new BeachLine(point));

		Point* s = new Point((point->x + fp->x) / 2, height);

		if (point->x > fp->x) {
			tree->edge = new Edge(s, fp, point);
		
		}else {
			tree->edge = new Edge(s, point, fp);
		}

		list_edges->push_back(tree->edge);
		
		return;
	}
	// -------------------------------------------------------

	// Recuperer la parabole en dessous du site
	BeachLine* parable = GetParable(point->x);

	// Enlever l'evenement s'il n'a pas lieu d'etre
	if (parable->circle_event) {
		parable->circle_event = 0;
	}

	// Remplacer la feuille de l'arbre par par un sous-arbre avec trois feuilles 
	BeachLine* a = new BeachLine(parable->site);
	BeachLine* b = new BeachLine(point);
	BeachLine* c = new BeachLine(parable->site);

	parable->SetLeft(new BeachLine());
	parable->SetRight(c);

	parable->Left()->SetLeft(a);
	parable->Left()->SetRight(b);

	// Créer deux nouvelles demi-arêtes dans le DCEL
	Point* start = new Point(point->x, GetYParable(parable->site, point->x));

	Edge* xl = new Edge(start, parable->site, point);
	Edge* xr = new Edge(start, point, parable->site);

	xl->neighbour = xr;
	list_edges->push_back(xl);

	parable->edge = xr;
	parable->is_a_leaf = false;
	parable->Left()->edge = xl;

	// Verifier que les nouveau triplets d'arcs consecutifs avec l'arc associe situes en dessous (a) ou au dessus (c)
    // correspondent a deux aretes convergentes
	CheckCircle(a);
	CheckCircle(c);
}

void Voronoi::HandleCircleEvent(BeachLine* parable) {
    BeachLine* l = BeachLine::get_left(parable);
    BeachLine* r = BeachLine::get_right(parable);

	if (l->circle_event) {
		l->circle_event = 0;
	}
	if (r->circle_event) {
		r->circle_event = 0;
	}

	Point* s = new Point(parable->circle_event->point->x, GetYParable(parable->site, parable->circle_event->point->x));

	Edge* xl = BeachLine::get_left_parent(parable)->edge;
	Edge* xr = BeachLine::get_right_parent(parable)->edge;

	xl->finish = s;
	xr->finish = s;

	// --- PAS TOUT COMPRIS ----------------------------------
    BeachLine* pl = BeachLine::get_left_parent(parable);
    BeachLine* pr = BeachLine::get_right_parent(parable);

	BeachLine* higher;
	BeachLine* par = parable;
	
	while (par != tree) {
		par = par->parent;
		if (par == pl) higher = pl;
		if (par == pr) higher = pr;
	}

	higher->edge = new Edge(s, l->site, r->site);
	list_edges->push_back(higher->edge);

	BeachLine* gparent = parable->parent->parent;
	if (parable->parent->Left() == parable) {
		if (gparent->Left() == parable->parent) {
			gparent->SetLeft(parable->parent->Right());
		}
		if (gparent->Right() == parable->parent) {
			gparent->SetRight(parable->parent->Right());
		}
	}else {
		if (gparent->Left() == parable->parent) {
			gparent->SetLeft(parable->parent->Left());
		}
		if (gparent->Right() == parable->parent) {
			gparent->SetRight(parable->parent->Left());
		}
	}

	delete parable->parent;
	delete parable;
	// -------------------------------------------------------

	CheckCircle(l);
	CheckCircle(r);
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

	FinishEdge(line->Left());
	FinishEdge(line->Right());
	
	delete line;
}

double	Voronoi::GetDiscriminantSolution(BeachLine* par, double y) {
	BeachLine* l = BeachLine::get_left_child(par);
	BeachLine* r = BeachLine::get_right_child(par);

	Point* pl = l->site;
	Point* pr = r->site;

	// Calcul des coeff pour la parabole de gauche
	double length_l = pl->y - y;

	double a_l = 1 / (2 * length_l);
	double b_l = -pl->x / length_l;
	double c_l = y + 2 * length_l / 4 + pl->x * pl->x / (2 * length_l);

	// Calcul des coeff pour la parabole de droite
	double length_r = pr->y - y;

	double a_r = 1 / (2 * length_r);
	double b_r = -pr->x / length_r;
	double c_r = y + 2 * length_r / 4 + pr->x * pr->x / (2 * length_r);

	// Difference entre les deux coeff de paraboles
	double a = a_l - a_r;
	double b = b_l - b_r;
	double c = c_l - c_r;

	// Discriminant
	double disc = pow(b, 2) - 4 * a * c;
	
	// Racines reelles du discriminant
	double x1 = (-b + sqrt(disc)) / (2 * a);
	double x2 = (-b - sqrt(disc)) / (2 * a);

	if (pl->y < pr->y) {
		return std::max(x1, x2);
	
	}else {
		return std::min(x1, x2);
	}

	return 0;
}

BeachLine* Voronoi::GetParable(double value) {
	BeachLine* parable = tree;

	// Parcourir jusqu'a une feuille
	while (!parable->is_a_leaf) {
		double x = GetDiscriminantSolution(parable, beach);
		
		if (value < x) {
			// Recuperer le sous-arbre de gauche (vis a vis de l'arbre de recherche binaire)
			parable = parable->Left();

		}else {
			// Recuperer le sous-arbre de droite (vis a vis du l'arbre de recherche binaire)
			parable = parable->Right();
		}
	}

	return parable;
}

double	Voronoi::GetYParable(Point* p, double x) {
	double length = p->y - beach;

	// Calcul des coeff
	double a = 1 / (2 * length);
	double b = -p->x / length;
	double c = beach + 2 * length / 4 + p->x * p->x / (2 * length);

	// De la forme ax² + bx + c
	return a * pow(x, 2) + b * x + c; 
}

double Voronoi::GetSiteLength(Point* s, Point* site) {
    // Retrourne la distance entre s et le site (rayon du cercle)

    return sqrt(pow(site->x - s->x, 2) + pow(site->y - s->y, 2));
}

void Voronoi::CheckCircle(BeachLine* parable) {
	BeachLine* l = BeachLine::get_left(parable);
	BeachLine* r = BeachLine::get_right(parable);
	
	if(!l || !r || l->site == r->site) {
        return;
    }

	Edge* xl = BeachLine::get_left_parent(parable)->edge;
	Edge* xr = BeachLine::get_right_parent(parable)->edge;

	Point* s = GetEdgeIntersection(xl, xr);

	if (s == 0) {
		return;
	}

	double length = GetSiteLength(s, l->site);

	if (s->y - length >= beach) {
		return;
	}

	Event* e = new Event(new Point(s->x, s->y - length), false);

	parable->circle_event = e;
	e->parable = parable;
	
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
	
	return p;
}