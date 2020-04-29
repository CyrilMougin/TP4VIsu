#include <iostream>
#include <set>
#include <list>

#include "voronoi/voronoi.h"

int main() {
    std::cout << "Execution start" << std::endl;

    int width = 20;
    int height = 20;
    std::set<Point*> set_points;
    Voronoi* voronoi = new Voronoi();
    std::list<Edge*> list_edges;

    for (int i = 0; i < 2; i++) {
        Point* new_data = new Point(4 * i, 4 * i);

        set_points.insert(new_data);
    }

    for (auto point = set_points.begin(); point != set_points.end(); point++) {
        Point* new_data = *point;

        std::cout << "x : " << new_data->x  << " | y : " << new_data->y << std::endl;

    }
    
    std::cout << "Voronoi start" << std::endl;
    list_edges = voronoi->voronoi_diagram(set_points, width, height);
    std::cout << "Voronoi done" << std::endl;

    for(auto edge = list_edges.begin(); edge != list_edges.end(); edge++) {
		Edge* new_edge = *edge;

        if( new_edge->start == 0) {
			std::cout << "Début du bord manquant" << std::endl;
		}
		
        if(new_edge->finish == 0) {
			std::cout << "Extremite du bord manquant" << std::endl;
		}

        std::cout << "Debut : " << new_edge->start->x << "," << new_edge->start->y << std::endl;
        std::cout << "Fin : " << new_edge->finish->x << "," << new_edge->finish->y << std::endl;
	}

    std::cout << "Execution done" << std::endl;
}