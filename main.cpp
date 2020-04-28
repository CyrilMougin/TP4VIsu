
#include <iostream>

#include "build/voronoi.cpp"

int main() {
    std::cout << "Execution start" << std::endl;

    int width = 1000;
    int height = 1000;
    std::set<Point*>* set_points;

    for (int i = 0; i < 5; i++) {
        Point* new_data = new Point(4 * i, 4 * i);

        set_points->insert(new_data);
    }
    
    for (auto point = set_points->begin(); point != set_points->end(); point++) {
        Point* new_data = *point;

        std::cout << "x : " << new_data->point.x  << " | y : " << new_data->point.y << std::endl;

    }

    voronoi_diagram(set_points, width, height);

    std::cout << "Execution done" << std::endl;
}