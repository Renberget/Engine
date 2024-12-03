#include "Input/Keyboard.hpp"
#include "Impl.hpp"

namespace input
{
    TextEnter Keyboard::sTextEnterEvent;
    
    bool Keyboard::isPressed(Key key)
    {
        return Impl::isKeyPressed(static_cast<int>(key));
    }

    std::string_view Keyboard::getName(Key key)
    {
        if (const char* name = glfwGetKeyName(static_cast<int>(key), 0))
            return name;
        return "Unknown";
    }

    TextEnter& Keyboard::textEnterEvent()
    {
        return sTextEnterEvent;
    }

    void Keyboard::textEnterCallback(Codepoint codepoint)
    {
        sTextEnterEvent(codepoint);
    }
}
