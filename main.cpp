#include <iostream>
#include <set>
#include <list>

#include "voronoi/voronoi.h"

vor::Voronoi * v;
vor::Vertices * ver;
vor::Vertices * dir;
vor::Edges * edg;

double width = 5;
double height = 5;

int main() {
    std::cout << "Execution start" << std::endl;

    using namespace vor;

    v = new Voronoi();
	ver = new Vertices();
	dir = new Vertices();

    for (int i = 0; i < 3; i++) {
        //Point* new_data = new Point(4 * i, 4 * i);

        //ver->push_back(new_data);

        ver->push_back(new Point( width * (double)rand()/(double)RAND_MAX , height * (double)rand()/(double)RAND_MAX )); 
		dir->push_back(new Point( (double)rand()/(double)RAND_MAX - 0.5, (double)rand()/(double)RAND_MAX - 0.5));
    }

    for (auto point = ver->begin(); point != ver->end(); point++) {
        Point* new_data = *point;

        std::cout << "x : " << new_data->x  << " | y : " << new_data->y << std::endl;

    }
    
    std::cout << "Voronoi start" << std::endl;
    edg = v->GetEdges(ver, width, height);
    std::cout << "Voronoi done" << std::endl;

    for(auto edge = edg->begin(); edge != edg->end(); edge++) {
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