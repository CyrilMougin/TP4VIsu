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

double get_y_data(std::vector<Data> source_data, double x_data);

typedef struct {
    GLfloat x, y, z;
} Data;

float set_datas_fortune(int sample) {
	// Creer une vecteur de datas pour les sources & Ajouter des elements au vecteur
	std::vector<Data> source_data = init_vector(source_data, sample);

	// Creer un arbre binaire de recherche vide
	BinarySearchTree* source_tree = new BinarySearchTree();

	// Creer un vecteur avec toutes les feuilles de l'arbre
	std::vector<BinarySearchTree*> leaf_data = beach_line(source_tree);

	// Creer un vecteur avec tous les ecarts entre les feuilles et la plage
	std::vector<float> length_data;

	// Creer un vecteur avec l'ensemble des points constituant la ligne de plage
	std::vector<Data> beachline_data;
	
	// Plage qui descent d'une iteration chaque tour
	for(int y = 0; y < sample; y++) {
		float beach = get_beach(y, sample);
		
		for(int iter = 0; iter < source_data.size(); iter++) {
			if(source_data[iter].y < beach) {
				// Ajouter la source à l'arbre binaire de recherche
				source_tree->insert(source_data[iter].x);

				// Mise a jour de la ligne de plage
				leaf_data = beach_line(source_tree);
			}
		}

		// Remplir le vecteur avec toutes les distances (source - plage) des feuilles
		for(int iter = 0; iter < leaf_data.size(); iter++) {
			Data leaf_point;
			
			leaf_point.x = leaf_data[iter]->value;
			leaf_point.y = get_y_data(source_data, leaf_point.x);
			leaf_point.z = 0;

			// Recuperer la distance entre la source et la plage
			length_data.push_back(get_length(leaf_point.y, beach));
		}

		for(int x = 0; x < sample; x++) {
			Data beachline_point;

			beachline_point.x = (x - 0.5 * (double)sample) / (0.1 * (double)sample);
			beachline_point.y = 0;
			beachline_point.z = 0;

			for(int iter = 0; iter<leaf_data.size(); iter++) {
				// Definir la parabole
				float parable = get_parable(x, length_data[iter], sample);

				// Recuperer la parabole la plus 'basse' en un point x
				if(parable > beachline_point.y) {
					beachline_point.y = parable;
				}
			}

			// Ajouter le point au vecteur
			beachline_data.push_back(beachline_point);
		}
	}
}



double get_y_data(std::vector<Data> source_data, double x_data) {
	// Retoune la donnee 'y' affiliee a une donnee 'x'
	for(auto iter = source_data.begin(); iter != source_data.end(); iter++) {
		if(iter->x == x_data) {
			return iter->y;
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