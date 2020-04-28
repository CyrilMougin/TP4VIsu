// Inspire de : 
// Fortune’s algorithm and implementation : http://blog.ivank.net/fortunes-algorithm-and-implementation.html#impl_cpp

#include <iostream>

#include "point.cpp"

class Event {
public:

	Point* point;           // Point affilie a l'evenement
	bool is_a_site_event;   // Booleen signifiant si l'element est un site (true) ou pas (false)
	float y;                // Coordonnee affiliee au point
	BeachLine* parable;		// Parabole associee a l'evenement

	Event(Point* a_data, bool iase)
	{
		point = a_data;
		is_a_site_event = iase;
		y = a_data->point.y;
		parable = 0;
	}
};