#include "input.h"

#include "window.h"

// Initializer sets up key callbacks
void Keyboard::init(Window* window) {
    auto key_callback_wrapper = [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        auto window_obj = static_cast<Window*>(glfwGetWindowUserPointer(window));
        window_obj->getKeyboardPtr()->key_callback(window, key, scancode, action, mods);
    };
    glfwSetKeyCallback(window->getWindowHandle(), key_callback_wrapper);
}

// Initializer sets up button, position and scroll callbacks
void Mouse::init(Window* window) {
	auto cursor_position_callback_wrapper = [](GLFWwindow* window, double xpos, double ypos) {
		auto window_obj = static_cast<Window*>(glfwGetWindowUserPointer(window));
		window_obj->getMousePtr()->cursor_position_callback(window, xpos, ypos);
	};
	glfwSetCursorPosCallback(window->getWindowHandle(), cursor_position_callback_wrapper);

	auto mouse_button_callback_wrapper = [](GLFWwindow* window, int button, int action, int mods) {
		auto window_obj = static_cast<Window*>(glfwGetWindowUserPointer(window));
		window_obj->getMousePtr()->mouse_button_callback(window, button, action, mods);
	};
	glfwSetMouseButtonCallback(window->getWindowHandle(), mouse_button_callback_wrapper);

	auto scroll_callback_wrapper = [](GLFWwindow* window, double xoffset, double yoffset) {
		auto window_obj = static_cast<Window*>(glfwGetWindowUserPointer(window));
		window_obj->getMousePtr()->scroll_callback(window, xoffset, yoffset);
	};
	glfwSetScrollCallback(window->getWindowHandle(), scroll_callback_wrapper);
}

void Keyboard::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
		keys[key].pressed = true;
	if (action == GLFW_RELEASE)
		keys[key].pressed = false;
}

void Mouse::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	mousePos.x = xpos;
	mousePos.y = ypos;
}

void Mouse::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
		buttons[button].pressed = true;
	if (action == GLFW_RELEASE)
		buttons[button].pressed = false;
}

void Mouse::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	scrollOffset += yoffset;
}