#include "bezier1D.h"
#include "math.h"

Bezier1D::Bezier1D(void)
{
	for (int i = 0; i < this->num_of_segments; i++)
	{
		segments.push_back(glm::mat4(i)); // TODO change that?
	}
}

IndexedModel Bezier1D::GetLine(int resT)
{
	IndexedModel line;

}

LineVertex Bezier1D::GetVertex(int segment, int t)
{
	glm::mat4 segment_coord = this->segments[segment];
	glm::vec3 position = glm::vec3(segment_coord[0]) * float(pow((1 - t), 3)) +
		                 glm::vec3(segment_coord[1]) * float(3 * pow((1 - t), 2) * t) +
		                 glm::vec3(segment_coord[2]) * float(3 * pow((t), 2) * (t-1)) +
		                 glm::vec3(segment_coord[3]) * float(pow((t), 3));

	return LineVertex(position, glm::vec3(0, 0, 1));
}

LineVertex Bezier1D::GetControlPoint(int segment, int indx)
{
	LineVertex control_point = LineVertex(glm::vec3(this->segments[segment][indx]),glm::vec3(0,0,1));
	return control_point;
}

glm::vec3 Bezier1D::GetVelosity(int segment, int t)
{
	glm::mat4 segment_coord = this->segments[segment];
	glm::vec3 position = (glm::vec3(segment_coord[1]) - glm::vec3(segment_coord[0]))* float(3 * pow((1 - t), 2)) +
						 (glm::vec3(segment_coord[2]) - glm::vec3(segment_coord[1]))* float(6 * (1 - t) * t) +
						 (glm::vec3(segment_coord[3]) - glm::vec3(segment_coord[2]))* float(3 * pow((t), 2) * t);

	return position;
}

void Bezier1D::MoveControlPoint(int segment, int indx, bool preserveC1)
{
	//glm::mat4 segment_coord = this->segments[segment];
	// TODO WTF Tamir? to move where???

}


Bezier1D::~Bezier1D(void)
{
}
