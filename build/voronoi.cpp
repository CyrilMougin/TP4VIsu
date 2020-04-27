// Inspire de : 
// Fortune’s algorithm and implementation : http://blog.ivank.net/fortunes-algorithm-and-implementation.html#impl_cpp
// Geometrie Algorithmique : http://www.cgeo.ulg.ac.be/CG/CG_07.pdf
// Diagramme de Voronoi : https://perso.telecom-paristech.fr/dufourd/pact_archives/projet-2011-52/le-projet/avancement/solution-simplifiee/diagramme-de-voronoi/

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <math.h>
#include <queue>
#include <set>

#include "edge.cpp"
#include "event.cpp"

float length(Data beachline_point, Data source_point);

float y_beach;
std::priority_queue<Event*> queue;
std::set<Event*> set_events_deleted;
BeachLine* line;

std::list<Data> summit(std::list<Data> summit_data, std::vector<Data> beachline_data, std::vector<Data> source_data) {
    // Retourne la liste des sommets du diagramme
    std::list<Data> current_data = summit_data;

    for(int i = 0; i < beachline_data.size(); i++) {
        std::vector<float> length_data;

        // Ajouter toutes les distances en mémoire
        for(int j = 0; j < source_data.size(); i++) {
            length_data.push_back(length(beachline_data[i], source_data[j]));
        }

        // Recuperer la valeur minimale
        float min_element = *std::min_element(length_data.begin(), length_data.end());

        // Compter le nombre d'occurence de la valeur minimale
        int nb_min_element = std::count(length_data.begin(), length_data.end(), min_element);

        if(nb_min_element >= 3) {
            current_data.push_back(beachline_data[i]);
        } 
    }

    return current_data;
}

float length(Data beachline_point, Data source_point) {
	// Retourne la distance entre deux points
	return sqrt(pow(source_point.x - beachline_point.x, 2) + pow(source_point.y - beachline_point.y, 2));
}

void voronoi_diagram(std::set<Point*>* set_sites) {

    // Initialiser la queue Q en fonction des valeurs y (ordre decroissant) 
    for(auto site = set_sites->begin(); site != set_sites->end(); site++) {
        queue.push(new Event(*site, true));
    }

    // Initialiser la liste de bords D
    std::list<Edge*> list_edges;

    while(!queue.empty()) {
        // Recuperer le primer element de la queue et l'enlever de cette derniere
        Event* event = queue.top();
        queue.pop();

        // Verifier si l'element est un site
        if(event->is_a_site_event) {
            std::cout << "L'element est un site" << std::endl;

            handle_site_event(event->point);

        }else {
            std::cout << "L'element n'est pas un site" << std::endl;
        }
    }

}

void handle_site_event(Point* site) {

    // Si l'abre est vide, on ajoute le site a l'arbre (qui sera donc la racine)
    if(!line) {
        line = new BeachLine(site);

        return;
    }

    // Recuperer la parabole en dessous du site
    BeachLine* parable = search(line, site->point.x);

    // 
    if (parable->circle_event) {
		set_events_deleted.insert(parable->circle_event);
		parable->circle_event = 0;
	}

    BeachLine* a = new BeachLine(parable->site);
    BeachLine* b = new BeachLine(site);
    BeachLine* c = new BeachLine(parable->site);

    // Remplacer la feuille de l'arbre par par un sous-arbre avec trois feuilles 
    parable->left = new BeachLine();
    parable->right = c;

    parable->left->left = a;
    parable->left->right = b;

    // Créer deux nouvelles demi-arêtes dans le DCEL
    Point* start = new Point(site->point.x, get_y_parable(parable->site, site->point.x));

    Edge* xl = new Edge(start, parable->site, site);
    Edge* xr = new Edge(start, site, parable->site);
    
    // Verifier que les nouveau triplets d'arcs consecutifs avec l'arc associe situes en dessous (a) ou au dessus (c)
    // correspondent a deux aretes convergentes
    check_circle_event(a);
    check_circle_event(c);

}

void check_circle_event(BeachLine* parable) {

}

// Rechercher une valeur dans l'arbre
BeachLine* search(BeachLine* line, int val) {
    BeachLine* currentNode = line;

    // Parcourir jusqu'a une feuille
    while(currentNode != NULL) {
        // Checker si la valeur est inférieure a celle du noeud courant
        if(val < currentNode->site->point.x) {
            // Mettre a jour le noeud courant (cote sous-arbre gauche)
            currentNode = currentNode->left;

        // Checker si la valeur est superieure a celle du noeud courant
        }else if(val > currentNode->site->point.x) {
            // Mettre a jour le noeud courant (cote sous-arbre droit)
            currentNode = currentNode->right;
        
        // Valeur trouvee
        }else {
            return currentNode;
        }
    }
    
    return 0;
}

float get_length(float y_data, float y_beach) {
	// Retourne la distance entre le site et la plage
	return y_beach - y_data;
}

float get_y_parable(Point* point, float x) {
	// Retourne 'y' vis a vis de l'equation de la parabole
    float p = get_length(point->point.y, y_beach);

	return pow(x - point->point.x, 2) / (2 * p) + point->point.y;
}


