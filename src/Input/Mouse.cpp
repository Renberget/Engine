#include "Input/Mouse.hpp"
#include "Impl.hpp"

namespace input
{
    EnterEvent Mouse::sEnterEvent;

    void Mouse::setPos(const Vec2i& pos)
    {
        Impl::setMousePos(static_cast<double>(pos.x), static_cast<double>(pos.y));
    }

    Vec2i Mouse::getPos()
    {
        return Vec2i(Impl::getMousePos());
    }
    
    std::string_view Mouse::getName(Button button)
    {
        constexpr std::array<const char*, static_cast<size_t>(Button::EnumEnd)> names
        {
            "Left", "Right", "Middle",
            "Button 1", "Button 2", "Button 3", "Button 4", "Button 5"
        };
        return names[static_cast<size_t>(button)];
    }

    std::string_view Mouse::getName(Axis axis)
    {
        constexpr std::array<const char*, static_cast<size_t>(Axis::EnumEnd)> names
        {
            "Mouse X", "Mouse Y",
            "Scroll X", "Scroll Y"
        };
        return names[static_cast<size_t>(axis)];
    }

    bool Mouse::isPressed(Button button)
    {
        return Impl::isMouseButtonPressed(static_cast<int>(button));
    }

    EnterEvent& Mouse::enterEvent()
    {
        return sEnterEvent;
    }

    void Mouse::enterCallback(bool entered)
    {
        sEnterEvent(entered);
    }
}
