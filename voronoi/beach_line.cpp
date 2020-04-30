#include <iostream>
#include <vector>

#include "beach_line.h"

BeachLine::BeachLine() {
    site = 0;
    is_a_leaf = false;
    circle_event = 0;
    edge = 0;
    parent = 0;
}

BeachLine::BeachLine(Point* site_data) {
    site = site_data;
    is_a_leaf = true;
    circle_event = 0;
    edge = 0;
    parent = 0;
}

BeachLine* BeachLine::get_left_parent(BeachLine* line) {
    BeachLine* parentNode = line->parent;
    BeachLine* currentNode = line;

    // Parcourir jusqu'a ce que le sous-arbre gauche du parent ne soit plus le noeud courant
    while (parentNode->Left() == currentNode) {
        // Cas de la racine
        if (!parentNode->parent) {
            return 0;
        }

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
    while (parentNode->Right() == currentNode) {
        // Cas de la racine
        if (!parentNode->parent) {
            return 0;
        }

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
        BeachLine* currentNode = line->Left();

        // Parcourir jusqu'a tomber sur une feuille
        while (!currentNode->is_a_leaf) {
            currentNode = currentNode->Right();
        }

        return currentNode;
    }
}

BeachLine* BeachLine::get_right_child(BeachLine* line) {
    if(!line) {
        return 0;

    }else {  
        // Retroune le plus proche enfant (a droite du noeud courant) 
        BeachLine* currentNode = line->Right();

        // Parcourir jusqu'a tomber sur une feuille
        while (!currentNode->is_a_leaf) {
            currentNode = currentNode->Left();
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
