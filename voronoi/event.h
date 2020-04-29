// Inspire de : 
// Fortune’s algorithm and implementation : http://blog.ivank.net/fortunes-algorithm-and-implementation.html

#include <iostream>

class Event {
public:
	// VARIABLES
	Point* point;           // Point affilie a l'evenement
	bool is_a_site_event;   // Booleen signifiant si l'element est un site (true) ou pas (false)
	float y;                // Coordonnee affiliee au point
	BeachLine* parable;		// Parabole associee a l'evenement

	// CONSTRUCTEUR
	Event(Point* a_data, bool iase)
	{
		point = a_data;
		is_a_site_event = iase;
		y = a_data->y;
		parable = 0;
	}
};