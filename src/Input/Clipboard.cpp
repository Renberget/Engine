#include "Input/Clipboard.hpp"
#include "Glfw.hpp"

namespace input
{
    void Clipboard::set(std::string_view input)
    {
        glfwSetClipboardString(nullptr, input.data());
    }

    std::string_view Clipboard::get()
    {
        return glfwGetClipboardString(nullptr);
    }
}
