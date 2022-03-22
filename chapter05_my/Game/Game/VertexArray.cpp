#include "VertexArray.h"
#include<glew.h>
VertexArray::VertexArray(const float* verts, unsigned int numVerts, const unsigned int* indices, unsigned int numIndices)
{
}

VertexArray::~VertexArray()
{
}

void VertexArray::SetActive()
{
	glBindVertexArray(mVertesArray);
}
