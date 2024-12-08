#pragma once
#include "Image.hpp"
#include "UniformBuffer.hpp"
#include "Maths/Mat.hpp"
#include <string>
#include <string_view>
#include <variant>
#include <unordered_map>

class Shader : public Uncopyable
{
public:
    Shader() = default;
    Shader(Shader&& shader) noexcept;
    Shader& operator=(Shader&& shader) noexcept;
    ~Shader();
    //Creates shader from files
    void createFromFiles(std::string_view vertex, std::string_view fragment, std::string_view geometry = {});
    //Creates shader from data
    void createFromData(std::string_view vertex, std::string_view fragment, std::string_view geometry = {});
    //Binds shader as target for operations
    void bind() const;
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
    void setUniform(const std::string& name, const Mat2& value);
    void setUniform(const std::string& name, const Mat2x3& value);
    void setUniform(const std::string& name, const Mat2x4& value);
    void setUniform(const std::string& name, const Mat3& value);
    void setUniform(const std::string& name, const Mat3x2& value);
    void setUniform(const std::string& name, const Mat3x4& value);
    void setUniform(const std::string& name, const Mat4& value);
    void setUniform(const std::string& name, const Mat4x2& value);
    void setUniform(const std::string& name, const Mat4x3& value);
    void setUniform(const std::string& name, const Color& color);
    void setUniform(const std::string& name, const Texture& texture);
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
    void setUniform(const std::string& name, const std::span<const Mat2>& values);
    void setUniform(const std::string& name, const std::span<const Mat2x3>& values);
    void setUniform(const std::string& name, const std::span<const Mat2x4>& values);
    void setUniform(const std::string& name, const std::span<const Mat3>& values);
    void setUniform(const std::string& name, const std::span<const Mat3x2>& values);
    void setUniform(const std::string& name, const std::span<const Mat3x4>& values);
    void setUniform(const std::string& name, const std::span<const Mat4>& values);
    void setUniform(const std::string& name, const std::span<const Mat4x2>& values);
    void setUniform(const std::string& name, const std::span<const Mat4x3>& values);
    void setUniform(const std::string& name, const std::span<const Color>& colors);
    void setUniform(const std::string& name, const UniformBuffer& buffer);
    //Returns the OpenGL handle
    [[nodiscard]] uint32_t id() const;

private:
    struct UniformData
    {
        std::variant<int32_t, uint32_t> location;
        int32_t textureIndex = -1;
    };

    constexpr static size_t LogMaxSize = 512;

    void compileAndRegisterUniforms();
    void loadAndAttachShader(std::string_view path, uint32_t type);
    void attachShader(std::string_view code, uint32_t type);

	uint32_t mId = 0;
    std::unordered_map<std::string, UniformData> mUniforms;
    std::vector<const Texture*> mTextures;
};
