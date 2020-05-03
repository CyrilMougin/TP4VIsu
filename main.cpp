#include <iostream>

#include "delaunay/delaunay.h"

del::Delaunay* delaunay;
del::Points * list_points;
del::Edges * list_edges;

double width = 5;
double height = 5;

int main() {
    std::cout << "Execution start" << std::endl;

    using namespace del;

    delaunay = new Delaunay();
    list_points = new Points();

    // Mis en place des points et des directions 
    for (int i = 0; i < 10; i++) {
        list_points->push_back(new Point( width * (double)rand()/(double)RAND_MAX , height * (double)rand()/(double)RAND_MAX )); 
    }

    for (auto point = list_points->begin(); point != list_points->end(); point++) {
        Point* new_data = *point;

        std::cout << "x : " << new_data->x  << " | y : " << new_data->y << std::endl;

    }
    
    std::cout << "Delaunay start" << std::endl;
    list_edges = delaunay->DelaunayTriangulation(list_points);
    std::cout << "Delaunay done" << std::endl;

    std::cout << "list_edges size : " << list_edges->size() << std::endl;
    
    for(auto edge = list_edges->begin(); edge != list_edges->end(); edge++) {
		Edge* new_edge = *edge;

        std::cout << "Debut : " << new_edge->start->x << "," << new_edge->start->y << " | Fin : " << new_edge->finish->x << "," << new_edge->finish->y << std::endl;
	}

    std::cout << "Execution done" << std::endl;
}