#include "game.h"
#include <iostream>

static void printMat(const glm::mat4 mat)
{
	std::cout<<" matrix:"<<std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout<< mat[j][i]<<" ";
		std::cout<<std::endl;
	}
}


Game::Game():Scene(){curve = 0;}

Game::Game(glm::vec3 position,float angle,float hwRelation,float near, float far) : Scene(position,angle,hwRelation,near,far)
{ 
	curve = new Bezier1D();
}
void Game::addShape(int type,int parent,unsigned int mode)
{
		chainParents.push_back(parent);
		if(type!=BezierLine && type!=BezierSurface)
			shapes.push_back(new Shape(type,mode));
		else
		{
			if(type == BezierLine)
				shapes.push_back(new Shape(curve,30,30,false,mode));
			else
				shapes.push_back(new Shape(curve,30,30,true,mode));
		}
}

void Game::Init()
{
	addShape(Axis,-1,LINES);
	addShape(BezierLine, -1, LINE_STRIP);

	addShape(Cube, -1, TRIANGLES);

	Bezier1D line = *(shapes[1]->mesh)->curve;
	glm::vec3 tmp_control_point;
	for (int segment = 0; segment < line.num_of_segments; segment++) 
	{
		// TODO DON"T draw double
		for (int control_point = 0; control_point < 3; control_point++)
		{
			if ((control_point == 0) && (segment == 0))
			{
				
			}
			else
			{
				addShapeCopy(2, -1, TRIANGLES);
			}
			tmp_control_point = *line.GetControlPoint(segment, control_point).GetPos();

			pickedShape = 2 + segment*3 + control_point;

			//myTranslate(tmp_control_point, 0);
			
			shapeTransformation(xLocalTranslate, tmp_control_point.x);
			shapeTransformation(yLocalTranslate, tmp_control_point.y);
			shapeTransformation(zLocalTranslate, tmp_control_point.z);

			shapeTransformation(yScale, 0.1);
			shapeTransformation(xScale, 0.1);
			shapeTransformation(zScale, 0.1);
		}
	}
	
	//addShapeFromFile("../res/objs/testBoxNoUV.obj",-1,TRIANGLES);
	
	//translate all scene away from camera
	myTranslate(glm::vec3(0,0,-20),0);

	pickedShape = 0;

	shapeTransformation(yScale,10);
	shapeTransformation(xScale,10);
	shapeTransformation(zScale,10);

	
	//pickedShape = 1;
	//shapeTransformation(yScale, 5);
	//shapeTransformation(xScale, 5);
	//shapeTransformation(zScale, 5);
	//shapeTransformation(yGlobalTranslate,5);
	
	//pickedShape = 2;
	//shapeTransformation(yGlobalRotate,45);	

}

void Game::Update(glm::mat4 MVP,glm::mat4 Normal,Shader *s)
{
	int r = ((pickedShape+1) & 0x000000FF) >>  0;
	int g = ((pickedShape+1) & 0x0000FF00) >>  8;
	int b = ((pickedShape+1) & 0x00FF0000) >> 16;
	s->Bind();
	s->SetUniformMat4f("MVP", MVP);
	s->SetUniformMat4f("Normal", Normal);
	s->SetUniform4f("lightDirection", 0.0f , 0.0f, -1.0f, 1.0f);
	s->SetUniform4f("lightColor",r/255.0f, g/255.0f, b/255.0f,1.0f);
		
}

void Game::WhenRotate()
{
	if(pickedShape>=0)
		printMat(GetShapeTransformation());
}

void Game::WhenTranslate()
{
	if(pickedShape>=0)
	{
		glm::vec4 pos = GetShapeTransformation()*glm::vec4(0,0,0,1);
		std::cout<<"( "<<pos.x<<", "<<pos.y<<", "<<pos.z<<")"<<std::endl;
		Bezier1D line = *(shapes[1]->mesh)->curve;
		int segment = (pickedShape - 2) / 4;
		int index = (pickedShape - 2) % 4;
		line.MoveControlPoint(segment, index, false, pos);
		//delete shapes[1];
		shapes[1] = new Shape(&line, 30, 30, false, LINE_STRIP);
	}
}

Game::~Game(void)
{
	delete curve;
}
