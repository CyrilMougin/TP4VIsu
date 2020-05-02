#include "../glad/glad.h"
#include <GLFW/glfw3.h>

class Point {
public :
    // VARIABLES
    GLdouble x; 
    GLdouble y;

    // CONSTRUCTEUR
    Point(float data_x, float data_y) {
        x = data_x;
        y = data_y;
    }

    static bool PointAreEqual(Point* a, Point* b) {
        if(a->x == b->x && a->y == b->y) {
            return true;
        
        }else {
            return false;
        }
    }
};