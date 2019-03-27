#pragma once
#include "MovableGLM.h"
#include "VertexArray.hpp"
#include "shader.h"
#include "MeshConstructor.h"

#include "texture.h"

class Shape : public MovableGLM
{
private:

	
	Texture *tex;
	
	bool isCopy;
	
	
public:
	MeshConstructor *mesh;
	unsigned int mode;

	Shape(const Shape& shape,unsigned int mode);

	Shape(const std::string& fileName,unsigned int mode);
	
	Shape(const int SimpleShapeType,unsigned int mode);

	Shape(Bezier1D *curve, unsigned int xResolution,unsigned int yResolution,bool is2D,unsigned int mode);

	//MeshConstructor GetMesh();

	void AddTexture(const std::string& textureFileName);

	void Draw( const Shader& shader);

	virtual ~Shape(void);
};

