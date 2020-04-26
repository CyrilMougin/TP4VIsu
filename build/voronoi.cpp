#include "../glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <math.h>

typedef struct {
    GLfloat x, y, z;
} Data;

float length(Data beachline_point, Data source_point);

std::list<Data> summit(std::list<Data> summit_data, std::vector<Data> beachline_data, std::vector<Data> source_data) {
    std::list<Data> current_data = summit_data;

    for(int i = 0; i < beachline_data.size(); i++) {
        std::vector<float> length_data;

        // Ajouter toutes les distances en mémoire
        for(int j = 0; j < source_data.size(); i++) {
            length_data.push_back(length(beachline_data[i], source_data[j]));
        }

        // Recuperer la valeur minimale
        float min_element = *std::min_element(length_data.begin(), length_data.end());

        // Compter le nombre d'occurence de la valeur minimale
        int nb_min_element = std::count(length_data.begin(), length_data.end(), min_element);

        if(nb_min_element >= 3) {
            current_data.push_back(beachline_data[i]);
        } 
    }

    return current_data;
}

float length(Data beachline_point, Data source_point) {
	// Retourne la distance entre deux points
	return sqrt(pow(source_point.x - beachline_point.x, 2) + pow(source_point.y - beachline_point.y, 2));
}