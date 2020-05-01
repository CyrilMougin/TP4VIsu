#include <iostream>
#include <set>
#include <list>

#include "voronoi/voronoi.h"

vor::Voronoi * voronoi;
vor::Points * list_points;
vor::Points * list_directions;
vor::Edges * list_edges;

double width = 5;
double height = 5;

int main() {
    std::cout << "Execution start" << std::endl;

    using namespace vor;

    voronoi = new Voronoi();
	list_points = new Points();
	list_directions = new Points();

    // Mis en place des points et des directions 
    for (int i = 0; i < 3; i++) {
        list_points->push_back(new Point( width * (double)rand()/(double)RAND_MAX , height * (double)rand()/(double)RAND_MAX )); 
		list_directions->push_back(new Point( (double)rand()/(double)RAND_MAX - 0.5, (double)rand()/(double)RAND_MAX - 0.5));
    }

    for (auto point = list_points->begin(); point != list_points->end(); point++) {
        Point* new_data = *point;

        std::cout << "x : " << new_data->x  << " | y : " << new_data->y << std::endl;

    }
    
    std::cout << "Voronoi start" << std::endl;
    list_edges = voronoi->VoronoiDiagram(list_points, width, height);
    std::cout << "Voronoi done" << std::endl;

    for(auto edge = list_edges->begin(); edge != list_edges->end(); edge++) {
		Edge* new_edge = *edge;

        if( new_edge->start == 0) {
			std::cout << "Début du bord manquant" << std::endl;

            continue;
		}
		
        if(new_edge->finish == 0) {
			std::cout << "Extremite du bord manquant" << std::endl;

            continue;
		}

        std::cout << "Debut : " << new_edge->start->x << "," << new_edge->start->y << " | Fin : " << new_edge->finish->x << "," << new_edge->finish->y << std::endl;
	}

    std::cout << "Execution done" << std::endl;
}