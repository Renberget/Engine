#include "Shader.hpp"
#include "Glfw.hpp"

void Shader::create()
{
	assert(!mId);
	mId = glCreateProgram();
}

Shader::Shader(Shader&& shader) noexcept :
	mTexturesUnits(std::move(shader.mTexturesUnits)),
	mTextures(std::move(shader.mTextures)),
	mId(shader.mId)
{
	shader.mId = 0;
}

Shader& Shader::operator=(Shader&& shader) noexcept
{
	mTexturesUnits = std::move(shader.mTexturesUnits);
	mTextures = std::move(shader.mTextures);
	mId = shader.mId;
	shader.mId = 0;
	return *this;
}

Shader::~Shader()
{
	glDeleteProgram(mId);
}

void Shader::setUniform(int32_t location, float_t value)
{
	glProgramUniform1f(mId, location, value);
}

void Shader::setUniform(int32_t location, const Vec2f& value)
{
	glProgramUniform2f(mId, location, value.x, value.y);
}

void Shader::setUniform(int32_t location, const Vec3f& value)
{
	glProgramUniform3f(mId, location, value.x, value.y, value.z);
}

void Shader::setUniform(int32_t location, const Vec4f& value)
{
	glProgramUniform4f(mId, location, value.x, value.y, value.z, value.w);
}

void Shader::setUniform(int32_t location, int32_t value)
{
	glProgramUniform1i(mId, location, value);
}

void Shader::setUniform(int32_t location, const Vec2i& value)
{
	glProgramUniform2i(mId, location, value.x, value.y);
}

void Shader::setUniform(int32_t location, const Vec3i& value)
{
	glProgramUniform3i(mId, location, value.x, value.y, value.z);
}

void Shader::setUniform(int32_t location, const Vec4i& value)
{
	glProgramUniform4i(mId, location, value.x, value.y, value.z, value.w);
}

void Shader::setUniform(int32_t location, uint32_t value)
{
	glProgramUniform1ui(mId, location, value);
}

void Shader::setUniform(int32_t location, const Vec2u& value)
{
	glProgramUniform2ui(mId, location, value.x, value.y);
}

void Shader::setUniform(int32_t location, const Vec3u& value)
{
	glProgramUniform3ui(mId, location, value.x, value.y, value.z);
}

void Shader::setUniform(int32_t location, const Vec4u& value)
{
	glProgramUniform4ui(mId, location, value.x, value.y, value.z, value.w);
}

void Shader::setUniform(int32_t location, const Mat2f& value)
{
	glProgramUniformMatrix2fv(mId, location, 1, GL_FALSE, value.matrix().data());
}

void Shader::setUniform(int32_t location, const Mat2x3f& value)
{
	glProgramUniformMatrix2x3fv(mId, location, 1, GL_FALSE, value.matrix().data());
}

void Shader::setUniform(int32_t location, const Mat2x4f& value)
{
	glProgramUniformMatrix2x4fv(mId, location, 1, GL_FALSE, value.matrix().data());
}

void Shader::setUniform(int32_t location, const Mat3f& value)
{
	glProgramUniformMatrix3fv(mId, location, 1, GL_FALSE, value.matrix().data());
}

void Shader::setUniform(int32_t location, const Mat3x2f& value)
{
	glProgramUniformMatrix3x2fv(mId, location, 1, GL_FALSE, value.matrix().data());
}

void Shader::setUniform(int32_t location, const Mat3x4f& value)
{
	glProgramUniformMatrix3x4fv(mId, location, 1, GL_FALSE, value.matrix().data());
}

void Shader::setUniform(int32_t location, const Mat4f& value)
{
	glProgramUniformMatrix4fv(mId, location, 1, GL_FALSE, value.matrix().data());
}

void Shader::setUniform(int32_t location, const Mat4x2f& value)
{
	glProgramUniformMatrix4x2fv(mId, location, 1, GL_FALSE, value.matrix().data());
}

void Shader::setUniform(int32_t location, const Mat4x3f& value)
{
	glProgramUniformMatrix4x3fv(mId, location, 1, GL_FALSE, value.matrix().data());
}

void Shader::setUniform(int32_t location, const Transform2f& value)
{
	glProgramUniformMatrix3fv(mId, location, 1, GL_FALSE, value.data().data());
}

void Shader::setUniform(int32_t location, const Transform3f& value)
{
	glProgramUniformMatrix4fv(mId, location, 1, GL_FALSE, value.data().data());
}

void Shader::setUniform(int32_t location, const Color& color)
{
	glProgramUniform4f(mId, location, color.r, color.g, color.b, color.a);
}

void Shader::setUniform(int32_t location, const std::span<const Vec2f>& values)
{
	glProgramUniform2fv(mId, location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLfloat*>(values.data()));
}

void Shader::setUniform(int32_t location, const std::span<const Vec3f>& values)
{
	glProgramUniform3fv(mId, location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLfloat*>(values.data()));
}

void Shader::setUniform(int32_t location, const std::span<const Vec4f>& values)
{
	glProgramUniform4fv(mId, location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLfloat*>(values.data()));
}

void Shader::setUniform(int32_t location, const std::span<const int32_t>& values)
{
	glProgramUniform1iv(mId, location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLint*>(values.data()));
}

void Shader::setUniform(int32_t location, const std::span<const Vec2i>& values)
{
	glProgramUniform2iv(mId, location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLint*>(values.data()));
}

void Shader::setUniform(int32_t location, const std::span<const Vec3i>& values)
{
	glProgramUniform3iv(mId, location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLint*>(values.data()));
}

void Shader::setUniform(int32_t location, const std::span<const Vec4i>& values)
{
	glProgramUniform4iv(mId, location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLint*>(values.data()));
}

void Shader::setUniform(int32_t location, const std::span<const uint32_t>& values)
{
	glProgramUniform1uiv(mId, location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLuint*>(values.data()));
}

void Shader::setUniform(int32_t location, const std::span<const Vec2u>& values)
{
	glProgramUniform2uiv(mId, location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLuint*>(values.data()));
}

void Shader::setUniform(int32_t location, const std::span<const Vec3u>& values)
{
	glProgramUniform3uiv(mId, location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLuint*>(values.data()));
}

void Shader::setUniform(int32_t location, const std::span<const Vec4u>& values)
{
	glProgramUniform4uiv(mId, location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLuint*>(values.data()));
}

void Shader::setUniform(int32_t location, const std::span<const Mat2f>& values)
{
	glProgramUniformMatrix2fv(mId, location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));
}

void Shader::setUniform(int32_t location, const std::span<const Mat2x3f>& values)
{
	glProgramUniformMatrix2x3fv(mId, location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));
}

void Shader::setUniform(int32_t location, const std::span<const Mat2x4f>& values)
{
	glProgramUniformMatrix2x4fv(mId, location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));
}

void Shader::setUniform(int32_t location, const std::span<const Mat3f>& values)
{
	glProgramUniformMatrix3fv(mId, location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));
}

void Shader::setUniform(int32_t location, const std::span<const Mat3x2f>& values)
{
	glProgramUniformMatrix3x2fv(mId, location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));
}

void Shader::setUniform(int32_t location, const std::span<const Mat3x4f>& values)
{
	glProgramUniformMatrix3x4fv(mId, location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));
}

void Shader::setUniform(int32_t location, const std::span<const Mat4f>& values)
{
	glProgramUniformMatrix4fv(mId, location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));
}

void Shader::setUniform(int32_t location, const std::span<const Mat4x2f>& values)
{
	glProgramUniformMatrix4x2fv(mId, location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));
}

void Shader::setUniform(int32_t location, const std::span<const Mat4x3f>& values)
{
	glProgramUniformMatrix4x3fv(mId, location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));
}

void Shader::setUniform(int32_t location, const std::span<const Color>& colors)
{
	glProgramUniform4fv(mId, location, static_cast<GLsizei>(colors.size()), reinterpret_cast<const GLfloat*>(colors.data()));
}

void Shader::setUniform(int32_t location, const Texture& texture)
{
	GLint index = mTexturesUnits.find(location)->second;
	glProgramUniform1i(mId, location, index);
	mTextures[index] = texture.id();
}

void Shader::setUniform(uint32_t index, const UniformBuffer& buffer)
{
#ifndef NDEBUG
	checkBlockLayout(GL_UNIFORM_BLOCK, index, buffer.layout());
#endif
	glUniformBlockBinding(mId, index, buffer.binding());
}

void Shader::setUniform(uint32_t index, const ShaderStorageBuffer& buffer)
{
#ifndef NDEBUG
	checkBlockLayout(GL_SHADER_STORAGE_BLOCK, index, buffer.layout());
#endif
	glShaderStorageBlockBinding(mId, index, buffer.binding());
}

void Shader::bind() const
{
	glUseProgram(mId);
	glBindTextures(0, static_cast<GLsizei>(mTextures.size()), mTextures.data());
}

std::vector<char> Shader::load(const std::filesystem::path& path, std::ifstream::openmode flags)
{
	std::ifstream file(path, flags);
	if (!file.is_open())
		throw std::runtime_error("File not found : " + path.string());
	std::vector<char> code(std::filesystem::file_size(path));
	file.read(code.data(), code.size());
	return code;
}

void Shader::checkBlockLayout(uint32_t blockType, uint32_t index, const std::vector<size_t>& layout)
{
	constexpr GLenum countProp = GL_NUM_ACTIVE_VARIABLES;
	GLint count;
	glGetProgramResourceiv(mId, blockType, index, 1, &countProp, 1, nullptr, &count);
	if (count != layout.size())
		throw std::runtime_error("The object layout must be the same as in the shader");

	constexpr GLenum variablesProp = GL_ACTIVE_VARIABLES;
	std::vector<GLint> variables(count);
	glGetProgramResourceiv(mId, blockType, index, 1, &variablesProp, count, nullptr, variables.data());
	std::vector<GLint> variablesOffsets(variables.size());
	for (size_t i = 0; i < variables.size(); ++i)
	{
		constexpr GLenum offsetProp = GL_OFFSET;
		glGetProgramResourceiv(mId, GL_UNIFORM, variables[i], 1, &offsetProp, 1, nullptr, &variablesOffsets[i]);
	}
	std::sort(variablesOffsets.begin(), variablesOffsets.end());
	for (size_t i = 0; i < variablesOffsets.size(); ++i)
	{
		if (variablesOffsets[i] != layout[i])
			throw std::runtime_error("The object layout must be the same as in the shader");
	}
}

void Shader::compile()
{
	glLinkProgram(mId);
#ifndef NDEBUG
	GLint logLength;
	glGetProgramiv(mId, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength)
	{
		std::string log(logLength, ' ');
		glGetProgramInfoLog(mId, static_cast<GLsizei>(logLength), nullptr, log.data());
		throw std::runtime_error(log);
	}
#endif
}

void Shader::registerTextures()
{
	GLint count;
	glGetProgramInterfaceiv(mId, GL_UNIFORM, GL_ACTIVE_RESOURCES, &count);
	int32_t textureUnit = 0;
	for (GLuint i = 0; i < static_cast<GLuint>(count); ++i)
	{
		constexpr std::array<GLenum, 2> propsName{ GL_LOCATION, GL_TYPE };
		std::array<GLint, propsName.size()> props;
		glGetProgramResourceiv(mId, GL_UNIFORM, i, static_cast<GLsizei>(propsName.size()), propsName.data(), static_cast<GLsizei>(props.size()), nullptr, props.data());
		if (props[1] == GL_SAMPLER_2D)
		{
			mTexturesUnits.insert({ props[0], textureUnit++ });
			mTextures.emplace_back(0);
		}
	}
	mTextures.shrink_to_fit();
}
