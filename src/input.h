#pragma once

// prevent glad include errors
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Window;

// mouse and keyboard handling: callbacks update the status
struct Button
{
	bool pressed;
};

struct Keyboard
{
	Button keys[GLFW_KEY_LAST]{ false };

	Keyboard() = default;
	void init(Window* window);

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

struct Mouse
{
	bool first = true;

	double pos_x = 0, pos_y = 0;
	double last_x = 0, last_y = 0;
	double x_offset = 0, y_offset = 0;
	double scrollOffset = 0;

	Button buttons[GLFW_MOUSE_BUTTON_LAST]{ false };

	Mouse() = default;
	void init(Window* window);

	// callbacks
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};