#pragma once
#include "Maths/Math.hpp"
#include "Image.hpp"
#include "UniformBuffer.hpp"
#include "ShaderStorageBuffer.hpp"
#include <unordered_map>
#include <fstream>

class Shader : public Uncopyable
{
protected:
    Shader() = default;
    void create();

public:
    Shader(Shader&& shader) noexcept;
    Shader& operator=(Shader&& shader) noexcept;
    ~Shader();
    void setUniform(int32_t location, float_t value);
    void setUniform(int32_t location, const Vec2f& value);
    void setUniform(int32_t location, const Vec3f& value);
    void setUniform(int32_t location, const Vec4f& value);
    void setUniform(int32_t location, int32_t value);
    void setUniform(int32_t location, const Vec2i& value);
    void setUniform(int32_t location, const Vec3i& value);
    void setUniform(int32_t location, const Vec4i& value);
    void setUniform(int32_t location, uint32_t value);
    void setUniform(int32_t location, const Vec2u& value);
    void setUniform(int32_t location, const Vec3u& value);
    void setUniform(int32_t location, const Vec4u& value);
    void setUniform(int32_t location, const Mat2f& value);
    void setUniform(int32_t location, const Mat2x3f& value);
    void setUniform(int32_t location, const Mat2x4f& value);
    void setUniform(int32_t location, const Mat3f& value);
    void setUniform(int32_t location, const Mat3x2f& value);
    void setUniform(int32_t location, const Mat3x4f& value);
    void setUniform(int32_t location, const Mat4f& value);
    void setUniform(int32_t location, const Mat4x2f& value);
    void setUniform(int32_t location, const Mat4x3f& value);
    void setUniform(int32_t location, const Transform2f& value);
    void setUniform(int32_t location, const Transform3f& value);
    void setUniform(int32_t location, const Color& color);
    void setUniform(int32_t location, const std::span<const float_t>& values);
    void setUniform(int32_t location, const std::span<const Vec2f>& values);
    void setUniform(int32_t location, const std::span<const Vec3f>& values);
    void setUniform(int32_t location, const std::span<const Vec4f>& values);
    void setUniform(int32_t location, const std::span<const int32_t>& values);
    void setUniform(int32_t location, const std::span<const Vec2i>& values);
    void setUniform(int32_t location, const std::span<const Vec3i>& values);
    void setUniform(int32_t location, const std::span<const Vec4i>& values);
    void setUniform(int32_t location, const std::span<const uint32_t>& values);
    void setUniform(int32_t location, const std::span<const Vec2u>& values);
    void setUniform(int32_t location, const std::span<const Vec3u>& values);
    void setUniform(int32_t location, const std::span<const Vec4u>& values);
    void setUniform(int32_t location, const std::span<const Mat2f>& values);
    void setUniform(int32_t location, const std::span<const Mat2x3f>& values);
    void setUniform(int32_t location, const std::span<const Mat2x4f>& values);
    void setUniform(int32_t location, const std::span<const Mat3f>& values);
    void setUniform(int32_t location, const std::span<const Mat3x2f>& values);
    void setUniform(int32_t location, const std::span<const Mat3x4f>& values);
    void setUniform(int32_t location, const std::span<const Mat4f>& values);
    void setUniform(int32_t location, const std::span<const Mat4x2f>& values);
    void setUniform(int32_t location, const std::span<const Mat4x3f>& values);
    void setUniform(int32_t location, const std::span<const Color>& colors);
    void setUniform(int32_t location, const Texture& texture);
    void setUniform(uint32_t index, const UniformBuffer& buffer);
    void setUniform(uint32_t index, const ShaderStorageBuffer& buffer);
    //Binds shader as target for operations
    void bind() const;
    //Returns the OpenGL handle
    [[nodiscard]] inline uint32_t id() const { return mId; }

protected:
    static std::vector<char> load(const std::filesystem::path& path, std::ifstream::openmode flags = 0);
    void checkBlockLayout(uint32_t blockType, uint32_t index, const std::vector<size_t>& layout);
    void compile();
    void registerTextures();

    std::unordered_map<int32_t, int32_t> mTexturesUnits;
    std::vector<uint32_t> mTextures;
	uint32_t mId = 0;
};
