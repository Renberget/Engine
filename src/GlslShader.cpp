#include "GlslShader.hpp"
#include "Glfw.hpp"

GlslShader::GlslShader(GlslShader&& glslShader) noexcept :
	Shader(std::move(glslShader)),
	mUniforms(std::move(glslShader.mUniforms)) {}

GlslShader& GlslShader::operator=(GlslShader&& glslShader) noexcept
{
	Shader::operator=(std::move(glslShader));
	mUniforms = std::move(glslShader.mUniforms);
	return *this;
}

void GlslShader::createFromFiles(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath, const std::filesystem::path& geometryPath)
{
	Shader::create();

	if (!vertexPath.empty())
		attachShader(GL_VERTEX_SHADER, load(vertexPath));

	if (!fragmentPath.empty())
		attachShader(GL_FRAGMENT_SHADER, load(fragmentPath));

	if (!geometryPath.empty())
		attachShader(GL_GEOMETRY_SHADER, load(geometryPath));

	Shader::compile();
	Shader::registerTextures();
	registerUniforms();
	registerBlockIndices(GL_UNIFORM_BLOCK);
	registerBlockIndices(GL_SHADER_STORAGE_BLOCK);
}

void GlslShader::createFromCode(std::string_view vertexCode, std::string_view fragmentCode, std::string_view geometryCode)
{
	Shader::create();

	if (!vertexCode.empty())
		attachShader(GL_VERTEX_SHADER, vertexCode);

	if (!fragmentCode.empty())
		attachShader(GL_FRAGMENT_SHADER, fragmentCode);

	if (!geometryCode.empty())
		attachShader(GL_GEOMETRY_SHADER, geometryCode);

	Shader::compile();
	Shader::registerTextures();
	registerUniforms();
	registerBlockIndices(GL_UNIFORM_BLOCK);
	registerBlockIndices(GL_SHADER_STORAGE_BLOCK);
}

int32_t GlslShader::getLocation(const std::string& name) const
{
	return mUniforms.find(name)->second.location;
}

uint32_t GlslShader::getBlockIndex(const std::string& name) const
{
	return mUniforms.find(name)->second.blockIndex;
}

void GlslShader::setUniform(const std::string& name, float_t value)
{
	glProgramUniform1f(mId, mUniforms.find(name)->second.location, value);
}

void GlslShader::setUniform(const std::string& name, const Vec2f& value)
{
	glProgramUniform2f(mId, mUniforms.find(name)->second.location, value.x, value.y);
}

void GlslShader::setUniform(const std::string& name, const Vec3f& value)
{
	glProgramUniform3f(mId, mUniforms.find(name)->second.location, value.x, value.y, value.z);
}

void GlslShader::setUniform(const std::string& name, const Vec4f& value)
{
	glProgramUniform4f(mId, mUniforms.find(name)->second.location, value.x, value.y, value.z, value.w);
}

void GlslShader::setUniform(const std::string& name, int32_t value)
{
	glProgramUniform1i(mId, mUniforms.find(name)->second.location, value);
}

void GlslShader::setUniform(const std::string& name, const Vec2i& value)
{
	glProgramUniform2i(mId, mUniforms.find(name)->second.location, value.x, value.y);
}

void GlslShader::setUniform(const std::string& name, const Vec3i& value)
{
	glProgramUniform3i(mId, mUniforms.find(name)->second.location, value.x, value.y, value.z);
}

void GlslShader::setUniform(const std::string& name, const Vec4i& value)
{
	glProgramUniform4i(mId, mUniforms.find(name)->second.location, value.x, value.y, value.z, value.w);
}

void GlslShader::setUniform(const std::string& name, uint32_t value)
{
	glProgramUniform1ui(mId, mUniforms.find(name)->second.location, value);
}

void GlslShader::setUniform(const std::string& name, const Vec2u& value)
{
	glProgramUniform2ui(mId, mUniforms.find(name)->second.location, value.x, value.y);
}

void GlslShader::setUniform(const std::string& name, const Vec3u& value)
{
	glProgramUniform3ui(mId, mUniforms.find(name)->second.location, value.x, value.y, value.z);
}

void GlslShader::setUniform(const std::string& name, const Vec4u& value)
{
	glProgramUniform4ui(mId, mUniforms.find(name)->second.location, value.x, value.y, value.z, value.w);
}

void GlslShader::setUniform(const std::string& name, const Mat2f& value)
{
	glProgramUniformMatrix2fv(mId, mUniforms.find(name)->second.location, 1, GL_FALSE, value.matrix().data());
}

void GlslShader::setUniform(const std::string& name, const Mat2x3f& value)
{
	glProgramUniformMatrix2x3fv(mId, mUniforms.find(name)->second.location, 1, GL_FALSE, value.matrix().data());
}

void GlslShader::setUniform(const std::string& name, const Mat2x4f& value)
{
	glProgramUniformMatrix2x4fv(mId, mUniforms.find(name)->second.location, 1, GL_FALSE, value.matrix().data());
}

void GlslShader::setUniform(const std::string& name, const Mat3f& value)
{
	glProgramUniformMatrix3fv(mId, mUniforms.find(name)->second.location, 1, GL_FALSE, value.matrix().data());
}

void GlslShader::setUniform(const std::string& name, const Mat3x2f& value)
{
	glProgramUniformMatrix3x2fv(mId, mUniforms.find(name)->second.location, 1, GL_FALSE, value.matrix().data());
}

void GlslShader::setUniform(const std::string& name, const Mat3x4f& value)
{
	glProgramUniformMatrix3x4fv(mId, mUniforms.find(name)->second.location, 1, GL_FALSE, value.matrix().data());
}

void GlslShader::setUniform(const std::string& name, const Mat4f& value)
{
	glProgramUniformMatrix4fv(mId, mUniforms.find(name)->second.location, 1, GL_FALSE, value.matrix().data());
}

void GlslShader::setUniform(const std::string& name, const Mat4x2f& value)
{
	glProgramUniformMatrix4x2fv(mId, mUniforms.find(name)->second.location, 1, GL_FALSE, value.matrix().data());
}

void GlslShader::setUniform(const std::string& name, const Mat4x3f& value)
{
	glProgramUniformMatrix4x3fv(mId, mUniforms.find(name)->second.location, 1, GL_FALSE, value.matrix().data());
}

void GlslShader::setUniform(const std::string& name, const Transform2f& value)
{
	glProgramUniformMatrix3fv(mId, mUniforms.find(name)->second.location, 1, GL_FALSE, value.data().data());
}

void GlslShader::setUniform(const std::string& name, const Transform3f& value)
{
	glProgramUniformMatrix4fv(mId, mUniforms.find(name)->second.location, 1, GL_FALSE, value.data().data());
}

void GlslShader::setUniform(const std::string& name, const Color& color)
{
	glProgramUniform4f(mId, mUniforms.find(name)->second.location, color.r, color.g, color.b, color.a);
}

void GlslShader::setUniform(const std::string& name, const std::span<const float_t>& values)
{
	glProgramUniform1fv(mId, mUniforms.find(name)->second.location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLfloat*>(values.data()));
}

void GlslShader::setUniform(const std::string& name, const std::span<const Vec2f>& values)
{
	glProgramUniform2fv(mId, mUniforms.find(name)->second.location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLfloat*>(values.data()));
}

void GlslShader::setUniform(const std::string& name, const std::span<const Vec3f>& values)
{
	glProgramUniform3fv(mId, mUniforms.find(name)->second.location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLfloat*>(values.data()));
}

void GlslShader::setUniform(const std::string& name, const std::span<const Vec4f>& values)
{
	glProgramUniform4fv(mId, mUniforms.find(name)->second.location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLfloat*>(values.data()));
}

void GlslShader::setUniform(const std::string& name, const std::span<const int32_t>& values)
{
	glProgramUniform1iv(mId, mUniforms.find(name)->second.location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLint*>(values.data()));
}

void GlslShader::setUniform(const std::string& name, const std::span<const Vec2i>& values)
{
	glProgramUniform2iv(mId, mUniforms.find(name)->second.location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLint*>(values.data()));
}

void GlslShader::setUniform(const std::string& name, const std::span<const Vec3i>& values)
{
	glProgramUniform3iv(mId, mUniforms.find(name)->second.location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLint*>(values.data()));
}

void GlslShader::setUniform(const std::string& name, const std::span<const Vec4i>& values)
{
	glProgramUniform4iv(mId, mUniforms.find(name)->second.location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLint*>(values.data()));
}

void GlslShader::setUniform(const std::string& name, const std::span<const uint32_t>& values)
{
	glProgramUniform1uiv(mId, mUniforms.find(name)->second.location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLuint*>(values.data()));
}

void GlslShader::setUniform(const std::string& name, const std::span<const Vec2u>& values)
{
	glProgramUniform2uiv(mId, mUniforms.find(name)->second.location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLuint*>(values.data()));
}

void GlslShader::setUniform(const std::string& name, const std::span<const Vec3u>& values)
{
	glProgramUniform3uiv(mId, mUniforms.find(name)->second.location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLuint*>(values.data()));
}

void GlslShader::setUniform(const std::string& name, const std::span<const Vec4u>& values)
{
	glProgramUniform4uiv(mId, mUniforms.find(name)->second.location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLuint*>(values.data()));
}

void GlslShader::setUniform(const std::string& name, const std::span<const Mat2f>& values)
{
	glProgramUniformMatrix2fv(mId, mUniforms.find(name)->second.location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));
}

void GlslShader::setUniform(const std::string& name, const std::span<const Mat2x3f>& values)
{
	glProgramUniformMatrix2x3fv(mId, mUniforms.find(name)->second.location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));
}

void GlslShader::setUniform(const std::string& name, const std::span<const Mat2x4f>& values)
{
	glProgramUniformMatrix2x4fv(mId, mUniforms.find(name)->second.location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));
}

void GlslShader::setUniform(const std::string& name, const std::span<const Mat3f>& values)
{
	glProgramUniformMatrix3fv(mId, mUniforms.find(name)->second.location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));
}

void GlslShader::setUniform(const std::string& name, const std::span<const Mat3x2f>& values)
{
	glProgramUniformMatrix3x2fv(mId, mUniforms.find(name)->second.location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));
}

void GlslShader::setUniform(const std::string& name, const std::span<const Mat3x4f>& values)
{
	glProgramUniformMatrix3x4fv(mId, mUniforms.find(name)->second.location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));
}

void GlslShader::setUniform(const std::string& name, const std::span<const Mat4f>& values)
{
	glProgramUniformMatrix4fv(mId, mUniforms.find(name)->second.location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));
}

void GlslShader::setUniform(const std::string& name, const std::span<const Mat4x2f>& values)
{
	glProgramUniformMatrix4x2fv(mId, mUniforms.find(name)->second.location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));
}

void GlslShader::setUniform(const std::string& name, const std::span<const Mat4x3f>& values)
{
	glProgramUniformMatrix4x3fv(mId, mUniforms.find(name)->second.location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));
}

void GlslShader::setUniform(const std::string& name, const std::span<const Color>& colors)
{
	glProgramUniform4fv(mId, mUniforms.find(name)->second.location, static_cast<GLsizei>(colors.size()), reinterpret_cast<const GLfloat*>(colors.data()));
}

void GlslShader::setUniform(const std::string& name, const Texture& texture)
{
	const Uniform& uniform = mUniforms.find(name)->second;
	glProgramUniform1i(mId, uniform.location, uniform.textureUnit);
	mTextures[uniform.textureUnit] = texture.id();
}

void GlslShader::setUniform(const std::string& name, const UniformBuffer& buffer)
{
	uint32_t index = mUniforms.find(name)->second.blockIndex;
#ifndef NDEBUG
	checkBlockLayout(GL_UNIFORM_BLOCK, index, buffer.layout());
#endif
	glUniformBlockBinding(mId, index, buffer.binding());
}

void GlslShader::setUniform(const std::string& name, const ShaderStorageBuffer& buffer)
{
	uint32_t index = mUniforms.find(name)->second.blockIndex;
#ifndef NDEBUG
	checkBlockLayout(GL_SHADER_STORAGE_BLOCK, index, buffer.layout());
#endif
	glShaderStorageBlockBinding(mId, index, buffer.binding());
}

void GlslShader::attachShader(uint32_t type, std::span<const char> code)
{
	const GLchar* const codeData = code.data();

	GLuint id = glCreateShader(type);
	glShaderSource(id, 1, &codeData, nullptr);
	glCompileShader(id);

#ifndef NDEBUG
	GLint logLength;
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength)
	{
		std::string log(logLength, ' ');
		glGetShaderInfoLog(id, static_cast<GLsizei>(logLength), nullptr, log.data());
		throw std::runtime_error(log);
	}
#endif
	glAttachShader(mId, id);
	glDeleteShader(id);
}

void GlslShader::registerUniforms()
{
	GLint count;
	glGetProgramInterfaceiv(mId, GL_UNIFORM, GL_ACTIVE_RESOURCES, &count);
	mUniforms.reserve(count);
	int32_t textureCount = 0;
	for (GLuint i = 0; i < static_cast<GLuint>(count); ++i)
	{
		constexpr std::array<GLenum, 4> propsName{ GL_LOCATION, GL_BLOCK_INDEX, GL_NAME_LENGTH, GL_TYPE };
		std::array<GLint, propsName.size()> props;
		glGetProgramResourceiv(mId, GL_UNIFORM, i, static_cast<GLsizei>(propsName.size()), propsName.data(), static_cast<GLsizei>(props.size()), nullptr, props.data());

		std::string name(props[2], ' ');
		glGetProgramResourceName(mId, GL_UNIFORM, i, props[2], nullptr, name.data());
		name.pop_back();

		if (props[1] == -1)
		{
			Uniform uniform
			{
				.location = props[0]
			};

			if (props[3] == GL_SAMPLER_2D)
			{
				uniform.textureUnit = textureCount++;
				mTextures.emplace_back(0);
			}
			mUniforms.insert({ std::move(name), std::move(uniform) });
		}
	}
	mTextures.shrink_to_fit();
}

void GlslShader::registerBlockIndices(uint32_t blockType)
{
	GLint count;
	glGetProgramInterfaceiv(mId, blockType, GL_ACTIVE_RESOURCES, &count);
	for (GLuint i = 0; i < static_cast<GLuint>(count); ++i)
	{
		constexpr GLenum propName = GL_NAME_LENGTH;
		GLint nameLength;
		glGetProgramResourceiv(mId, blockType, i, 1, &propName, 1, nullptr, &nameLength);

		std::string name(nameLength, ' ');
		glGetProgramResourceName(mId, blockType, i, nameLength, nullptr, name.data());
		name.pop_back();

		mUniforms.insert({ std::move(name), Uniform{ .blockIndex = i } });
	}
}
