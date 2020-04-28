// Inspire de : 
// Fortune’s algorithm and implementation : http://blog.ivank.net/fortunes-algorithm-and-implementation.html
// Equation de droite : http://labomath.free.fr/qcms/seconde/equadroite/droites.pdf

#include <iostream>

#include "point.cpp"

class Edge {
public:
    Point* start;       // Point de depart
    Point* finish;      // Point d'arrivee
    Point* direction;   // Direction
    Point* left;        // Point suivant (par convention du sens antihoraire)
    Point* right;       // Point précédent (par convention du sens antihoraire)

    Edge* twin;         // Arete jumelle

    float a;            // 'a' de l'equation de droite 'ax + b'
    float b;            // 'b' de l'equation de droite 'ax + b'

    Edge(Point* start_data, Point* a_data, Point* b_data) {
        start = start_data;
        finish = 0;
        direction = new Point(b_data->point.y - a_data->point.y, -(b_data->point.x - a_data->point.x));
        left = a_data;
        right = b_data;

        twin = 0;
        
        // a = (yb - ya) / (xb - xa)
        a = (b_data->point.y - a_data->point.y) / (b_data->point.x - a_data->point.x);
        // b = y - ax avec (x,y) coordonnees d'un point passant par la droite
        b = start_data->point.y - a * start_data->point.x;
    }
};