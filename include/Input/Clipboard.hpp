#pragma once
#include <string_view>

namespace input
{
    class Clipboard
    {
    public:
        Clipboard() = delete;
        //Sets the content of the clipboard
        static void set(std::string_view input);
        //Returns the content of the clipboard
        [[nodiscard]] static std::string_view get();
    };
}