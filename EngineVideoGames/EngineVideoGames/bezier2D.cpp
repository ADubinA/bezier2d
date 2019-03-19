#include "bezier2D.h"


Bezier2D::Bezier2D(void)
{
}

Bezier2D::Bezier2D(Bezier1D & b, glm::vec3 axis, int circularSubdivision)
{
	this->circularSubdivision = circularSubdivision;
	this->axis = axis;
	this->b = b;
	//this->b = new Bezier1D();
}


Bezier2D::~Bezier2D(void)
{
}
