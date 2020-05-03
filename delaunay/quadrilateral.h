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
    Quadrilateral() {
        A = 0;
        B = 0;
        C = 0;
        D = 0;

        AB = 0;
        BC = 0;
        CD = 0;
        DA = 0;
        
        InternEdge = 0;
    }
    
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