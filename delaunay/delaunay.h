#include <iostream>
#include <list>
#include <queue>

#include "triangle.h"
#include "quadrilateral.h"

namespace del {
    
    typedef std::list<Triangle*> Triangles;
    typedef std::list<Point*> Points;
    typedef std::list<Edge*> Edges;

    class Delaunay {
    public:
        // VARIABLES
        Edges* list_edges;
        Points* list_points;
        Triangles* list_triangles;

        std::priority_queue<Point*> queue;

        // CONSTRUCTEUR
        Delaunay();

        // METHODES
        Edges* DelaunayTriangulation(Points* list_sites);
        std::list<Triangle*> SearchTriangle(Point* point);
        std::list<Triangle*> SearchLegalEdge(std::list<Triangle*> triangles);
        
        Point* GetPointFromTriangle(Edge* common_edge);
        double GetLength(Point* a, Point* b);
        double GetDeterminant(Point* A, Point* B);
        bool GetSegmentsIntersection(Edge* a, Edge* b);
        Triangle* SetFirstTriangle(Points* list_points);
    };
}