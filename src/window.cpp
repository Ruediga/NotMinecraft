#include "window.h"

#include <iostream>

#include <glm/glm.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <util/stb_image.h>

Window::Window(GLFWwindow* window_)
	: win_size_x{ glfwGetVideoMode(glfwGetPrimaryMonitor())->width }, win_size_y{ glfwGetVideoMode(glfwGetPrimaryMonitor())->height },
	m_handle{ window_ }, icons{ 0 }, m_monitor{ glfwGetPrimaryMonitor() }, m_isFullscreen{ false }, m_cursorLocked{ false }
{
	glfwSetWindowUserPointer(m_handle, this);
	glfwSetFramebufferSizeCallback(m_handle, [](GLFWwindow* window, int width, int height)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			glViewport(0, 0, width, height);
		});
	glfwSetWindowSizeCallback(m_handle, [](GLFWwindow* window, int width, int height)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->setWinX(width);
			win->setWinY(height);
		});
	glfwSetWindowUserPointer(m_handle, nullptr);

	// set a icon
	icons[0].pixels = stbi_load("res/steve32x32.png", &icons[0].width, &icons[0].height, 0, 4); //rgba channels 
	glfwSetWindowIcon(m_handle, 1, icons);
	stbi_image_free(icons[0].pixels);
}

Window::~Window()
{
	glfwDestroyWindow(m_handle);
	glfwTerminate();
}

void Window::maximize()
{
	const GLFWvidmode* vm = glfwGetVideoMode(m_monitor);
	glfwSetWindowMonitor(m_handle, m_monitor, 0, 0, vm->width, vm->height, vm->refreshRate);
	m_isFullscreen = true;
}

void Window::minimize()
{
	const GLFWvidmode* vm = glfwGetVideoMode(m_monitor);
	glfwSetWindowMonitor(m_handle, NULL, 0, 0, vm->width, vm->height, vm->refreshRate);
	glfwMaximizeWindow(m_handle);
	m_isFullscreen = false;
}

void Window::lockCursor()
{
	glfwSetInputMode(m_handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	m_cursorLocked = true;
}

void Window::unlockCursor()
{
	glfwSetInputMode(m_handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	m_cursorLocked = false;
}