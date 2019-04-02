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

IndexedModel Bezier2D::GetSurface(int resT, int resS)
{
	IndexedModel surface;
	int counter=0;
	Vertex vertex = Vertex(glm::vec3(0), glm::vec2(0), glm::vec3(0), glm::vec3(0));
	float time = 0.0f;
	for (int segment_indexT = 0; segment_indexT < this->b.num_of_segments; segment_indexT++)
	{
		for (int segment_indexS = 0; segment_indexS < this->b.num_of_segments; segment_indexS++)
		{
			for (int t = 0; t < resT; t++) {
				// calcualte line
				time = (float)t / resT;
				vertex = this->GetVertex(segment_indexT, segment_indexS, time, 0);

				// insert to indexed model line
				surface.positions.push_back(*vertex.GetPos());
				surface.colors.push_back(*vertex.GetColor());
				surface.normals.push_back(glm::vec3(1));
				surface.texCoords.push_back(glm::vec2(1));
				surface.indices.push_back(counter);
				counter++;
			}
			
		}
		time = 0.0f;
	}
	
	return surface;
}

Vertex Bezier2D::GetVertex(int segmentT, int segmentS, float t, float s)
{
	glm::mat4 segment_coordT = this->b.segments[segmentT];

	glm::mat4 rotateMat= glm::rotate((float)((360*segmentS) / this->circularSubdivision), this->axis);
	

	glm::vec3 pos= glm::vec3(rotateMat * glm::vec4(*b.GetVertex(segmentT, t).GetPos(),1));
	glm::vec2 texCoord = glm::vec2(0);
	glm::vec3 normal = glm::vec3(0); //TODO change that
	glm::vec3 color = *b.GetVertex(segmentT, t).GetColor();
	glm::vec3 weight = glm::vec3(0);
	Vertex vertex = Vertex(pos, texCoord, normal, color);
	  
	return vertex;
}


Bezier2D::~Bezier2D(void)
{
	//delete &this->b;
}
