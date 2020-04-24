#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "binary_search_tree.cpp"
#include "beach_line.cpp"
 
float get_beach(int y, int sample);
float get_parable(int x, int p, int sample);
float get_length(float y_data, float y_bitch);

std::vector<Data> init_vector(std::vector<Data> data, int sample);

float set_datas_fortune(int sample);

typedef struct {
    GLfloat x, y, z;
} Data;

float set_datas_fortune(int sample) {
	// Creer une vecteur de datas pour les sources & Ajouter des elements au vecteur
	std::vector<Data> source_data = init_vector(source_data, sample);

	// Creer un arbre binaire de recherche vide
	BinarySearchTree* source_tree = new BinarySearchTree();
	
	// Plage qui descent d'une iteration chaque tour
	for(int y = 0; y < sample; y++) {
		float beach = get_beach(y, sample);
		
		for(int iter = 0; iter < source_data.size(); iter++) {
			if(source_data[iter].y < beach) {
				// Ajouter la source à l'arbre binaire de recherche
				source_tree->insert(iter);	
			}
		}

		for(int x = 0; x < sample; x++) {
			// Recuperer la distance entre la source et la plage
			float length = get_length(source_data[x].y, beach);
			
			// Definir la parabole
			float parable = get_parable(x, length, sample);
		}
	}
}

std::vector<Data> init_vector(std::vector<Data> data, int sample) {
	// Ajout de sources dans la liste
	Data new_data;

	for(int i = 0; i < 4; i++) {
		new_data.x = (i - 0.5 * (double)sample) / (0.1 * (double)sample);
		new_data.y = (i - 0.5 * (double)sample) / (0.1 * (double)sample);
		new_data.z = 0;

		data.push_back(new_data);
	}
	
	return data;
}

float get_length(float y_data, float y_bitch) {
	// Retourne la distance entre la source et la plage
	return y_bitch - y_data;
}

float get_parable(int x, int p, int sample) {
	// Retourne la conversion dans l'espace {-5, 5} de l'equation de la parabole
	double x_data = (x - 0.5 * (double)sample) / (0.1 * (double)sample);
	
	return x / (2 * p);
}

float get_beach(int y, int sample) {
	// Retroune la conversion dans l'espace {-5, 5} de la plage
	return (y - 0.5 * (double)sample) / (0.1 * (double)sample);
}