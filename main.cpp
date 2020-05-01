#include "delaunay/test.cpp"

int main() {

    Point* A = new Point(1,1);
    Point* B = new Point(4,4);

    //Point* C = new Point(1,2);
    //Point* D = new Point(4,5);
    //Point* C = new Point(4,5);
    //Point* D = new Point(5,6);
    Point* C = new Point(2,3);
    Point* D = new Point(9,4);
    
    //Point* C = new Point(2,3);
    //Point* D = new Point(4,1);

    Edge* AB = new Edge(A, B);
    Edge* CD = new Edge(C, D);

    bool verdict = GetSegmentsIntersection(AB, CD);

    return 0;
}