#include "point.h"
#include "edge.h"

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
    
    // CONSTRUCTEURS
    Triangle();
    Triangle(Point* sa, Point* sb, Point* sc, bool is);

    // METHODES
    static Point* GetCentreCercle(Triangle* tr);
    static bool EdgesAreEqual(Edge* a, Edge* b);
};

