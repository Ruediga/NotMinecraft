#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

class Window
{
public:
	Window(GLFWwindow* window_);
	~Window();

	glm::ivec2 getSize() { return { win_size_x, win_size_y }; }

	GLFWwindow* getWindowHandle() { return m_handle; }
	
	// window
	void setTitle(const char* text) { glfwSetWindowTitle(m_handle, text); }
	void maximize() { glfwSetWindowMonitor(m_handle, m_monitor, NULL, NULL, NULL, NULL, NULL); m_isFullscreen = true; }
	void minimize() { glfwSetWindowMonitor(m_handle, NULL, NULL, NULL, NULL, NULL, NULL); m_isFullscreen = false; }
	bool isFullscreen() const { return m_isFullscreen; }
	void close() { glfwSetWindowShouldClose(m_handle, GLFW_TRUE); }
	bool shouldClose() const { return glfwWindowShouldClose(m_handle); }

	// cursor
	void lockCursor() { glfwSetInputMode(m_handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED); m_cursorLocked = true; }
	void unlockCursor() { glfwSetInputMode(m_handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL); m_cursorLocked = false; }
	bool isCursorLocked() const { return m_cursorLocked; }

	void setWinX(int x) { win_size_x = x; }
	void setWinY(int y) { win_size_y = y; }
	
private:

	// taskbar icon
	GLFWimage icons[1];

	int win_size_x, win_size_y;
	bool m_cursorLocked, m_isFullscreen;

	GLFWmonitor* m_monitor = nullptr;
	GLFWwindow* m_handle = nullptr;
};