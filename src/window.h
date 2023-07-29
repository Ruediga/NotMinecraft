#pragma once

#include "../lib/glm/glm.hpp"

#include "input.h"

class Window
{
private:
	// handle and window information
	GLFWwindow* m_handle = nullptr;
	
	// mouse and keyboard
	Keyboard m_keyboard;
	Mouse m_mouse;

	glm::ivec2 m_window_size;

public:
	// constructor / destructor
	Window(char* name, glm::ivec2 size);
	~Window();

	glm::ivec2 getSize() { return m_window_size; }

	Keyboard* getKeyboardPtr() { return &m_keyboard; }
	Mouse* getMousePtr() { return &m_mouse; }
	GLFWwindow* getWindowHandle() { return m_handle; }

	// closing
	void close() { glfwSetWindowShouldClose(m_handle, GLFW_TRUE); }
	bool shouldClose() { return glfwWindowShouldClose(m_handle); }

	bool m_cursorLocked;
};