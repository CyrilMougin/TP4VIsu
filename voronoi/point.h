#include "../glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>

class Point {
public :
    // VARIABLE
    double x; 
    double y;

    // CONSTRUCTEUR
    Point(float data_x, float data_y) {
        x = data_x;
        y = data_y;
    }
};
