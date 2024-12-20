#include "UniformBuffer.hpp"
#include "Glfw.hpp"

UniformBuffer::Binding UniformBuffer::sCurrentBinding = 0;

UniformBuffer::UniformBuffer() : BlockBuffer() {}

void UniformBuffer::create()
{
	if (mBinding == InvalidBinding)
	{
		mBinding = sCurrentBinding++;
		glBindBufferBase(GL_UNIFORM_BUFFER, mBinding, Buffer::id());
	}
}

UniformBuffer::Binding UniformBuffer::binding() const
{
	return mBinding;
}
