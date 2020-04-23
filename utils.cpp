#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <map>
 
float get_bitch(int y, int sample);
float get_parable(int x, int p, int sample);
float get_length(float y_data, float y_bitch);

auto get_dict_value(int element);
void set_dict_element(int element, int value);
void del_dict_element(int element);

float set_datas_fortune(int sample);

std::map<int, int> dictionary;

typedef struct {
    GLfloat x, y, z;
} Data;

int main() {
	int sample = 10;	
}

float set_datas_fortune(int sample) {
	// Creer un 'vecteur' de datas pour les sources
	/**
	* Deja il faudrait remplir ce vecteur de donnees
	* Mais je sais pas si c'est utile que ce soit de type 'Data'
	* A moins que tu veuilles afficher les sources
	*/
	Data source_data[sample][1]; 
	
	// Plage qui descent d'une iteration chaque tour
	for(int y = 0; y < sample; y++) {
		float beach = get_beach(y, sample);
		
		for(int x = 0; x < sample; x++) {
			if(source_data[x][0].y < beach) {
				// Recuperer la distance entre la source et la plage
				float length = get_length(source_data[x][0].y, beach);
				
				// Definir la parabole
				float parable = get_parable(x, length, sample);

				// Ajouter la parabole au dictionnaire
				set_dict_element(x, y);
				
			}
		}
	}
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

auto get_dict_value(int element) {
	// Retourne un element du dictionnaire
	return dictionary.find(element);
}

void set_dict_element(int element, int value) {
	// Ajoute un element dans le dictionnaire
	dictionary.insert(std::make_pair(element, value));
}

void del_dict_element(int element) {
	// Suppime un element dans le dictionnaire
	dictionary.erase(element);
}