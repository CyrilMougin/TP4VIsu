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
    std::cout << "2.0" << std::endl;
    BeachLine* parentNode = line->parent;
    BeachLine* currentNode = line;
    std::cout << "2.1" << std::endl;
    // Cas de la racine
    std::cout << parentNode << std::endl;
    /*if (!parentNode) {
        std::cout << "2.3" << std::endl;
        return 0;
    }*/

    // Parcourir jusqu'a ce que le sous-arbre gauche du parent ne soit plus le noeud courant
    while (parentNode->Left() == currentNode) {
        std::cout << "2.2" << std::endl;
        // Cas de la racine
        if (!parentNode->parent) {
            std::cout << "2.3" << std::endl;
            return 0;
        }
        std::cout << "2.4" << std::endl;
        // Mise a jour des variables
        currentNode = parentNode;
        parentNode = parentNode->parent;
    }
    std::cout << "2.5" << std::endl;
    return parentNode;      
}

BeachLine* BeachLine::get_right_parent(BeachLine* line) {
    BeachLine* parentNode = line->parent;
    BeachLine* currentNode = line;

    // Cas de la racine
    /*if (!parentNode) {
        std::cout << "2.3" << std::endl;
        return 0;
    }*/

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
    std::cout << "3.0" << std::endl;
    if(!line) {
        std::cout << "3.1" << std::endl;
        return 0;

    }else {
        std::cout << "3.2" << std::endl;
        // Retourne le plus proche enfant (a gauche du noeud courant)     
        BeachLine* currentNode = line->Left();
        std::cout << "3.3" << std::endl;
        // Parcourir jusqu'a tomber sur une feuille
        while (!currentNode->is_a_leaf) {
            currentNode = currentNode->Right();
        }
        std::cout << "3.4" << std::endl;
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
    std::cout << "1" << std::endl;
    return get_left_child(get_left_parent(line));
}

BeachLine* BeachLine::get_right(BeachLine* line) {
    return get_right_child(get_right_parent(line));
}
