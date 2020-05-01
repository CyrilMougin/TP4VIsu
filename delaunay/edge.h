#include <iostream>

class Edge {
public:
    // VARIABLES
    Point* start;       // Point de depart
    Point* finish;      // Point d'arrivee

    Point* direction;

    double a;           // 'a' de l'equation de droite 'ax + b'
    double b;           // 'b' de l'equation de droite 'ax + b'

    // CONSTRUCTEUR
    Edge(Point* a_data, Point* b_data) {
        start = a_data;
        finish = b_data;
        
        direction = new Point(b_data->x - a_data->x, b_data->y - a_data->y);

        // a = (yb - ya) / (xb - xa)
        a = (b_data->x - a_data->x) / (a_data->y - b_data->y);
        // b = y - ax avec (x,y) coordonnees d'un point passant par la droite
        b = start->y - a * start->x;
    }

};