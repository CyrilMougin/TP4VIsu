// Inspire de : Fortune’s algorithm and implementation
// http://blog.ivank.net/fortunes-algorithm-and-implementation.html#impl_cpp

#include <iostream>
#include <vector>

#include "binary_search_tree.cpp"

BinarySearchTree* left_parent(BinarySearchTree* tree) {
    //std::cout << "3.3.1" << std::endl;
    // Retourne le plus proche parent de gauche
    BinarySearchTree* parentNode = tree->parent;
    BinarySearchTree* currentNode = tree;
    //std::cout << "3.3.2" << std::endl;
    //std::cout << "parent : " << parentNode << " | parent gauche : " << parentNode->left << " | courant : " << currentNode << std::endl;
    // Parcourir jusqu'a ce que le sous-arbre gauche du parent ne soit plus le noeud courant
    while (parentNode->left == currentNode && parentNode->parent->value != 42) {
        //std::cout << "3.3.3" << std::endl;
        // Mise a jour des variables
        currentNode = parentNode;
        parentNode = parentNode->parent;
    }

    return parentNode;      
}

BinarySearchTree* right_parent(BinarySearchTree* tree) {
    // Retourne le plus proche parent de droite
    BinarySearchTree* parentNode = tree->parent;
    BinarySearchTree* currentNode = tree;

    // Parcourir jusqu'a ce que le sous-arbre droit du parent ne soit plus le noeud courant
    while (parentNode->right == currentNode && parentNode->parent->value != 42) {
        // Mise a jour des variables
        currentNode = parentNode;
        parentNode = parentNode->parent;
    }

    return parentNode;      
}

BinarySearchTree* left_child(BinarySearchTree* tree) { 
    //std::cout << "3.3.4" << std::endl;
    if(tree->left != NULL) {
        // Retourne le plus proche enfant (a gauche du noeud courant)     
        BinarySearchTree* currentNode = tree->left;

        // Parcourir jusqu'a tomber sur une feuille
        while (currentNode->left != NULL && currentNode->right != NULL) {
            currentNode = currentNode->right;
        }

        return currentNode;
    
    }else {
        return tree;
    }
}

BinarySearchTree* right_child(BinarySearchTree* tree) {
    if(tree->right != NULL) {    
        // Retroune le plus proche enfant (a droite du noeud courant) 
        BinarySearchTree* currentNode = tree->right;

        // Parcourir jusqu'a tomber sur une feuille
        while (currentNode->left != NULL && currentNode->right != NULL) {
            currentNode = currentNode->left;
        }
 
        return currentNode;

    }else {
        return tree;
    }
}

BinarySearchTree* left(BinarySearchTree* tree) {
    // Retroune la plus proche feuille de gauche
    return left_child(left_parent(tree));
}

BinarySearchTree* right(BinarySearchTree* tree) {
    // Retroune la plus proche feuille de droite
    return right_child(right_parent(tree));
}

std::vector<BinarySearchTree*> beach_line(BinarySearchTree* tree) {
    //std::cout << "3.1" << std::endl;
	std::vector<BinarySearchTree*> leaf_data;
	leaf_data.push_back(tree);

    if(tree->parent != NULL) {
        if(tree->parent->value != 42) {
            //std::cout << "3.2" << std::endl;
            BinarySearchTree* current_node = tree;
            BinarySearchTree* neighbor_left = left(current_node);
            
            // Parcourir jusqu'a ce qu'il n'y ait plus de voisin a gauche (a partir du noeud courant)
            while(current_node != neighbor_left && neighbor_left->left == NULL && neighbor_left->right == NULL) {
                //std::cout << "3.2.1" << std::endl;
                // Ajouter l'element au vecteur
                leaf_data.push_back(neighbor_left);

                // Mise a jour des valeurs
                current_node = neighbor_left;
                neighbor_left = left(current_node);
            } 

            current_node = tree;
            BinarySearchTree* neighbor_right = right(current_node);

            // Parcourir jusqu'a ce qu'il n'y ait plus de voisin a droite (a partir du noeud courant)
            while(current_node != neighbor_right && neighbor_right->right == NULL && neighbor_right->left == NULL) {
                //std::cout << "3.2.2" << std::endl;
                // Ajouter l'element au vecteur
                leaf_data.push_back(neighbor_right);

                // Mise a jour des valeurs
                current_node = neighbor_right;
                neighbor_right = right(current_node);
            }
        }
    }

	return leaf_data;
}

// Rechercher une valeur dans l'arbre
BinarySearchTree* search(BinarySearchTree* tree, int val) {
    BinarySearchTree* currentNode = tree;

    // Parcourir jusqu'a une feuille
    while(currentNode != NULL) {
        // Checker si la valeur est inférieure a celle du noeud courant
        if(val < currentNode->value) {
            // Mettre a jour le noeud courant (cote sous-arbre gauche)
            currentNode = currentNode->left;

        // Checker si la valeur est superieure a celle du noeud courant
        }else if(val > currentNode->value) {
            // Mettre a jour le noeud courant (cote sous-arbre droit)
            currentNode = currentNode->right;
        
        // Valeur trouvee
        }else {
            return currentNode;
        }
    }
    
    return NULL;
}
