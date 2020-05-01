#include <iostream>

class Triangle {
public:
    // VARIABLES
    Point* A;       // Sommet A
    Point* B;       // Sommet B
    Point* C;       // Sommet C

    Edge* AB;       // Arete AB du triangle
    Edge* BC;       // Arete BC du triangle
    Edge* CA;       // Arete CA du triangle

    bool is_legal;  // Le traingle est 'legal'
    
    // CONSTRUCTEUR
    Triangle(Point* sa, Point* sb, Point* sc, bool is) {
        A = sa;
        B = sb;
        C = sc;

        AB = new Edge(sa, sb);
        BC = new Edge(sb, sc);
        CA = new Edge(sc, sa);

        is_legal = is;
    }
};