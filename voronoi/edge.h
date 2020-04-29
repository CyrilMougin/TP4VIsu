// Inspire de : 
// Fortune’s algorithm and implementation : http://blog.ivank.net/fortunes-algorithm-and-implementation.html
// Equation de droite : http://labomath.free.fr/qcms/seconde/equadroite/droites.pdf

#include <iostream>

class Edge {
public:
    // VARIABLES
    Point* start;       // Point de depart
    Point* finish;      // Point d'arrivee
    Point* direction;   // Direction
    Point* left;        // Point suivant (par convention du sens antihoraire)
    Point* right;       // Point précédent (par convention du sens antihoraire)

    Edge* neighbour;         // Arete jumelle

    double a;            // 'a' de l'equation de droite 'ax + b'
    double b;            // 'b' de l'equation de droite 'ax + b'

    // CONSTRUCTEUR
    Edge(Point* start_data, Point* a_data, Point* b_data) {
        start = start_data;
        finish = 0;
        direction = new Point(b_data->y - a_data->y, a_data->x - b_data->x);
        left = a_data;
        right = b_data;

        neighbour = 0;
        
        // a = (yb - ya) / (xb - xa)
        a = (b_data->x - a_data->x) / (a_data->y - b_data->y);
        // b = y - ax avec (x,y) coordonnees d'un point passant par la droite
        b = start_data->y - a * start_data->x;
    }

    ~Edge() {
		delete direction;
	}
};