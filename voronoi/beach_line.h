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

    // CONSTRUCTEURS
    BeachLine();
    BeachLine(Point* site_data);

    void SetLeft(BeachLine* p) { _left = p; p->parent = this; }
	void SetRight(BeachLine* p) { _right = p; p->parent = this; }

	BeachLine* Left() { return _left; }
	BeachLine* Right() { return _right; }

    // METHODES
    static BeachLine* get_left_parent(BeachLine* line);    // Retourne le plus proche parent de gauche
    static BeachLine* get_right_parent(BeachLine* line);   // Retourne le plus proche parent de droite
    static BeachLine* get_left_child(BeachLine* line);
    static BeachLine* get_right_child(BeachLine* line);
    static BeachLine* get_left(BeachLine* line);           // Retroune la plus proche feuille de gauche
    static BeachLine* get_right(BeachLine* line);          // Retroune la plus proche feuille de droite

private:

	BeachLine* _left;
	BeachLine* _right;

};