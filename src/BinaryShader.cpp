#include "BinaryShader.hpp"
#include "Glfw.hpp"
#include <fstream>

void BinaryShader::createFromFile(const std::filesystem::path& path, const Settings& settings)
{
	Shader::create();

	std::vector<char> code = load(path, std::ifstream::binary);
	if (!settings.vertexEntry.empty())
		attachShader(GL_VERTEX_SHADER, code, settings.vertexEntry, settings);

	if (!settings.fragmentEntry.empty())
		attachShader(GL_FRAGMENT_SHADER, code, settings.fragmentEntry, settings);

	if (!settings.geometryEntry.empty())
		attachShader(GL_GEOMETRY_SHADER, code, settings.geometryEntry, settings);

	Shader::compile();
	Shader::registerTextures();
}

void BinaryShader::createFromCode(std::span<const char> code, const Settings& settings)
{
	Shader::create();

	if (!settings.vertexEntry.empty())
		attachShader(GL_VERTEX_SHADER, code, settings.vertexEntry, settings);

	if (!settings.fragmentEntry.empty())
		attachShader(GL_FRAGMENT_SHADER, code, settings.fragmentEntry, settings);

	if (!settings.geometryEntry.empty())
		attachShader(GL_GEOMETRY_SHADER, code, settings.geometryEntry, settings);

	Shader::compile();
	Shader::registerTextures();
}

void BinaryShader::create(const FilesInfo& info, const Settings& settings)
{
	Shader::create();

	if (!info.vertexPath->empty())
		attachShader(GL_VERTEX_SHADER, load(*info.vertexPath), info.vertexEntry, settings);

	if (!info.fragmentPath->empty())
		attachShader(GL_FRAGMENT_SHADER, load(*info.fragmentPath), info.fragmentEntry, settings);

	if (!info.geometryPath->empty())
		attachShader(GL_GEOMETRY_SHADER, load(*info.geometryPath), info.geometryEntry, settings);

	Shader::compile();
	Shader::registerTextures();
}

void BinaryShader::create(const CodeInfo& info, const Settings& settings)
{
	Shader::create();

	if (!info.vertexCode.empty())
		attachShader(GL_VERTEX_SHADER, info.vertexCode, info.vertexEntry, settings);

	if (!info.fragmentCode.empty())
		attachShader(GL_FRAGMENT_SHADER, info.fragmentCode, info.fragmentEntry, settings);

	if (!info.geometryCode.empty())
		attachShader(GL_GEOMETRY_SHADER, info.geometryCode, info.geometryEntry, settings);

	Shader::compile();
	Shader::registerTextures();
}

void BinaryShader::attachShader(uint32_t type, std::span<const char> code, std::string_view entry, const Settings& settings)
{
	assert(settings.constantsIndex.size() == settings.constantsValue.size());

	GLuint id = glCreateShader(type);
	glShaderBinary(1, &id, GL_SHADER_BINARY_FORMAT_SPIR_V, reinterpret_cast<const void*>(code.data()), static_cast<GLsizei>(code.size()));
	glSpecializeShader(id, entry.data(), static_cast<GLuint>(settings.constantsIndex.size()), settings.constantsIndex.data(), settings.constantsValue.data());

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
