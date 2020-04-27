// Inspire de : 
// Binary Search Tree Implementation in C++ : https://medium.com/@13dipty/binary-search-tree-implementation-in-c-537b9a9cedf8

#include <iostream>

class BinarySearchTree {
public:
    int value;                  // Cle de l'arbre
    BinarySearchTree* left;     // Sous-arbre gauche
    BinarySearchTree* right;    // Sous-arbre droit
    BinarySearchTree* parent;   // Noeud parent
    
    // Initialsation d'un nouvelle arbre
    BinarySearchTree() {
        value = 42;
        left = NULL;
        right = NULL;
        parent = NULL;
    }

    BinarySearchTree(int val) {
        value = val;
        left = NULL;
        right = NULL;
        parent = NULL;
    }

    // Rechercher une valeur dans l'arbre
    bool search(int val) {
        BinarySearchTree* currentNode = this;

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
                return true;
            }
        }
        
        return false;
    }

    // Met a jour le fils et parent de deux noeuds
	void SetLeft(BinarySearchTree* tree) {
        this->left = tree;
        tree->parent = this; 
    }

    // Met a jour le fils et parent de deux noeuds
	void SetRight(BinarySearchTree* tree) {
        this->right = tree;
        tree->parent = this;
    }

    // Inserer un nouvelle valeur dans l'arbre
    BinarySearchTree& insert(int val) {
        BinarySearchTree* currentNode = this;
        
        while(true) {
            // Checker si la valeur est inférieure a celle du noeud courant 
            if(val < currentNode->value) {
                // Parcourir le sous-arbre de gauche
                if(currentNode->left == NULL) {
                    // Si on arrive a une feuille on creer un nouveau noeud et on insere la valeur
                    BinarySearchTree* newNode = new BinarySearchTree(val);
                    //currentNode->left = newNode;
                    currentNode->SetLeft(newNode);

                    break;
                }else {
                    // Mettre a jour le noeud courant
                    currentNode = currentNode->left;
                }

            // Checker si la valeur est superieure a celle du noeud courant
            }else if(val > currentNode->value) {
                // Parcourir le sous-arbre de droite
                if(currentNode->right == NULL) {
                    // Si on arrive a une feuille on creer un nouveau noeud et on insere la valeur
                    BinarySearchTree* newNode = new BinarySearchTree(val);
                    //currentNode->right = newNode;
                    currentNode->SetRight(newNode);

                    break;
                }else {
                    // Mettre a jour le noeud courant
                    currentNode = currentNode->right;
                }
            
            }else {
                break;
            }
        }

        return *this;
    }
    
    // Supprimer une valeur de l'arbre
    BinarySearchTree& remove(int val, BinarySearchTree* parentNode = NULL){
        BinarySearchTree* currentNode = this;

        // Parcourir jusqu'a une feuille
        while(currentNode != NULL) {
            // Checker si la valeur est inférieure a celle du noeud courant
            if(val < currentNode->value) {
                // Mettre a jour le noeud courant (cote sous-arbre gauche)
                parentNode = currentNode;
                currentNode = currentNode->left;

            // Checker si la valeur est superieure a celle du noeud courant
            }else if(val > currentNode->value) {
                // Mettre a jour le noeud courant (cote sous-arbre droit)
                parentNode = currentNode;
                currentNode = currentNode->right;

            // Valeur trouvee           
            }else {
                // Cas ou l'on a deux enfants
                if(currentNode->left != NULL && currentNode->right != NULL) {
                    // Recuperer la plus petite valeur du sous-arbre de droite
                    currentNode->value = currentNode->right->getMinValue();
                    currentNode->right->remove(currentNode->value, currentNode);

                // Cas ou le noeud est la racine
                }else if(parentNode == NULL) {
                    // Checker s'il y a des enfants dans le sous-arbre gauche
                    if(currentNode->left != NULL){
                        // Mettre a jour le noeud courant
                        currentNode->value = currentNode->left->value;
                        currentNode->right=currentNode->left->right;
                        currentNode->left = currentNode->left->left;

                    // Sinon dans le sous-arbre droit
                    }else if(currentNode->right != NULL) {
                        // Mettre a jour le noeud courant
                        currentNode->value = currentNode->right->value;
                        currentNode->left = currentNode->right->left;
                        currentNode->right=currentNode->right->right;

                    // Sinon pas d'enfants
                    }else {
                        // Mettre a jour le noeud courant
                        currentNode->value = 0;
                    }

                // Cas ou l'on a un enfant (parent d'une branche gauche)
                }else if(parentNode->left == currentNode){
                    // L'enfant est a gauche
                    if(currentNode->left != NULL){
                        parentNode->left = currentNode->left;

                    // L'enfant est a droite
                    }else if(currentNode->right != NULL){
                        parentNode->right = currentNode->right;
                    }
                
                // Cas ou l'on a un enfant (parent d'une branche droite)
                }else if(parentNode->right == currentNode){
                    // L'enfant est a gauche
                    if(currentNode->left != NULL){
                        parentNode->right = currentNode->left;
                    
                    // L'enfant est a droite
                    }else {
                        parentNode->right = currentNode->right;
                    }
                }
                break;
            }
        }    
        return *this;
    }

    // Retourne la valeur minimale de l'arbre
    int getMinValue() {
        BinarySearchTree* currentNode = this;

        while(currentNode->left != NULL) {
            currentNode = currentNode->left;
        }

        return currentNode->value;
    }

    // Retourne la valeur maximale de l'arbre
    int getMaxValue() {
        BinarySearchTree* currentNode = this;

        while(currentNode->right != NULL) {
            currentNode = currentNode->right;
        }

        return currentNode->value;
    }
};
