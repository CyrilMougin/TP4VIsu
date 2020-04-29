// Inspire de : 
// Fortune’s algorithm and implementation : http://blog.ivank.net/fortunes-algorithm-and-implementation.html

#include <iostream>

class Event {
public:
	// VARIABLES
	Point* point;           // Point affilie a l'evenement
	bool is_a_site_event;   // Booleen signifiant si l'element est un site (true) ou pas (false)
	double y;                // Coordonnee affiliee au point
	BeachLine* parable;		// Parabole associee a l'evenement

	// CONSTRUCTEUR
	Event(Point* a_data, bool iase)
	{
		point = a_data;
		is_a_site_event = iase;
		y = a_data->y;
		parable = 0;
	}

	struct CompareEvent : public std::binary_function<Event*, Event*, bool>
	{
		bool operator()(const Event* l, const Event* r) const { return (l->y < r->y); }
	};
};