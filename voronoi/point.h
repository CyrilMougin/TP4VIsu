#include "../glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>

typedef struct {
    GLfloat x, y;
} Data;

class Point {
public :
    // VARIABLE
    //Data point;
    GLfloat x, y;

    // CONSTRUCTEUR
    Point(float data_x, float data_y) {
        x = data_x;
        y = data_y;
    }
};
