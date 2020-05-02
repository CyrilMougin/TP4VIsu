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
        Edges* list_edges;                  // Liste des aretes
        Points* list_points;                // Liste des sommets
        Triangles* list_triangles;          // Liste des tiangles

        std::priority_queue<Point*> queue;  // Queue

        // CONSTRUCTEUR
        Delaunay();

        // METHODES
        Edges* DelaunayTriangulation(Points* list_sites);                       // Corps de la triangulation de Delaunay
        std::list<Triangle*> SearchTriangle(Point* point);                      // Retrourne les nouveaux triangles consitues a partir d'un point
        std::list<Triangle*> SearchLegalEdge(std::list<Triangle*> triangles);   // Verfie si les aretes d'un triangle sont legales ou non
        
        Point* GetPointFromTriangle(Edge* common_edge);                         // Retourne le sommet oppose a l'arete commune
        double GetLength(Point* a, Point* b);                                   // Calcule la distance entre deux points
        double GetDeterminant(Point* A, Point* B);                              // Calcule le determinant entre deux aretes
        bool GetSegmentsIntersection(Edge* a, Edge* b);                         // Verfie s'il y a une intersection (true) ou pas (false) entre deux aretes
        Triangle* SetFirstTriangle(Points* list_points);                        // Retourne le triangle englobant tous les points
        Point* GetEdgeIntersection(Edge* a, Edge* b);                           // Calcul le point d'intersection entre deux aretes
    };
}