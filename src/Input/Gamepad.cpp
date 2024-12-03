#include "Input/Gamepad.hpp"
#include "Impl.hpp"

namespace input
{
    Gamepad::Gamepad() :
        mId(-1),
        mConnection(Connection::Disconnected),
        mCurrentState{ { GLFW_RELEASE }, { 0.f } },
        mPreviousState{ { GLFW_RELEASE }, { 0.f } } {}

    void Gamepad::reset(int id)
    {
        mId = id;
        mConnection = glfwJoystickIsGamepad(id) ? Connection::Connected : Connection::ConnectedIncompatible;
        
        for (uint8_t& button : mCurrentState.buttons)
            button = GLFW_RELEASE;
        for (float& axe : mCurrentState.axes)
            axe = 0.f;

        for (uint8_t& button : mPreviousState.buttons)
            button = GLFW_RELEASE;
        for (float& axe : mPreviousState.axes)
            axe = 0.f;
    }

    std::vector<Map>& Gamepad::maps()
    {
        return mMaps;
    }

    std::string_view Gamepad::name() const
    {
        return glfwGetGamepadName(mId);
    }

    bool Gamepad::isPressed(Button button) const
    {
        return mCurrentState.buttons[static_cast<size_t>(button)];
    }

    float Gamepad::getAxis(Axis axis) const
    {
        return mCurrentState.axes[static_cast<size_t>(axis)];
    }

    const Gamepad::Connection& Gamepad::connection() const
    {
        return mConnection;
    }

    void Gamepad::setConnection(Connection connection)
    {
        mConnection = connection;
    }

    void Gamepad::pollEvents()
    {
        if (mConnection != Connection::Connected)
            return;

        glfwGetGamepadState(mId, reinterpret_cast<GLFWgamepadstate*>(&mCurrentState));

        //Buttons
        for (size_t i = 0; i < mCurrentState.buttons.size(); ++i)
        {
            if (mCurrentState.buttons[i] != mPreviousState.buttons[i])
            {
                if (mCurrentState.buttons[i] == GLFW_PRESS)
                {
                    for (Map& map : mMaps)
                        map.applyInput(static_cast<Button>(i), true);
                }
                else if (mCurrentState.buttons[i] == GLFW_RELEASE)
                {
                    for (Map& map : mMaps)
                        map.applyInput(static_cast<Button>(i), false);
                }
            }
            mPreviousState.buttons[i] = mCurrentState.buttons[i];
        }

        //Axes
        for (size_t i = 0; i < mCurrentState.axes.size(); ++i)
        {
            if (mCurrentState.axes[i] != mPreviousState.axes[i])
            {
                for (Map& map : mMaps)
                    map.applyInput(static_cast<Axis>(i), mCurrentState.axes[i]);
            }
        }
    }
}
