// Inspire de : 
// Fortune’s algorithm and implementation : http://blog.ivank.net/fortunes-algorithm-and-implementation.html

#include <iostream>
#include <vector>

#include "edge.cpp"

class BeachLine {
public:
    Point* site;                // Site associe a la parabole

    bool is_a_leaf;             // Definis si c'est une feuille (true) ou pas (false)

    Event* circle_event;   //
    Edge* edge;                 // Bord associe a la parabole

    BeachLine* parent;          // Parent (vis a vis de l'arbre de recherche binaire)
    BeachLine* left;            // Sous-arbre gauche (vis a vis de l'arbre de recherche binaire)
    BeachLine* right;           // Sous-arbre droit (vis a vis de l'arbre de recherche binaire)

    BeachLine() {
        site = 0;
        is_a_leaf = false;
        circle_event = 0;
        edge = 0;
        parent = 0;
        left = 0;
        right = 0;
    }

    BeachLine(Point* site_data) {
        site = site_data;
        is_a_leaf = true;
        circle_event = 0;
        edge = 0;
        parent = 0;
        left = 0;
        right = 0;
    }

	void SetLeft(BeachLine* tree) {
        // Met a jour le fils et parent de deux noeuds
        this->left = tree;
        tree->parent = this; 
    }

	void SetRight(BeachLine* tree) {
        // Met a jour le fils et parent de deux noeuds
        this->right = tree;
        tree->parent = this;
    }

    BeachLine* get_left_parent(BeachLine* line) {
        // Retourne le plus proche parent de gauche
        BeachLine* parentNode = line->parent;
        BeachLine* currentNode = line;

        // Parcourir jusqu'a ce que le sous-arbre gauche du parent ne soit plus le noeud courant
        while (parentNode->left == currentNode) {
            // Mise a jour des variables
            currentNode = parentNode;
            parentNode = parentNode->parent;
        }

        return parentNode;      
    }

    BeachLine* get_right_parent(BeachLine* line) {
        // Retourne le plus proche parent de droite
        BeachLine* parentNode = line->parent;
        BeachLine* currentNode = line;

        // Parcourir jusqu'a ce que le sous-arbre droit du parent ne soit plus le noeud courant
        while (parentNode->right == currentNode) {
            // Mise a jour des variables
            currentNode = parentNode;
            parentNode = parentNode->parent;
        }

        return parentNode;      
    }

    BeachLine* get_left_child(BeachLine* line) {
        if(!line) {
            return 0;

        }else {
            // Retourne le plus proche enfant (a gauche du noeud courant)     
            BeachLine* currentNode = line->left;

            // Parcourir jusqu'a tomber sur une feuille
            while (currentNode->left != NULL && currentNode->right != NULL) {
                currentNode = currentNode->right;
            }

            return currentNode;
        }
    }

    BeachLine* get_right_child(BeachLine* line) {
        if(!line) {
            return 0;
    
        }else {  
            // Retroune le plus proche enfant (a droite du noeud courant) 
            BeachLine* currentNode = line->right;

            // Parcourir jusqu'a tomber sur une feuille
            while (currentNode->left != NULL && currentNode->right != NULL) {
                currentNode = currentNode->left;
            }

            return currentNode;
        }
    }

    BeachLine* get_left(BeachLine* line) {
        // Retroune la plus proche feuille de gauche
        return get_left_child(get_left_parent(line));
    }

    BeachLine* get_right(BeachLine* line) {
        // Retroune la plus proche feuille de droite
        return get_right_child(get_right_parent(line));
    }

};
