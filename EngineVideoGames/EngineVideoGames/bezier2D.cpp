#include "bezier2D.h"


Bezier2D::Bezier2D(void)
{
}

Bezier2D::Bezier2D(Bezier1D& b, glm::vec3 axis, int circularSubdivision)
{
	this->circularSubdivision = circularSubdivision;
	this->axis = axis;
	this->b.segments = b.segments;
	//this->b = new Bezier1D();
}

/*Vertex Bezier2D::GetVertex(int segmentT, int segmentS, int t, int s)
{
	return Vertex(glm::vec3(0), glm::vec3(0));
}*/


Bezier2D::~Bezier2D(void)
{
	delete &this->b;
}
