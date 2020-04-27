#include "../glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>

typedef struct {
    GLfloat x, y;
} Data;

class Point {
public :

    Data point;

    Point(float data_x, float data_y) {
        point.x = data_x;
        point.y = data_y;
    }
};
