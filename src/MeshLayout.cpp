#include "MeshLayout.hpp"
#include "Glfw.hpp"

void MeshLayout::registerAttribs(uint32_t vaoId, uint32_t vboId, Usage usage, const MeshLayout* previousLayout) const
{
	assert(mAttribs.size() <= GL_MAX_VERTEX_ATTRIB_BINDINGS);

	//Divisor is 0 for vertex attribs and 1 for instance attribs
	GLuint divisor = static_cast<GLuint>(usage);
	//Like divisor for now but may change later
	GLuint binding = static_cast<GLuint>(usage);
	glVertexArrayVertexBuffer(vaoId, binding, vboId, 0, mStride);
	
	GLuint startIndex = previousLayout ? static_cast<GLuint>(previousLayout->mAttribs.size()) : 0;
	GLuint offset = 0;
	for (size_t i = 0; i < mAttribs.size(); ++i)
	{
		GLuint index = startIndex + static_cast<GLuint>(i);
		glEnableVertexArrayAttrib(vaoId, index);
		glVertexArrayBindingDivisor(vaoId, index, divisor);

		if (mAttribs[i].type == Type::Double)
		{
			//Used for 64-bits data, only double for now
			glVertexArrayAttribLFormat(vaoId, index, mAttribs[i].size, static_cast<GLenum>(mAttribs[i].type), offset);
		}
		else if (mAttribs[i].isFloat || mAttribs[i].normalize)
		{
			//Used for floats and normalized integers
			glVertexArrayAttribFormat(vaoId, index, mAttribs[i].size, static_cast<GLenum>(mAttribs[i].type), static_cast<GLboolean>(mAttribs[i].normalize), offset);
		}
		else
		{
			//Used for unormalized integers
			glVertexArrayAttribIFormat(vaoId, index, mAttribs[i].size, static_cast<GLenum>(mAttribs[i].type), offset);
		}

		glVertexArrayAttribBinding(vaoId, index, binding);
		offset += mAttribs[i].size * mAttribs[i].elementSize;
	}
}
