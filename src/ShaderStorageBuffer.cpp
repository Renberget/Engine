#include "ShaderStorageBuffer.hpp"
#include "Glfw.hpp"

ShaderStorageBuffer::Binding ShaderStorageBuffer::sCurrentBinding = 0;

ShaderStorageBuffer::ShaderStorageBuffer() : BlockBuffer() {}

void ShaderStorageBuffer::create()
{
	if (mBinding == InvalidBinding)
	{
		mBinding = sCurrentBinding++;
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, mBinding, Buffer::id());
	}
}

ShaderStorageBuffer::Binding ShaderStorageBuffer::binding() const
{
	return mBinding;
}
