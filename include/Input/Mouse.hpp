#pragma once
#include "Utils/Delegate.hpp"
#include "Maths/Vec2.hpp"
#include <string_view>
#include <array>

namespace input
{
    //The bool parameter is true when the mouse enters the window and false when the mouse leaves
    using EnterEvent = Delegate<bool>;
    
    class Mouse
    {
    public:
        enum class Button : int
        {
            Left = 0, Right = 1, Middle = 2,
            Button1 = 3, Button2 = 4, Button3 = 5, Button4 = 6, Button5 = 7,
            EnumEnd
        };

        enum class Axis : int
        {
            MoveX, MoveY,
            ScrollX, ScrollY,
            EnumEnd
        };

        Mouse() = delete;
        //Sets the mouse position in screen coordinates
        static void setPos(const Vec2i& pos);
        //Returns the mouse position in screen coordinates
        [[nodiscard]] static Vec2i getPos();
        //Returns the name of button
        [[nodiscard]] static std::string_view getName(Button button);
        //Returns the name of axis
        [[nodiscard]] static std::string_view getName(Axis axis);
        //Returns true if button is being pressed
        [[nodiscard]] static bool isPressed(Button button);
        //Returns the mouse enter event
        [[nodiscard]] static EnterEvent& enterEvent();

    private:
        static void enterCallback(bool entered);
        
        static EnterEvent sEnterEvent;
        
        friend class Impl;
    };
}