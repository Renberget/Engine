#pragma once
#include "Shader.hpp"

class BinaryShader : public Shader
{
public:
    struct Settings
    {
        std::string_view vertexEntry = "main";
        std::string_view fragmentEntry = "main";
        std::string_view geometryEntry = "main";
        std::span<const uint32_t> constantsIndex = {};
        std::span<const uint32_t> constantsValue = {};
    };

    struct FilesInfo : Settings
    {
        const std::filesystem::path* vertexPath = nullptr;
        const std::filesystem::path* fragmentPath = nullptr;
        const std::filesystem::path* geometryPath = nullptr;
    };

    struct CodeInfo : Settings
    {
        std::span<const char> vertexCode = {};
        std::span<const char> fragmentCode = {};
        std::span<const char> geometryCode = {};
    };

    BinaryShader() = default;
    void createFromFile(const std::filesystem::path& path, const Settings& settings);
    void createFromCode(std::span<const char> code, const Settings& settings);
    void create(const FilesInfo& info, const Settings& settings);
    void create(const CodeInfo& info, const Settings& settings);

private:
    void attachShader(uint32_t type, std::span<const char> code, std::string_view entry, const Settings& settings);
};
