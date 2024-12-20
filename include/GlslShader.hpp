#pragma once
#include "Shader.hpp"

class GlslShader : public Shader
{
public:
    GlslShader() = default;
    GlslShader(GlslShader&& glslShader) noexcept;
    GlslShader& operator=(GlslShader&& glslShader) noexcept;
    //Creates shader from files
    void createFromFiles(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath, const std::filesystem::path& geometryPath = {});
    //Creates shader from code
    void createFromCode(std::string_view vertexCode, std::string_view fragmentCode, std::string_view geometryCode = {});
    //Returns the uniform location based on its name
    [[nodiscard]] int32_t getLocation(const std::string& name) const;
    //Returns the block index based on its name
    [[nodiscard]] uint32_t getBlockIndex(const std::string& name) const;
    void setUniform(const std::string& name, float_t value);
    void setUniform(const std::string& name, const Vec2f& value);
    void setUniform(const std::string& name, const Vec3f& value);
    void setUniform(const std::string& name, const Vec4f& value);
    void setUniform(const std::string& name, int32_t value);
    void setUniform(const std::string& name, const Vec2i& value);
    void setUniform(const std::string& name, const Vec3i& value);
    void setUniform(const std::string& name, const Vec4i& value);
    void setUniform(const std::string& name, uint32_t value);
    void setUniform(const std::string& name, const Vec2u& value);
    void setUniform(const std::string& name, const Vec3u& value);
    void setUniform(const std::string& name, const Vec4u& value);
    void setUniform(const std::string& name, const Mat2f& value);
    void setUniform(const std::string& name, const Mat2x3f& value);
    void setUniform(const std::string& name, const Mat2x4f& value);
    void setUniform(const std::string& name, const Mat3f& value);
    void setUniform(const std::string& name, const Mat3x2f& value);
    void setUniform(const std::string& name, const Mat3x4f& value);
    void setUniform(const std::string& name, const Mat4f& value);
    void setUniform(const std::string& name, const Mat4x2f& value);
    void setUniform(const std::string& name, const Mat4x3f& value);
    void setUniform(const std::string& name, const Transform2f& value);
    void setUniform(const std::string& name, const Transform3f& value);
    void setUniform(const std::string& name, const Color& color);
    void setUniform(const std::string& name, const std::span<const float_t>& values);
    void setUniform(const std::string& name, const std::span<const Vec2f>& values);
    void setUniform(const std::string& name, const std::span<const Vec3f>& values);
    void setUniform(const std::string& name, const std::span<const Vec4f>& values);
    void setUniform(const std::string& name, const std::span<const int32_t>& values);
    void setUniform(const std::string& name, const std::span<const Vec2i>& values);
    void setUniform(const std::string& name, const std::span<const Vec3i>& values);
    void setUniform(const std::string& name, const std::span<const Vec4i>& values);
    void setUniform(const std::string& name, const std::span<const uint32_t>& values);
    void setUniform(const std::string& name, const std::span<const Vec2u>& values);
    void setUniform(const std::string& name, const std::span<const Vec3u>& values);
    void setUniform(const std::string& name, const std::span<const Vec4u>& values);
    void setUniform(const std::string& name, const std::span<const Mat2f>& values);
    void setUniform(const std::string& name, const std::span<const Mat2x3f>& values);
    void setUniform(const std::string& name, const std::span<const Mat2x4f>& values);
    void setUniform(const std::string& name, const std::span<const Mat3f>& values);
    void setUniform(const std::string& name, const std::span<const Mat3x2f>& values);
    void setUniform(const std::string& name, const std::span<const Mat3x4f>& values);
    void setUniform(const std::string& name, const std::span<const Mat4f>& values);
    void setUniform(const std::string& name, const std::span<const Mat4x2f>& values);
    void setUniform(const std::string& name, const std::span<const Mat4x3f>& values);
    void setUniform(const std::string& name, const std::span<const Color>& colors);
    void setUniform(const std::string& name, const Texture& texture);
    void setUniform(const std::string& name, const UniformBuffer& buffer);
    void setUniform(const std::string& name, const ShaderStorageBuffer& buffer);
    using Shader::setUniform;

private:
    void attachShader(uint32_t type, std::span<const char> code);
    void registerUniforms();
    void registerBlockIndices(uint32_t blockType);

    struct Uniform
    {
        int32_t location;
        int32_t textureUnit;
        uint32_t blockIndex;
    };

    std::unordered_map<std::string, Uniform> mUniforms;
};