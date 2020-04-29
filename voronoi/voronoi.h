#include <queue>
#include <set>

#include "point.h"
#include "edge.h"
#include "beach_line.h"
#include "event.h"

class Voronoi {
public:
    // VARIABLES
    int width;
    int height;

    float y_beach;
    std::priority_queue<Event*> queue;
    std::set<Event*> set_events_deleted;
    BeachLine* line;
    std::list<Edge*> list_edges;

    // CONSTRUCTEUR
    Voronoi();

    // METHODES
    std::list<Edge*> voronoi_diagram(std::set<Point*> set_sites, int w, int h);
    void handle_site_event(Point* site);
    void handle_circle_event(BeachLine* parable);
    void check_circle_event(BeachLine* parable);
    BeachLine* search(BeachLine* line, int val);
    float get_length_site(Point* s, Point* site);
    float get_length_beach(float y_data, float y_beach);
    float get_y_parable(Point* point, float x);
    Point* get_edge_intersection(Edge* xl, Edge* xr);

    void FinishEdge(BeachLine* n);
    double GetXOfEdge(BeachLine* par, double y);
    BeachLine* GetParabolaByX(double xx);
    
};