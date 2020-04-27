// Inspire de : Fortune’s algorithm and implementation
// http://blog.ivank.net/fortunes-algorithm-and-implementation.html#impl_cpp

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

    Edge(Point* start_data, Point* a_data, Point* b_data) {
        start = start_data;
        finish = 0;
        direction = new Point(b_data->point.y - a_data->point.y, -(b_data->point.x - a_data->point.x), 0);
        left = a_data;
        right = b_data;

        twin = 0;
    }
};