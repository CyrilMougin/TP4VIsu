// Inspire de : 
// Fortune’s algorithm and implementation : http://blog.ivank.net/fortunes-algorithm-and-implementation.html
// Geometrie Algorithmique : http://www.cgeo.ulg.ac.be/CG/CG_07.pdf
// Diagramme de Voronoi : https://perso.telecom-paristech.fr/dufourd/pact_archives/projet-2011-52/le-projet/avancement/solution-simplifiee/diagramme-de-voronoi/
// Intersection entre deux droites : https://calculis.net/intersection

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <math.h>

#include "voronoi.h"

Voronoi::Voronoi() {}

std::list<Edge*> Voronoi::voronoi_diagram(std::set<Point*> set_sites, int w, int h) {
    // Corps de l'algorithme de Fortune

    width = w;
	height = h;

    // Initialiser la queue Q en fonction des valeurs y (ordre decroissant) 
    for(auto site = set_sites.begin(); site != set_sites.end(); site++) {
        queue.push(new Event(*site, true));
    }

    // Initialiser la liste de bords D
    std::cout << "list_edges size : " << list_edges.size() << std::endl;

    while(!queue.empty()) {
        // Recuperer le premier element de la queue et l'enlever de cette derniere
        Event* event = queue.top();
        queue.pop();

        std::cout << "Evenement de la queue : valeur de y : " << event->y << std::endl;
        y_beach = event->point->y;

        // Verifier si l'element est un site
        if(event->is_a_site_event) {
            std::cout << "L'element est un site" << std::endl;

            handle_site_event(event->point);

        }else {
            std::cout << "L'element n'est pas un site" << std::endl;

            handle_circle_event(event->parable);
        }
    }
    /*
    FinishEdge(line);
    
    std::cout << "list_edges size : " << list_edges.size() << std::endl;

    for (auto edge = list_edges.begin(); edge != list_edges.end(); edge++) {
        Edge* new_edge = *edge;

		if (new_edge->twin) {
			new_edge->start = new_edge->twin->finish;
			delete new_edge->twin;
		}
	}
    */
    return list_edges;
}

void Voronoi::handle_site_event(Point* site) {
    // Si l'abre est vide, on ajoute le site a l'arbre (qui sera donc la racine)
    std::cout << "1" << std::endl;
    if(!line) {
        line = new BeachLine(site);

        return;
    }
    std::cout << "2" << std::endl;
    // Recuperer la parabole en dessous du site
    //BeachLine* parable = search(line, site->x);
    BeachLine* parable = GetParabolaByX(site->x);
    std::cout << "3" << std::endl;
    // Enlever l'evenement s'il n'a pas lieu d'etre
    if (parable->circle_event) {
		parable->circle_event = 0;
	}
    std::cout << "4" << std::endl;
    // Remplacer la feuille de l'arbre par par un sous-arbre avec trois feuilles 
    BeachLine* a = new BeachLine(parable->site);
    BeachLine* b = new BeachLine(site);
    BeachLine* c = new BeachLine(parable->site);

    parable->left = new BeachLine();
    parable->right = c;

    parable->left->left = a;
    parable->left->right = b;
    std::cout << "5" << std::endl;
    // Créer deux nouvelles demi-arêtes dans le DCEL
    Point* start = new Point(site->x, get_y_parable(parable->site, site->x));

    Edge* xl = new Edge(start, parable->site, site);
    Edge* xr = new Edge(start, site, parable->site);

    xl->twin = xr;
    list_edges.push_back(xl);

    parable->edge = xr;
    parable->is_a_leaf = false;
    parable->left->edge = xl;
    std::cout << "6" << std::endl;
    // Verifier que les nouveau triplets d'arcs consecutifs avec l'arc associe situes en dessous (a) ou au dessus (c)
    // correspondent a deux aretes convergentes
    check_circle_event(a);
    check_circle_event(c);

}

void Voronoi::handle_circle_event(BeachLine* parable) {
    BeachLine* l = parable->get_left(parable);
    BeachLine* r = parable->get_right(parable);

    if(l->circle_event) {
        l->circle_event = 0;
    }
    if(r->circle_event) {
        r->circle_event = 0;
    }

    Point* s = new Point(parable->circle_event->point->x, get_y_parable(l->site, parable->circle_event->point->x));

    Edge* xl = parable->get_left_parent(parable)->edge;
    Edge* xr = parable->get_right_parent(parable)->edge;

    xl->finish = s;
    xr->finish = s;

    check_circle_event(l);
    check_circle_event(r);
}

void Voronoi::check_circle_event(BeachLine* parable) {
    std::cout << "7" << std::endl;
    BeachLine* l = parable->get_left(parable);
    BeachLine* r = parable->get_right(parable);
    std::cout << "7.1" << std::endl;
    if(!l || !r || l->site == r->site) {
        return;
    }
    std::cout << "8" << std::endl;
    Edge* xl = parable->get_left_parent(parable)->edge;
    Edge* xr = parable->get_right_parent(parable)->edge;

    Point* s = get_edge_intersection(xl, xr);

    if(s == 0) {
        return;
    }
    std::cout << "9" << std::endl;
    float length = get_length_site(s, l->site);

    if(s->y + length < y_beach) {
        return;
    }
    std::cout << "10" << std::endl;
    Event* e = new Event(new Point(s->x, s->y - length), false);

    r->circle_event = e;
    e->parable = parable;
    std::cout << "11" << std::endl;
    queue.push(e);
}

BeachLine* Voronoi::search(BeachLine* line, int val) {
    // Rechercher une valeur dans l'arbre

    BeachLine* currentNode = line;

    // Parcourir jusqu'a une feuille
    while(currentNode != NULL) {
        // Checker si la valeur est inférieure a celle du noeud courant
        if(val < currentNode->site->x) {
            // Mettre a jour le noeud courant (cote sous-arbre gauche)
            currentNode = currentNode->left;

        // Checker si la valeur est superieure a celle du noeud courant
        }else if(val > currentNode->site->x) {
            // Mettre a jour le noeud courant (cote sous-arbre droit)
            currentNode = currentNode->right;
        
        // Valeur trouvee
        }else {
            return currentNode;
        }
    }
    
    return 0;
}

float Voronoi::get_length_site(Point* s, Point* site) {
    // Retrourne la distance entre s et le site (rayon du cercle)

    return sqrt(pow(site->x - s->x, 2) + pow(site->y - s->y, 2));
}

float Voronoi::get_length_beach(float y_data, float y_beach) {
	// Retourne la distance entre le site et la plage
	
    return y_beach - y_data;
}

float Voronoi::get_y_parable(Point* point, float x) {
	// Retourne la valeur de 'y' vis a vis de l'equation de la parabole
    
    float p = get_length_beach(point->y, y_beach);

	return pow(x - point->x, 2) / (2 * p) + point->y;
}

Point* Voronoi::get_edge_intersection(Edge* xl, Edge* xr) {
    // Retrourne le point d'intersection s'il y en a un
    
    if(xl->a != xr->a) {
        // Calculer les coordonnees du point d'intersection
        float xj = (xr->b - xl->b) / (xl->a - xr->a);
        float yj = xr->a * xj + xr->b;

        Point* point = new Point(xj, yj);

        return point;

    }else {
        return 0;
    }
}

void Voronoi::FinishEdge(BeachLine* n)
{
	if (n->is_a_leaf) { delete n; return; }
	double mx;
	if (n->edge->direction->x > 0.0) {
        mx = std::max((float)width, n->edge->start->x + 10);
    }else {
    	mx = std::min((float)0, n->edge->start->x - 10);
    }

	Point* end = new Point(mx, mx * n->edge->a + n->edge->b);
	n->edge->finish = end;

	FinishEdge(n->left);
	FinishEdge(n->right);
	delete n;
}

double	Voronoi::GetXOfEdge(BeachLine* par, double y)
{
	BeachLine* left = par->get_left_child(par);
	BeachLine* right = par->get_right_child(par);

	Point* p = left->site;
	Point* r = right->site;

	double dp = 2.0 * (p->y - y);
	double a1 = 1.0 / dp;
	double b1 = -2.0 * p->x / dp;
	double c1 = y + dp / 4 + p->x * p->x / dp;

	dp = 2.0 * (r->y - y);
	double a2 = 1.0 / dp;
	double b2 = -2.0 * r->x / dp;
	double c2 = y_beach + dp / 4 + r->x * r->x / dp;

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
	BeachLine* par = line;
	double x = 0.0;

	while (!par->is_a_leaf) // projdu stromem dokud nenarazím na vhodný list
	{
		x = GetXOfEdge(par, y_beach);
		if (x > xx) par = par->left;
		else par = par->right;
	}
	return par;
}
