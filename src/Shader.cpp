#include "Shader.hpp"
#include "Glfw.hpp"
#include <fstream>
#include <sstream>

Shader::Shader(Shader&& shader) noexcept :
	mId(shader.mId),
	mUniforms(std::move(shader.mUniforms)),
	mTextures(std::move(shader.mTextures))
{
	shader.mId = 0;
}

Shader& Shader::operator=(Shader&& shader) noexcept
{
	mId = shader.mId;
	mUniforms = std::move(shader.mUniforms);
	mTextures = std::move(shader.mTextures);
	shader.mId = 0;
	return *this;
}

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath)
{
	create(vertexPath, fragmentPath, geometryPath);
}

Shader::~Shader()
{
	glDeleteProgram(mId);
}

void Shader::create(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath)
{
	assert(!mId);
	mId = glCreateProgram();

	if (!vertexPath.empty())
		loadAndAttachShader(vertexPath, GL_VERTEX_SHADER);

	if (!fragmentPath.empty())
		loadAndAttachShader(fragmentPath, GL_FRAGMENT_SHADER);

	if (!geometryPath.empty())
		loadAndAttachShader(geometryPath, GL_GEOMETRY_SHADER);

	glLinkProgram(mId);
	GLint success;
	glGetProgramiv(mId, GL_LINK_STATUS, &success);
	if (!success)
	{
		std::array<GLchar, LogMaxSize> log;
		glGetProgramInfoLog(mId, static_cast<GLsizei>(log.size()), nullptr, log.data());
		throw std::runtime_error(log.data());
	}

	GLint maxNameLength;
	glGetProgramiv(mId, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLength);
	std::string name(static_cast<size_t>(maxNameLength), ' ');

	GLint count;
	glGetProgramiv(mId, GL_ACTIVE_UNIFORMS, &count);
	mUniforms.reserve(count);
	int32_t textureCount = 0;
	for (GLint i = 0; i < count; ++i)
	{
		UniformData data{};
		data.location = i;

		GLsizei nameLength;
		GLint size;
		GLenum type;
		glGetActiveUniform(mId, static_cast<GLuint>(i), maxNameLength, &nameLength, &size, &type, name.data());
		if (type == GL_SAMPLER_2D)
		{
			data.textureIndex = textureCount++;
			mTextures.push_back(nullptr);
		}
		mUniforms.insert({ std::string(name.c_str(), static_cast<size_t>(nameLength)), data });
	}
	
	glGetProgramiv(mId, GL_ACTIVE_UNIFORM_BLOCKS, &count);
	for (GLint i = 0; i < count; ++i)
	{
		GLuint index = static_cast<GLuint>(i);
		UniformData data{};
		data.location = index;

		GLint nameLength;
		glGetActiveUniformBlockiv(mId, index, GL_UNIFORM_BLOCK_NAME_LENGTH, &nameLength);
		name.resize(nameLength);
		glGetActiveUniformBlockName(mId, index, nameLength, nullptr, name.data());
		mUniforms.insert({ std::string(name.c_str(), static_cast<size_t>(nameLength - 1)), data });
	}
}

void Shader::bind() const
{
	glUseProgram(mId);
	for (size_t i = 0; i < mTextures.size(); ++i)
	{
		glActiveTexture(GL_TEXTURE0 + static_cast<GLenum>(i));
		glBindTexture(GL_TEXTURE_2D, mTextures[i]->id());
	}
}

void Shader::setUniform(const std::string& name, float_t value)
{
	glUseProgram(mId);
	glUniform1f(std::get<int32_t>(mUniforms.find(name)->second.location), value);
}

void Shader::setUniform(const std::string& name, const Vec2f& value)
{
	glUseProgram(mId);
	glUniform2f(std::get<int32_t>(mUniforms.find(name)->second.location), value.x, value.y);
}

void Shader::setUniform(const std::string& name, const Vec3f& value)
{
	glUseProgram(mId);
	glUniform3f(std::get<int32_t>(mUniforms.find(name)->second.location), value.x, value.y, value.z);
}

void Shader::setUniform(const std::string& name, const Vec4f& value)
{
	glUseProgram(mId);
	glUniform4f(std::get<int32_t>(mUniforms.find(name)->second.location), value.x, value.y, value.z, value.w);
}

void Shader::setUniform(const std::string& name, int32_t value)
{
	glUseProgram(mId);
	glUniform1i(std::get<int32_t>(mUniforms.find(name)->second.location), value);
}

void Shader::setUniform(const std::string& name, const Vec2i& value)
{
	glUseProgram(mId);
	glUniform2i(std::get<int32_t>(mUniforms.find(name)->second.location), value.x, value.y);
}

void Shader::setUniform(const std::string& name, const Vec3i& value)
{
	glUseProgram(mId);
	glUniform3i(std::get<int32_t>(mUniforms.find(name)->second.location), value.x, value.y, value.z);
}

void Shader::setUniform(const std::string& name, const Vec4i& value)
{
	glUseProgram(mId);
	glUniform4i(std::get<int32_t>(mUniforms.find(name)->second.location), value.x, value.y, value.z, value.w);
}

void Shader::setUniform(const std::string& name, uint32_t value)
{
	glUseProgram(mId);
	glUniform1ui(std::get<int32_t>(mUniforms.find(name)->second.location), value);
}

void Shader::setUniform(const std::string& name, const Vec2u& value)
{
	glUseProgram(mId);
	glUniform2ui(std::get<int32_t>(mUniforms.find(name)->second.location), value.x, value.y);
}

void Shader::setUniform(const std::string& name, const Vec3u& value)
{
	glUseProgram(mId);
	glUniform3ui(std::get<int32_t>(mUniforms.find(name)->second.location), value.x, value.y, value.z);
}

void Shader::setUniform(const std::string& name, const Vec4u& value)
{
	glUseProgram(mId);
	glUniform4ui(std::get<int32_t>(mUniforms.find(name)->second.location), value.x, value.y, value.z, value.w);
}

void Shader::setUniform(const std::string& name, const Mat2& value)
{
	glUseProgram(mId);
	glUniformMatrix2fv(std::get<int32_t>(mUniforms.find(name)->second.location), 1, GL_FALSE, value.matrix());
}

void Shader::setUniform(const std::string& name, const Mat2x3& value)
{
	glUseProgram(mId);
	glUniformMatrix2x3fv(std::get<int32_t>(mUniforms.find(name)->second.location), 1, GL_FALSE, value.matrix());
}

void Shader::setUniform(const std::string& name, const Mat2x4& value)
{
	glUseProgram(mId);
	glUniformMatrix2x4fv(std::get<int32_t>(mUniforms.find(name)->second.location), 1, GL_FALSE, value.matrix());
}

void Shader::setUniform(const std::string& name, const Mat3& value)
{
	glUseProgram(mId);
	glUniformMatrix3fv(std::get<int32_t>(mUniforms.find(name)->second.location), 1, GL_FALSE, value.matrix());
}

void Shader::setUniform(const std::string& name, const Mat3x2& value)
{
	glUseProgram(mId);
	glUniformMatrix3x2fv(std::get<int32_t>(mUniforms.find(name)->second.location), 1, GL_FALSE, value.matrix());
}

void Shader::setUniform(const std::string& name, const Mat3x4& value)
{
	glUseProgram(mId);
	glUniformMatrix3x4fv(std::get<int32_t>(mUniforms.find(name)->second.location), 1, GL_FALSE, value.matrix());
}

void Shader::setUniform(const std::string& name, const Mat4& value)
{
	glUseProgram(mId);
	glUniformMatrix4fv(std::get<int32_t>(mUniforms.find(name)->second.location), 1, GL_FALSE, value.matrix());
}

void Shader::setUniform(const std::string& name, const Mat4x2& value)
{
	glUseProgram(mId);
	glUniformMatrix4x2fv(std::get<int32_t>(mUniforms.find(name)->second.location), 1, GL_FALSE, value.matrix());
}

void Shader::setUniform(const std::string& name, const Mat4x3& value)
{
	glUseProgram(mId);
	glUniformMatrix4x3fv(std::get<int32_t>(mUniforms.find(name)->second.location), 1, GL_FALSE, value.matrix());
}

void Shader::setUniform(const std::string& name, const Color& color)
{
	glUseProgram(mId);
	glUniform4f(std::get<int32_t>(mUniforms.find(name)->second.location), color.r, color.g, color.b, color.a);
}

void Shader::setUniform(const std::string& name, const Texture& texture)
{
	glUseProgram(mId);
	const UniformData& uniform = mUniforms.find(name)->second;
	glUniform1i(std::get<int32_t>(uniform.location), uniform.textureIndex);
	mTextures[uniform.textureIndex] = &texture;
}

void Shader::setUniform(const std::string& name, const std::span<const float_t>& values)
{
	glUseProgram(mId);
	glUniform1fv(std::get<int32_t>(mUniforms.find(name)->second.location), static_cast<GLsizei>(values.size()), reinterpret_cast<const GLfloat*>(values.data()));
}

void Shader::setUniform(const std::string& name, const std::span<const Vec2f>& values)
{
	glUseProgram(mId);
	glUniform2fv(std::get<int32_t>(mUniforms.find(name)->second.location), static_cast<GLsizei>(values.size()), reinterpret_cast<const GLfloat*>(values.data()));
}

void Shader::setUniform(const std::string& name, const std::span<const Vec3f>& values)
{
	glUseProgram(mId);
	glUniform3fv(std::get<int32_t>(mUniforms.find(name)->second.location), static_cast<GLsizei>(values.size()), reinterpret_cast<const GLfloat*>(values.data()));
}

void Shader::setUniform(const std::string& name, const std::span<const Vec4f>& values)
{
	glUseProgram(mId);
	glUniform4fv(std::get<int32_t>(mUniforms.find(name)->second.location), static_cast<GLsizei>(values.size()), reinterpret_cast<const GLfloat*>(values.data()));
}

void Shader::setUniform(const std::string& name, const std::span<const int32_t>& values)
{
	glUseProgram(mId);
	glUniform1iv(std::get<int32_t>(mUniforms.find(name)->second.location), static_cast<GLsizei>(values.size()), reinterpret_cast<const GLint*>(values.data()));
}

void Shader::setUniform(const std::string& name, const std::span<const Vec2i>& values)
{
	glUseProgram(mId);
	glUniform2iv(std::get<int32_t>(mUniforms.find(name)->second.location), static_cast<GLsizei>(values.size()), reinterpret_cast<const GLint*>(values.data()));
}

void Shader::setUniform(const std::string& name, const std::span<const Vec3i>& values)
{
	glUseProgram(mId);
	glUniform3iv(std::get<int32_t>(mUniforms.find(name)->second.location), static_cast<GLsizei>(values.size()), reinterpret_cast<const GLint*>(values.data()));
}

void Shader::setUniform(const std::string& name, const std::span<const Vec4i>& values)
{
	glUseProgram(mId);
	glUniform4iv(std::get<int32_t>(mUniforms.find(name)->second.location), static_cast<GLsizei>(values.size()), reinterpret_cast<const GLint*>(values.data()));
}

void Shader::setUniform(const std::string& name, const std::span<const uint32_t>& values)
{
	glUseProgram(mId);
	glUniform1uiv(std::get<int32_t>(mUniforms.find(name)->second.location), static_cast<GLsizei>(values.size()), reinterpret_cast<const GLuint*>(values.data()));
}

void Shader::setUniform(const std::string& name, const std::span<const Vec2u>& values)
{
	glUseProgram(mId);
	glUniform2uiv(std::get<int32_t>(mUniforms.find(name)->second.location), static_cast<GLsizei>(values.size()), reinterpret_cast<const GLuint*>(values.data()));
}

void Shader::setUniform(const std::string& name, const std::span<const Vec3u>& values)
{
	glUseProgram(mId);
	glUniform3uiv(std::get<int32_t>(mUniforms.find(name)->second.location), static_cast<GLsizei>(values.size()), reinterpret_cast<const GLuint*>(values.data()));
}

void Shader::setUniform(const std::string& name, const std::span<const Vec4u>& values)
{
	glUseProgram(mId);
	glUniform4uiv(std::get<int32_t>(mUniforms.find(name)->second.location), static_cast<GLsizei>(values.size()), reinterpret_cast<const GLuint*>(values.data()));
}

void Shader::setUniform(const std::string& name, const std::span<const Mat2>& values)
{
	glUseProgram(mId);
	glUniformMatrix2fv(std::get<int32_t>(mUniforms.find(name)->second.location), static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));
}

void Shader::setUniform(const std::string& name, const std::span<const Mat2x3>& values)
{
	glUseProgram(mId);
	glUniformMatrix2x3fv(std::get<int32_t>(mUniforms.find(name)->second.location), static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));
}

void Shader::setUniform(const std::string& name, const std::span<const Mat2x4>& values)
{
	glUseProgram(mId);
	glUniformMatrix2x4fv(std::get<int32_t>(mUniforms.find(name)->second.location), static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));
}

void Shader::setUniform(const std::string& name, const std::span<const Mat3>& values)
{
	glUseProgram(mId);
	glUniformMatrix3fv(std::get<int32_t>(mUniforms.find(name)->second.location), static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));
}

void Shader::setUniform(const std::string& name, const std::span<const Mat3x2>& values)
{
	glUseProgram(mId);
	glUniformMatrix3x2fv(std::get<int32_t>(mUniforms.find(name)->second.location), static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));
}

void Shader::setUniform(const std::string& name, const std::span<const Mat3x4>& values)
{
	glUseProgram(mId);
	glUniformMatrix3x4fv(std::get<int32_t>(mUniforms.find(name)->second.location), static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));
}

void Shader::setUniform(const std::string& name, const std::span<const Mat4>& values)
{
	glUseProgram(mId);
	glUniformMatrix4fv(std::get<int32_t>(mUniforms.find(name)->second.location), static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));
}

void Shader::setUniform(const std::string& name, const std::span<const Mat4x2>& values)
{
	glUseProgram(mId);
	glUniformMatrix4x2fv(std::get<int32_t>(mUniforms.find(name)->second.location), static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));
}

void Shader::setUniform(const std::string& name, const std::span<const Mat4x3>& values)
{
	glUseProgram(mId);
	glUniformMatrix4x3fv(std::get<int32_t>(mUniforms.find(name)->second.location), static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));
}

void Shader::setUniform(const std::string& name, const std::span<const Color>& colors)
{
	glUseProgram(mId);
	glUniform4fv(std::get<int32_t>(mUniforms.find(name)->second.location), static_cast<GLsizei>(colors.size()), reinterpret_cast<const GLfloat*>(colors.data()));
}

void Shader::setUniform(const std::string& name, const UniformBuffer& buffer)
{
	glUniformBlockBinding(mId, std::get<uint32_t>(mUniforms.find(name)->second.location), buffer.bindingPoint());
}

uint32_t Shader::id() const
{
	return mId;
}

void Shader::loadAndAttachShader(const std::string& path, GLenum type)
{
	std::ifstream file(path);
	if (!file.is_open())
		throw std::runtime_error(path + " : File not found");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string string = buffer.str();
	const GLchar* code = string.c_str();

	GLuint id = glCreateShader(type);
	glShaderSource(id, 1, &code, nullptr);
	glCompileShader(id);

	GLint success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::array<GLchar, LogMaxSize> log;
		glGetShaderInfoLog(id, static_cast<GLsizei>(log.size()), nullptr, log.data());
		throw std::runtime_error(log.data());
	}
	glAttachShader(mId, id);
	glDeleteShader(id);
}
