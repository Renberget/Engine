#pragma once
#include <vector>
#include <array>
#include <string_view>

namespace input
{
    class Map;

    class Gamepad
    {
    public:
        constexpr static size_t MaxCount = 16;

        enum Connection : uint8_t
        {
            Disconnected,
            Connected,
            ConnectedIncompatible
        };

        enum Button : int
        {
            A = 0, B = 1, X = 2, Y = 3,
            LeftBumper = 4, RightBumper = 5,
            Back = 6, Start = 7, Guide = 8,
            LeftThumb = 9, RightThumb = 10,
            DPadUp = 11, DPadRight = 12, DPadDown = 13, DPadLeft = 14
        };

        enum Axis : int
        {
            LeftAxisX = 0, LeftAxisY = 1,
            RightAxisX = 2, RightAxisY = 3,
            LeftTrigger = 4, RightTrigger = 5
        };

        Gamepad();

    private:
        void reset(int id);
        
    public:
        //Returns the active maps
        [[nodiscard]] std::vector<Map>& maps();
        //Returns the joystick name
        [[nodiscard]] std::string_view name() const;
        //Returns true if button is being pressed
        [[nodiscard]] bool isPressed(Button button) const;
        //Returns the current value of axis
        [[nodiscard]] float getAxis(Axis axis) const;
        //Returns the connection state
        [[nodiscard]] const Connection& connection() const;

    private:
        constexpr static size_t NbButtons = 15;
        constexpr static size_t NbAxes = 6;

        struct InputState
        {
            std::array<uint8_t, NbButtons> buttons;
            std::array<float, NbAxes> axes;
        };
        
        void setConnection(Connection connection);
        void pollEvents();

        std::vector<Map> mMaps;
        InputState mCurrentState;
        InputState mPreviousState;
        Connection mConnection;
        int mId;

        friend class Impl;
    };
}