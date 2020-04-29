#include <iostream>
#include <vector>

#include "beach_line.h"

BeachLine::BeachLine() {
    site = 0;
    is_a_leaf = false;
    circle_event = 0;
    edge = 0;
    parent = 0;
    left = 0;
    right = 0;
}

BeachLine::BeachLine(Point* site_data) {
    site = site_data;
    is_a_leaf = true;
    circle_event = 0;
    edge = 0;
    parent = 0;
    left = 0;
    right = 0;
}

void BeachLine::SetLeft(BeachLine* tree) {
    this->left = tree;
    tree->parent = this; 
}

void BeachLine::SetRight(BeachLine* tree) {
    this->right = tree;
    tree->parent = this;
}

BeachLine* BeachLine::get_left_parent(BeachLine* line) {
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

BeachLine* BeachLine::get_right_parent(BeachLine* line) {
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

BeachLine* BeachLine::get_left_child(BeachLine* line) {
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

BeachLine* BeachLine::get_right_child(BeachLine* line) {
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

BeachLine* BeachLine::get_left(BeachLine* line) {
    return get_left_child(get_left_parent(line));
}

BeachLine* BeachLine::get_right(BeachLine* line) {
    return get_right_child(get_right_parent(line));
}
