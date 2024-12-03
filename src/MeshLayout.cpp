#include "MeshLayout.hpp"
#include "Glfw.hpp"

void MeshLayout::registerAttribs(Usage usage, const MeshLayout* previousLayout) const
{
	GLuint startIndex = previousLayout ? previousLayout->mAttribs.size() : 0;
	//Divisor is 0 for vertex attribs and 1 for instance attribs
	GLuint divisor = static_cast<GLuint>(usage);
	size_t offset = 0;
	for (size_t i = 0; i < mAttribs.size(); ++i)
	{
		GLuint index = startIndex + static_cast<GLuint>(i);
		glEnableVertexAttribArray(index);
		glVertexAttribDivisor(index, divisor);
		if (mAttribs[i].isInt && !mAttribs[i].normalize)
		{
			//Used for unormalized integers
			glVertexAttribIPointer(index, mAttribs[i].size, static_cast<GLenum>(mAttribs[i].type), mStride, reinterpret_cast<const void*>(offset));
		}
		else
		{
			//Used for floats and normalized integers
			glVertexAttribPointer(index, mAttribs[i].size, static_cast<GLenum>(mAttribs[i].type), static_cast<GLboolean>(mAttribs[i].normalize), mStride, reinterpret_cast<const void*>(offset));
		}
		offset += mAttribs[i].size * mAttribs[i].elementSize;
	}
}
