#include "../glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "beach_line.cpp"
 
typedef struct {
    GLfloat x, y, z;
} Data;

float get_beach(int y, int sample);
float get_parable(int x, int p, int sample);
float get_length(float y_data, float y_bitch);

std::vector<Data> init_vector(std::vector<Data> data, int sample);

double get_y_data(std::vector<Data> source_data, double x_data);

void set_datas_fortune(int sample) {
	// Creer une vecteur de datas pour les sources & Ajouter des elements au vecteur
	std::vector<Data> source_data = init_vector(source_data, sample);
	std::cout << "source_data size : " << source_data.size() << std::endl;

	// Creer un arbre binaire de recherche vide
	BinarySearchTree* source_tree = new BinarySearchTree();
	//BinarySearchTree* source_tree;

	//std::cout << "valeur : " << source_data[iter].x << std::endl;
	//std::cout << "valeur : " << source_tree->value << std::endl;
	//std::cout << "noeud : " << source_tree << std::endl;
	//std::cout << "parent : " << source_tree->parent << std::endl;
	//std::cout << "left : " << source_tree->left << std::endl;
	//std::cout << "right : " << source_tree->right << std::endl;

	// Creer un vecteur avec toutes les feuilles de l'arbre
	std::vector<BinarySearchTree*> leaf_data = beach_line(source_tree);
	//std::vector<BinarySearchTree*> leaf_data;

	// Creer un vecteur avec tous les ecarts entre les feuilles et la plage
	std::vector<float> length_data;

	// Creer un vecteur avec l'ensemble des points constituant la ligne de plage
	std::vector<Data> beachline_data;
	
	// Plage qui descent d'une iteration chaque tour
	for(int y = 0; y < sample + 1; y++) {
		std::cout << "########## Descente de la plage ##########" << std::endl;
		float beach = get_beach(y, sample);
		std::cout << "beach value : " << beach << std::endl;
		
		for(int iter = 0; iter < source_data.size(); iter++) {
			if(source_data[iter].y <= beach) {
				/*
				FAIRE EN SORTE QUE ON N'AJOUTE PAS DEUX FOIS UNE DONNE
				*/
				// Ajouter la source à l'arbre binaire de recherche
				source_tree->insert(source_data[iter].x);

				// Recuperer l'element place dans l'arbre
				BinarySearchTree* current_node = search(source_tree, source_data[iter].x);
				
				std::cout << "valeur : " << current_node->value << std::endl;
				std::cout << "noeud : " << current_node << std::endl;
				std::cout << "parent : " << current_node->parent << std::endl;
				std::cout << "left : " << current_node->left << std::endl;
				std::cout << "right : " << current_node->right << std::endl;

				// Mise a jour de la ligne de plage
				leaf_data = beach_line(current_node);
			}
		}
		
		std::cout << "leaf_data size : " << leaf_data.size() << std::endl;
		std::cout << "leaf_data data : " << leaf_data[0]->value << std::endl;

		// Remplir le vecteur avec toutes les distances (source - plage) des feuilles
		for(int iter = 0; iter < leaf_data.size(); iter++) {
			Data leaf_point;
			
			leaf_point.x = leaf_data[iter]->value;
			leaf_point.y = get_y_data(source_data, leaf_point.x);
			leaf_point.z = 0;

			std::cout << "leaf_point y : " << leaf_point.y << std::endl;

			// Recuperer la distance entre la source et la plage
			length_data.push_back(get_length(leaf_point.y, beach));
		}

		std::cout << "length_data size : " << length_data.size() << std::endl;
		std::cout << "length_data data : " << length_data[0] << std::endl;

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

		std::cout << "" << std::endl;
	}
}



double get_y_data(std::vector<Data> source_data, double x_data) {
	// Retoune la donnee 'y' affiliee a une donnee 'x'
	for(int iter = 0; iter < source_data.size(); iter++) {
		if(source_data[iter].x == x_data) {
			return source_data[iter].y;
		}
	}

	return -42;
}

std::vector<Data> init_vector(std::vector<Data> data, int sample) {
	// Ajout de sources dans la liste
	Data new_data;

	for(int i = 0; i < 4; i++) {
		new_data.x = (i - 0.5 * (double)sample) / (0.1 * (double)sample);
		new_data.y = -(i - 0.5 * (double)sample) / (0.1 * (double)sample);
		new_data.z = 0;

		std::cout << "x : " << new_data.x << std::endl;
		std::cout << "y : " << new_data.y << std::endl;

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