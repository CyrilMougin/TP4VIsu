#include <iostream>
#include <numeric>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>
#include <math.h>

#include "delaunay.h"

using namespace del;

Delaunay::Delaunay() {
    list_edges = 0;
}

Edges* Delaunay::DelaunayTriangulation(Points* list_sites) {
    // Initialisation avec un triangle englobant tous les points
    Triangle* initial_triangle = SetFirstTriangle(list_sites);

    // Initialiser la queue
	for (auto i = list_sites->begin(); i != list_sites->end(); ++i) {
		Point* new_point = *i;

		queue.push(new_point);
	}

    // Initialiser la liste de triangles T
    list_triangles = new Triangles();

    list_triangles->push_back(initial_triangle);

    // Initialiser la liste de bords D
	list_edges = new Edges();

    list_edges->push_back(initial_triangle->AB);
    list_edges->push_back(initial_triangle->BC);
    list_edges->push_back(initial_triangle->CA);

    // Initialiser la liste de points P
    list_points = new Points();

    list_points->push_back(initial_triangle->A);
    list_points->push_back(initial_triangle->B);
    list_points->push_back(initial_triangle->C);

    Point* point;

    while (!queue.empty()) {
		// Recuperer le premier element de la queue et l'enlever de cette derniere
		point = queue.top();
		queue.pop();

        // Recuperer tous les triangles possibles avec le point
        std::list<Triangle*> new_triangles = SearchTriangle(point);

        // Verifier si les aretes sont legales
        std::list<Triangle*> triangles_to_recheck = SearchLegalEdge(new_triangles);

        while(triangles_to_recheck.size() != 0) {
            // Verifier si les aretes sont legales
            std::list<Triangle*> triangles_to_recheck = SearchLegalEdge(new_triangles);
        }
    }

    return list_edges;
}

std::list<Triangle*> Delaunay::SearchTriangle(Point* point) {
    Point* point_a = point;
    
    std::list<Triangle*> new_triangles;

    // Creer un nouveau triangle avec chaque arete deja existante
    for(auto e = list_edges->begin(); e != list_edges->end(); e++) {
        // Creer les sommets et les aretes du triangle
        Edge* edge_bc = *e;

        Point* point_b = edge_bc->start;
        Point* point_c = edge_bc->finish;

        Edge* edge_ab = new Edge(point_a, point_b);
        Edge* edge_ca = new Edge(point_c, point_a);

        bool is_intersection = false;
        
        // Verifier si les aretes du trainge coupe une autre arete deja existente
        for(auto i = list_edges->begin(); i != list_edges->end(); i++) {
            if(GetSegmentsIntersection(edge_ab, *i) || GetSegmentsIntersection(edge_ca, *i)) {
                is_intersection = true;
            }
        }

        // On ajoute le triangle si la condition precedente est verifiee
        if(!is_intersection) {
            new_triangles.push_back(new Triangle(point_a, point_b, point_c, false));
        }

    }

    return new_triangles;
}

std::list<Triangle*> Delaunay::SearchLegalEdge(std::list<Triangle*> triangles) {
    std::list<Triangle*> triangles_to_recheck;

    // Verifie si l'arete est legale parmis les nouveaux triangles
    for(auto t = triangles.begin(); t != triangles.end(); t++) {
        Triangle* new_triangle = *t;

        Edge* AB = new_triangle->AB;
        Edge* BC = new_triangle->BC;
        Edge* CA = new_triangle->CA;

        Quadrilateral* quadri;

        // Chercher l'ancienne arete dans la liste d'aretes
        Point* common_point;

        auto it_AB = std::find(list_edges->begin(), list_edges->end(), AB);
        auto it_BC = std::find(list_edges->begin(), list_edges->end(), BC);
        auto it_CA = std::find(list_edges->begin(), list_edges->end(), CA);

        // Constituer le quadrilatere a verifier
        if(it_AB != list_edges->end()) {
            common_point = GetPointFromTriangle(*it_AB);

            if(common_point) {
                quadri = new Quadrilateral(new_triangle->A, new_triangle->C, new_triangle->B, common_point);
            }

        }else if(it_BC != list_edges->end()) {
            common_point = GetPointFromTriangle(*it_BC);

            if(common_point) {
                quadri = new Quadrilateral(new_triangle->B, new_triangle->A, new_triangle->C, common_point);
            }

        }else if(it_CA != list_edges->end()) {
            common_point = GetPointFromTriangle(*it_CA);

            if(common_point) {
                quadri = new Quadrilateral(new_triangle->C, new_triangle->B, new_triangle->A, common_point);
            }
        }

        Triangle* tr = new Triangle(quadri->A, quadri->B, quadri->C, true);

        Point* cercle = Triangle::GetCentreCercle(tr);
        double radius = GetLength(cercle, quadri->A);

        double edge = GetLength(cercle, quadri->D);

        if(edge < radius) {
            std::cout << "Arete illegale" << std::endl;

            // Supprimer l'arrete illegale
            list_edges->erase(std::find(list_edges->begin(), list_edges->end(), quadri->InternEdge));

            // Ajouter l'arete legale
            quadri->InternEdge = new Edge(quadri->B, quadri->D);
            list_edges->push_back(quadri->InternEdge);

            // Ajouter les triangles a verifier suite a la modification
            triangles_to_recheck.push_back(new Triangle(quadri->A, quadri->B, quadri->C, false));
            triangles_to_recheck.push_back(new Triangle(quadri->A, quadri->C, quadri->D, false));

        } else {
            std::cout << "Arete legale" << std::endl;

            // Ajouter l'arete legale
            list_edges->push_back(quadri->InternEdge);
        }
    }

    return triangles_to_recheck;
}

Point* Delaunay::GetPointFromTriangle(Edge* common_edge) {
    // Retourne le triangle ayant l'arete en commun s'il y en a un
    for(auto t = list_triangles->begin(); t != list_triangles->end(); t++) {
        Triangle* new_triangle = *t;

        if(Triangle::EdgesAreEqual(new_triangle->AB, common_edge)) {
            return new_triangle->C;
        }
        if(Triangle::EdgesAreEqual(new_triangle->BC, common_edge)) {
            return new_triangle->A;
        }
        if(Triangle::EdgesAreEqual(new_triangle->CA, common_edge)) {
            return new_triangle->B;
        }
    }

    return 0;
}

double Delaunay::GetLength(Point* a, Point* b) {
    // Retrourne la distance entre a et b (rayon du cercle)

    return sqrt(pow(b->x - a->x, 2) + pow(b->y - a->y, 2));
}

double Delaunay::GetDeterminant(Point* A, Point* B) {
    return (A->x * B->y) - (B->x * A->y);
}

bool Delaunay::GetSegmentsIntersection(Edge* a, Edge* b) {
    // Definition de tout nos vecteurs
    Edge* AB = a;
    Edge* CD = b;
    Edge* AD = new Edge(AB->start, CD->finish);
    Edge* AC = new Edge(AB->start, CD->start);
    Edge* CB = new Edge(CD->start, AB->finish);
    Edge* CA = new Edge(CD->start, AB->start);

    // Produit scalaire pour le cas : AB & CD paralleles
    
    double check_1 = GetDeterminant(AB->direction, CD->direction);
    std::cout << check_1 << std::endl;
    
    // Produit scalaire pour le cas : Intersection sur CD
    double check_2 = GetDeterminant(AB->direction, AD->direction) * GetDeterminant(AB->direction, AC->direction); 

    // Produit scalaire pour le cas : Intersection sur AB
    double check_3 = GetDeterminant(CD->direction, CB->direction) * GetDeterminant(CD->direction, CA->direction);

    if(check_1 != 0 && check_2 <= 0 && check_3 <= 0) {
        std::cout << "Intersection entre les deux aretes" << std::endl;

        return true;
    
    }else {
        std::cout << "Pas d'intersection entre les deux aretes" << std::endl;

        return false;
    }
    
}

Triangle* Delaunay::SetFirstTriangle(Points* list_points) {
    double y_min = 0;
    double y_max = 0;
    double x_min = 0;
    double x_max = 0;

    for(auto point = list_points->begin(); point != list_points->end(); point++) {
        // Recuperer les valeurs maximales et minimales de 'x' et 'y'
        double x = (*point)->x;
        double y = (*point)->y;

        if(x < x_min) x_min = x;
        if(x > x_max) x_max = x;
        
        if(y < y_min) y_min = y;
        if(y > y_max) y_max = y;
    }

    Point* point_a = new Point(x_min, y_min);
    Point* point_b = new Point(x_min, 2 * y_max);
    Point* point_c = new Point(2 * x_max, y_min);

    Triangle* new_triangle = new Triangle(point_a, point_b, point_c, true);

    return new_triangle;
}
