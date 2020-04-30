#include <list>
#include <queue>
#include <set>

#include "point.h"
#include "edge.h"
#include "beach_line.h"
#include "event.h"
#include <functional>

namespace vor {

	typedef std::list<Point*> Points;
	typedef std::list<Edge*> Edges;

	class Voronoi {
	public:
		// VARIABLES
		double width;		// Largeur du diagramme
		double height;		// Hauteur du diagramme

		Points* list_sites;	// Liste des sites du diagramme
		Edges* list_edges;	// Liste des aretes du diagramme
		BeachLine* tree;	// Arbre de recherche binaire
		
		double beach;

		std::priority_queue<Event*, std::vector<Event*>, Event::CompareEvent> queue;

		// CONSTRUCTEUR
		Voronoi();

		// METHODES
		Edges* VoronoiDiagram(Points* v, int w, int h);					// Corps de l'aglorithme de Fortune
		void HandleSiteEvent(Point* point);								// Implementation du cas d'un site
		void HandleCircleEvent(BeachLine* parable);						// Implementation du cas d'un cercle
		
		void FinishEdge(BeachLine* parable);							// Definis une fin a toutes les aretes
		BeachLine* GetParable(double value);							// Recupere la parabole au dessus de la valeur
		void CheckCircle(BeachLine* parable);							// Verifie le cas du cercle pour une parabole donnee 
		
		double GetDiscriminantSolution(BeachLine* parable, double y);	// Calcul du discriminant entre deux courbes
		double GetYParable(Point* point, double x);						// Calcul la valeur de 'y' vis a vis de l'equation de la parabole
		double GetSiteLength(Point* s, Point* site);					// Calcul la distance entre deux points
		Point* GetEdgeIntersection(Edge* a, Edge* b);					// Calcul l'intersection entre deux aretes
		
	};

}
