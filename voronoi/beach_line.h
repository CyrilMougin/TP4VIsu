class Point;
class Edge;
class Event;

class BeachLine {
public:
    // VARIABLES
    Point* site;                // Site associe a la parabole

    bool is_a_leaf;             // Definis si c'est une feuille (true) ou pas (false)

    Event* circle_event;   //
    Edge* edge;                 // Bord associe a la parabole

    BeachLine* parent;          // Parent (vis a vis de l'arbre de recherche binaire)
    BeachLine* left;            // Sous-arbre gauche (vis a vis de l'arbre de recherche binaire)
    BeachLine* right;           // Sous-arbre droit (vis a vis de l'arbre de recherche binaire)

    // CONSTRUCTEURS
    BeachLine();
    BeachLine(Point* site_data);

    // METHODES
    void SetLeft(BeachLine* tree);                  // Met a jour le fils et parent de deux noeuds
    void SetRight(BeachLine* tree);                 // Met a jour le fils et parent de deux noeuds
    BeachLine* get_left_parent(BeachLine* line);    // Retourne le plus proche parent de gauche
    BeachLine* get_right_parent(BeachLine* line);   // Retourne le plus proche parent de droite
    BeachLine* get_left_child(BeachLine* line);
    BeachLine* get_right_child(BeachLine* line);
    BeachLine* get_left(BeachLine* line);           // Retroune la plus proche feuille de gauche
    BeachLine* get_right(BeachLine* line);          // Retroune la plus proche feuille de droite

};