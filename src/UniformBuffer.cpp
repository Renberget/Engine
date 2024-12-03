#include "UniformBuffer.hpp"
#include "Glfw.hpp"

uint32_t UniformBuffer::CurrentBindingPoint = 0;

UniformBuffer::UniformBuffer() : Buffer(BufferType::Uniform) {}

void UniformBuffer::create()
{
	if (mBindingPoint == -1)
	{
		mBindingPoint = CurrentBindingPoint++;
		glBindBufferBase(GL_UNIFORM_BUFFER, mBindingPoint, Buffer::id());
	}
}

uint32_t UniformBuffer::bindingPoint() const
{
	return mBindingPoint;
}
