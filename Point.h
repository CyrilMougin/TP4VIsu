#ifndef Point_h
#define Point_h

/*
	A structure that stores 2D point
*/

struct Point
{
public:

	double x, y;

	/*
		Constructor for structure; x, y - coordinates
	*/

	Point(double nx, double ny)
	{
		x = nx;
		y = ny;
	}
};

#endif