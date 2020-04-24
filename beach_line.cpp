// Inspire de : Fortune’s algorithm and implementation
// http://blog.ivank.net/fortunes-algorithm-and-implementation.html#impl_cpp

#include <iostream>

#include "binary_search_tree.cpp"

class BeachLine {
public:
    int value;
    BinarySearchTree* tree;

    BeachLine() {
        value = 0;
        tree  = new BinarySearchTree();
    }

    BeachLine(int val) {
        value = val;
        tree  = new BinarySearchTree(val, NULL);
    }

    BinarySearchTree* left(BinarySearchTree* tree) {
        // Retroune la plus proche feuille de gauche
        return left_child(left_parent(tree));
    }

    BinarySearchTree* right(BinarySearchTree* tree) {
        // Retroune la plus proche feuille de droite
        return right_child(right_parent(tree));
    }

    BinarySearchTree* left_parent(BinarySearchTree* tree) {
        // Retourne le plus proche parent de gauche
        BinarySearchTree* parentNode = tree->parent;
        BinarySearchTree* currentNode = tree;

        // Parcourir jusqu'a ce que le sous-arbre gauche du parent ne soit plus le noeud courant
        while (parentNode->left == currentNode) {
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
        while (parentNode->right == currentNode) {
            // Mise a jour des variables
            currentNode = parentNode;
            parentNode = parentNode->parent;
        }

        return parentNode;      
    }

    BinarySearchTree* left_child(BinarySearchTree* tree) { 
        // Retourne le plus proche enfant (a gauche du noeud courant)     
        BinarySearchTree* currentNode = tree->left;

        // Parcourir jusqu'a tomber sur une feuille
        while (currentNode->left != NULL && currentNode->right != NULL) {
            currentNode = currentNode->right;
        }

        return currentNode;
    }

    BinarySearchTree* right_child(BinarySearchTree* tree) {     
        // Retroune le plus proche enfant (a droite du noeud courant) 
        BinarySearchTree* currentNode = tree->right;

        // Parcourir jusqu'a tomber sur une feuille
        while (currentNode->left != NULL && currentNode->right != NULL) {
            currentNode = currentNode->left;
        }

        return currentNode;
    }
};