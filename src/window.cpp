#include "window.h"

#include <iostream>

Window::Window(char* name, glm::ivec2 size)
	: m_window_size{size}, m_keyboard{ Keyboard() }, m_mouse{ Mouse() }
{
	// create window
	m_handle = glfwCreateWindow(size.x, size.y, name, NULL, NULL);

	// set a global Userpointer to window class to access callbacks via a wrapper
	glfwSetWindowUserPointer(m_handle, this);

	// add mouse and keyboard input
	m_keyboard.init(this);
	m_mouse.init(this);

	// lock cursor to and maximize window
	glfwSetInputMode(m_handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	m_cursorLocked = true;
	glfwMaximizeWindow(m_handle);
}

Window::~Window()
{
	if (this->m_handle == nullptr) {
		return;
	}

	glfwTerminate();
}