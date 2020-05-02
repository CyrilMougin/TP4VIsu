#include <iostream>

class Quadrilateral {
public:
    // VARIABLES
    Point* A;
    Point* B;
    Point* C;
    Point* D;

    Edge* AB;
    Edge* BC;
    Edge* CD;
    Edge* DA;

    Edge* InternEdge;

    // CONSTRUCTEUR
    Quadrilateral(Point* pa, Point* pb, Point* pc, Point* pd) {
        A = pa;
        B = pb;
        C = pc;
        D = pd;

        AB = new Edge(pa, pb);
        BC = new Edge(pb, pc);
        CD = new Edge(pc, pd);
        DA = new Edge(pd, pa);
        
        InternEdge = new Edge(pa, pc);
    }
};