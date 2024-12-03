#include "Impl.hpp"
#include "../WindowImpl.hpp"

namespace input
{
	std::array<Gamepad, Gamepad::MaxCount> Impl::sGamepads;
    std::vector<Gamepad*> Impl::sActiveGamepads;
    std::vector<std::string_view> Impl::sDropPaths;
    Vec2f Impl::sLastMousePos;
    
    std::vector<Gamepad*>& Impl::gamepads()
    {
        return sActiveGamepads;
    }

    Vec2d Impl::getMousePos()
    {
        Vec2d pos;
        glfwGetCursorPos(Window::Impl::getFocusedWindow()->handle(), &pos.x, &pos.y);
        return pos;
    }

    void Impl::setCallbacks(GLFWwindow* windowHandle)
    {
        glfwSetKeyCallback(windowHandle, keyCallback);
        glfwSetMouseButtonCallback(windowHandle, mouseButtonCallback);
        glfwSetScrollCallback(windowHandle, scrollCallback);
        glfwSetCursorPosCallback(windowHandle, mouseMoveCallback);
        glfwSetCharCallback(windowHandle, textEnterCallback);
        glfwSetCursorEnterCallback(windowHandle, mouseEnterCallback);
        glfwSetDropCallback(windowHandle, dropCallback);
        glfwSetJoystickCallback(joystickStateChangeCallback);
    }

    void Impl::pollEvents()
    {
        glfwPollEvents();
        for (Gamepad* gamepad : sActiveGamepads)
            gamepad->pollEvents();
    }

    void Impl::setMousePos(double x, double y)
    {
        glfwSetCursorPos(Window::Impl::getFocusedWindow()->handle(), x, y);
    }

    bool Impl::isMouseButtonPressed(int glfwMouseButton)
    {
        return static_cast<bool>(glfwGetMouseButton(Window::Impl::getFocusedWindow()->handle(), glfwMouseButton));
    }

    bool Impl::isKeyPressed(int glfwKey)
    {
        return static_cast<bool>(glfwGetKey(Window::Impl::getFocusedWindow()->handle(), glfwKey));
    }

    void Impl::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        Manager::keyCallback(static_cast<Key>(key), scancode, action, mods);
    }

    void Impl::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        Manager::mouseButtonCallback(static_cast<Mouse::Button>(button), action, mods);
    }

    void Impl::scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
    {
        Manager::scrollCallback(static_cast<float>(xOffset), static_cast<float>(yOffset));
    }

    void Impl::mouseMoveCallback(GLFWwindow* window, double xPos, double yPos)
    {
        const Vec2f newPos = { static_cast<float>(xPos), static_cast<float>(yPos) };
        Manager::mouseMoveCallback(newPos.x - sLastMousePos.x, newPos.y - sLastMousePos.y);
        sLastMousePos = newPos;
    }

    void Impl::textEnterCallback(GLFWwindow* window, Codepoint codepoint)
    {
        Keyboard::textEnterCallback(codepoint);
    }

    void Impl::mouseEnterCallback(GLFWwindow* window, int entered)
    {
        Mouse::enterCallback(static_cast<bool>(entered));
    }

    void Impl::dropCallback(GLFWwindow* window, int count, const char* paths[])
    {
        sDropPaths.clear();
        sDropPaths.reserve(static_cast<size_t>(count));
        for (int i = 0; i < count; i++)
        {
            sDropPaths.emplace_back(paths[i]);
        }
    }

    void Impl::joystickStateChangeCallback(int id, int event)
    {
        if (event == GLFW_CONNECTED)
        {
            sGamepads[id].reset(id);
            if (sGamepads[id].connection() == Gamepad::Connection::Connected)
                sActiveGamepads.push_back(&sGamepads[id]);
        }
        else if (event == GLFW_DISCONNECTED)
        {
            sGamepads[id].setConnection(Gamepad::Connection::Disconnected);
            for (auto it = sActiveGamepads.begin(); it != sActiveGamepads.end(); ++it)
                if (*it == &sGamepads[id])
                    sActiveGamepads.erase(it);
        }

        Manager::gamepadConnectionChange(sGamepads[id]);
    }
}
