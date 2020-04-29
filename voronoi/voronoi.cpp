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

void Voronoi::voronoi_diagram(std::set<Point*> set_sites, int w, int h) {
    // Corps de l'algorithme de Fortune

    width = w;
	height = h;

    // Initialiser la queue Q en fonction des valeurs y (ordre decroissant) 
    for(auto site = set_sites.begin(); site != set_sites.end(); site++) {
        queue.push(new Event(*site, true));
    }

    // Initialiser la liste de bords D
    std::list<Edge*> list_edges;

    while(!queue.empty()) {
        // Recuperer le premier element de la queue et l'enlever de cette derniere
        Event* event = queue.top();
        queue.pop();

        std::cout << event->y << std::endl;

        // Verifier si l'element est un site
        if(event->is_a_site_event) {
            std::cout << "L'element est un site" << std::endl;

            handle_site_event(event->point);

        }else {
            std::cout << "L'element n'est pas un site" << std::endl;

            handle_circle_event(event->parable);
        }
    }

}

void Voronoi::handle_site_event(Point* site) {
    // Si l'abre est vide, on ajoute le site a l'arbre (qui sera donc la racine)
    if(!line) {
        line = new BeachLine(site);

        return;
    }

    // Recuperer la parabole en dessous du site
    BeachLine* parable = search(line, site->x);

    // Enlever l'evenement s'il n'a pas lieu d'etre
    if (parable->circle_event) {
		parable->circle_event = 0;
	}

    // Remplacer la feuille de l'arbre par par un sous-arbre avec trois feuilles 
    BeachLine* a = new BeachLine(parable->site);
    BeachLine* b = new BeachLine(site);
    BeachLine* c = new BeachLine(parable->site);

    parable->left = new BeachLine();
    parable->right = c;

    parable->left->left = a;
    parable->left->right = b;

    // Créer deux nouvelles demi-arêtes dans le DCEL
    Point* start = new Point(site->x, get_y_parable(parable->site, site->x));

    Edge* xl = new Edge(start, parable->site, site);
    Edge* xr = new Edge(start, site, parable->site);

    xl->twin = xr;

    parable->edge = xr;
    parable->is_a_leaf = false;
    parable->left->edge = xl;
    
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
    BeachLine* l = parable->get_left(parable);
    BeachLine* r = parable->get_right(parable);

    if(!l || !r || l->site == r->site) {
        return;
    }

    Edge* xl = parable->get_left_parent(parable)->edge;
    Edge* xr = parable->get_right_parent(parable)->edge;

    Point* s = get_edge_intersection(xl, xr);

    if(s == 0) {
        return;
    }

    float length = get_length_site(s, l->site);

    if(s->y + length < y_beach) {
        return;
    }

    Event* e = new Event(new Point(s->x, s->y - length), false);

    r->circle_event = e;
    e->parable = parable;

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
