#pragma once
#include "Input/Manager.hpp"
#include "../WindowImpl.hpp"
#include <array>

namespace input
{
    class Impl
    {
    public:
        Impl() = delete;
        static void setCallbacks(GLFWwindow* windowHandle);
        static void pollEvents();
        static void setMousePos(double x, double y);
        [[nodiscard]] static std::vector<Gamepad*>& gamepads();
        [[nodiscard]] static Vec2d getMousePos();
        [[nodiscard]] static bool isMouseButtonPressed(int glfwMouseButton);
        [[nodiscard]] static bool isKeyPressed(int glfwKey);

    private:
        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
        static void mouseMoveCallback(GLFWwindow* window, double xPos, double yPos);
        static void textEnterCallback(GLFWwindow* window, Codepoint codepoint);
        static void mouseEnterCallback(GLFWwindow* window, int entered);
        static void dropCallback(GLFWwindow* window, int count, const char* paths[]);
        static void joystickStateChangeCallback(int id, int event);

        static std::array<Gamepad, Gamepad::MaxCount> sGamepads;
        static std::vector<Gamepad*> sActiveGamepads;
        static std::vector<std::string_view> sDropPaths;
        static Vec2f sLastMousePos;
    };
}
