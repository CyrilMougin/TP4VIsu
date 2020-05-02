#include <iostream>

#include "triangle.h"

Triangle::Triangle() {
    A = 0;
    B = 0;
    C = 0;

    AB = 0;
    BC = 0;
    CA = 0;

    is_legal = false;
}

Triangle::Triangle(Point* sa, Point* sb, Point* sc, bool is) {
    A = sa;
    B = sb;
    C = sc;

    AB = new Edge(sa, sb);
    BC = new Edge(sb, sc);
    CA = new Edge(sc, sa);

    is_legal = is;
}

Point* Triangle::GetCentreCercle(Triangle* tr) {
    // Retourne le centre du cercle circonscrit au triangle
    Point* p1 = tr->A;
    Point* p2 = tr->B;
    Point* p3 = tr->C;

    // Equation de mediatrices
    double a1 = - (p2->x - p1->x) / (p2->y - p1->y);
    double b1 = ((p2->x - p1->x) * (p2->x + p1->x)) / (2 * (p2->y - p1->y)) + (p2->y + p1->y) / 2;

    double a2 = - (p3->x - p2->x) / (p3->y - p2->y);
    double b2 = ((p3->x - p2->x) * (p3->x + p2->x)) / (2 * (p3->y - p2->y)) + (p3->y + p2->y) / 2;

    // Coordonee du centre
    double xc = (b2 - b1) / (- a1 + a2);
    double yc = a1 * xc + b1;

    Point* cercle = new Point(xc, yc);
    
    return cercle;
}

bool Triangle::EdgesAreEqual(Edge* a, Edge* b) {
    // Verifie si deux aretes sont equivalentes 
    if(((a->start->x == b->start->x) && (a->start->y == b->start->y) && (a->finish->x == b->finish->x) && (a->finish->y == b->finish->y)) || 
    ((a->start->x == b->finish->x) && (a->start->y == b->finish->y) && (a->finish->x == b->start->x) && (a->finish->y == b->start->y))) {
        return true;
    }else {
        return false;
    }
}