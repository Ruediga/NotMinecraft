#include "Game.h"
#include "window.h"
#include "World/World.h"

#include <iostream>

#include "../lib/glm/glm.hpp"
#include <glad/glad.h>


Game::Game() :
	m_state{ MainMenuState },
	m_window{ nullptr },
	m_world{ nullptr }
{
	// setup glfw and glad and create a window
	if (!glfwInit()) {
		std::cerr << "ERROR: glfwInit() in Game.cpp failed initializing!\n";
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	m_window = new Window((char*)"Minecraft", (glm::ivec2)(800, 600));
	glfwMakeContextCurrent(m_window->getWindowHandle());
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "ERROR: glad initialization in Game.cpp failed!\n";
	}

	// create our world
	m_world = new World(1, "test world");
}

Game::~Game()
{

}

void Game::loop()
{
	while (!m_window->shouldClose())
	{
		// TODO: timing


		// events
		glfwPollEvents();

		m_world->update();
		m_world->render();
	}
}