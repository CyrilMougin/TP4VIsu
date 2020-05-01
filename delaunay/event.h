#include <iostream>

class Event {
public:
	// VARIABLES
	Point* point;           // Point affilie a l'evenement
	bool is_a_site_event;   // Booleen signifiant si l'element est un site (true) ou pas (false)
	double y;               // Coordonnee affiliee au point
	Triangle* triangle;		// Triangle affilie au point

	// CONSTRUCTEUR
	Event(Point* a_data, bool iase) {
		point = a_data;
		is_a_site_event = iase;
		y = a_data->y;
		triangle = 0;
	}

	// STRUCTURE
	struct CompareEvent : public std::binary_function<Event*, Event*, bool> {
		bool operator()(const Event* l, const Event* r) const { 
			return (l->y < r->y);
		}
	};
};