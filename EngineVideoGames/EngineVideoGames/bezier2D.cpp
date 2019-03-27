#include "bezier2D.h"
#include "glm/gtx/transform.hpp"
# define M_PI           3.14159265358979323846  /* pi */




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

Vertex Bezier2D::GetVertex(int segmentT, int segmentS, int t, int s)
{
	glm::mat4 segment_coordT = this->b.segments[segmentT];

	glm::mat4 rotateMat= glm::rotate((float)((2 * M_PI*segmentS) / this->circularSubdivision), this->axis);
	for (int i = 0; i < 4; i++) {
		segment_coordT[i] = rotateMat *segment_coordT[i];
	}

	glm::vec3 pos=  *b.GetVertex(segmentT, t).GetPos();
	glm::vec2 texCoord = glm::vec2(0);
	glm::vec3 normal = glm::vec3(0); //TODO change that
	glm::vec3 color = *b.GetVertex(segmentT, t).GetColor();
	glm::vec3 weight = glm::vec3(0);
	Vertex vertex = Vertex(pos, texCoord, normal, color);
	  
	return vertex;
}


Bezier2D::~Bezier2D(void)
{
	delete &this->b;
}
