#include "Game.h"

#include <iostream>
#include <chrono>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>


#include "Rendering/SimpleCubeRenderer.h"

Game::Game(GLFWwindow* window_) :
	m_state{ GameRunning }, m_window{ Window( window_ ) }, m_player{ Player() },
	scr{ nullptr }, m_mouse{ Mouse() }, m_keyboard{ Keyboard() }
{
	// key callbacks
	glfwSetWindowUserPointer(m_window.getWindowHandle(), this);
	auto key_callback_wrapper = [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		auto game_obj = static_cast<Game*>(glfwGetWindowUserPointer(window));
		game_obj->key_callback(window, key, scancode, action, mods);
		};
	glfwSetKeyCallback(m_window.getWindowHandle(), key_callback_wrapper);

	auto cursor_position_callback_wrapper = [](GLFWwindow* window, double xpos, double ypos) {
		auto game_obj = static_cast<Game*>(glfwGetWindowUserPointer(window));
		game_obj->cursor_position_callback(window, xpos, ypos);
		};
	glfwSetCursorPosCallback(m_window.getWindowHandle(), cursor_position_callback_wrapper);

	auto mouse_button_callback_wrapper = [](GLFWwindow* window, int button, int action, int mods) {
		auto game_obj = static_cast<Game*>(glfwGetWindowUserPointer(window));
		game_obj->mouse_button_callback(window, button, action, mods);
		};
	glfwSetMouseButtonCallback(m_window.getWindowHandle(), mouse_button_callback_wrapper);

	auto scroll_callback_wrapper = [](GLFWwindow* window, double xoffset, double yoffset) {
		auto game_obj = static_cast<Game*>(glfwGetWindowUserPointer(window));
		game_obj->scroll_callback(window, xoffset, yoffset);
		};
	glfwSetScrollCallback(m_window.getWindowHandle(), scroll_callback_wrapper);

	scr = new SimpleCubeRenderer();
}

Game::~Game()
{
	m_window.close();
}

using micros = std::chrono::microseconds;
void Game::handleInput(std::chrono::microseconds dt)
{
	// delta time in seconds
	float dts = static_cast<float>(dt.count()) / 1000000.0f;
	
	// also runs key callback input handling
	glfwPollEvents();

	if (m_keyboard.keys[GLFW_KEY_W].pressed)
		m_player.cam.updateMovement(Camera::Movement::FORWARD, dts);
	if (m_keyboard.keys[GLFW_KEY_S].pressed)
		m_player.cam.updateMovement(Camera::Movement::BACKWARD, dts);
	if (m_keyboard.keys[GLFW_KEY_A].pressed)
		m_player.cam.updateMovement(Camera::Movement::LEFT, dts);
	if (m_keyboard.keys[GLFW_KEY_D].pressed)
		m_player.cam.updateMovement(Camera::Movement::RIGHT, dts);

	std::string fps = std::to_string(1.0f / dts);
	m_window.setTitle(fps.c_str());
}

void Game::loop()
{
	micros deltaTime{ 0 };

	while (!m_window.shouldClose())
	{
		auto start_time = std::chrono::high_resolution_clock::now();
	
		handleInput(deltaTime);
		
		renderGame();
		
		auto end_time = std::chrono::high_resolution_clock::now();
		deltaTime = std::chrono::duration_cast<micros>(end_time - start_time);
	}
}

void Game::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
		m_keyboard.keys[key].pressed = true;
	if (action == GLFW_RELEASE)
		m_keyboard.keys[key].pressed = false;



	switch (m_state)
	{
	case(MainMenu): {
		std::cerr << "empty implementation";
		break;
	}

	case(GameRunning): {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			m_window.close();
		}
		if (key == GLFW_KEY_P && action == GLFW_PRESS) {
			if (m_window.isCursorLocked()) {
				m_window.unlockCursor();
			}
			else {
				m_window.lockCursor();
			}
			break;
		}
		if (key == GLFW_KEY_O && action == GLFW_PRESS) {
			if (m_window.isFullscreen()) {
				m_window.minimize();
			}
			else {
				m_window.maximize();
			}
			break;
		}
		break;
	}

	case(GamePaused): {
		std::cerr << "empty implementation";
		break;
	}
	}
}

void Game::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	m_mouse.pos_x = xpos;
	m_mouse.pos_y = ypos;

	// if first mouse
	if (m_mouse.first)
	{
		m_mouse.last_x = xpos;
		m_mouse.last_y = ypos;
		m_mouse.first = false;
	}

	float x_offset = static_cast<float>(m_mouse.pos_x - m_mouse.last_x);
	float y_offset = static_cast<float>(m_mouse.last_y - m_mouse.pos_y);

	m_mouse.last_x = xpos;
	m_mouse.last_y = ypos;


	switch (m_state)
	{
	case(MainMenu): {
		std::cerr << "empty implementation";
		break;
	}

	case(GameRunning): {
		m_player.cam.updateView(x_offset, y_offset);
		break;
	}

	case(GamePaused): {
		std::cerr << "empty implementation";
		break;
	}
	}
}

void Game::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
		m_mouse.buttons[button].pressed = true;
	if (action == GLFW_RELEASE)
		m_mouse.buttons[button].pressed = false;


	switch (m_state)
	{
	case(MainMenu): {
		std::cerr << "empty implementation";
		break;
	}

	case(GameRunning): {
		break;
	}

	case(GamePaused): {
		std::cerr << "empty implementation";
		break;
	}
	}
}

void Game::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	switch (m_state)
	{
	case(MainMenu): {
		break;
	}

	case(GameRunning): {
		std::cerr << "empty implementation";
		break;
	}

	case(GamePaused): {
		std::cerr << "empty implementation";
		break;
	}
	}
}

void Game::renderGame()
{
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glClearColor(0.5f, 0.6f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	scr->shader->use();

	// projection matrix
	glm::mat4 projection = glm::perspective(glm::radians(m_player.cam.getZoom()), (float)m_window.getSize().x / (float)m_window.getSize().y, 0.1f, 1000.0f);
	scr->shader->setMat4("projection", projection);

	// camera matrix
	glm::mat4 view = m_player.cam.getViewMatrix();
	scr->shader->setMat4("view", view);

	scr->shader->setFloat("blockSize", 5.0f);

	glBindVertexArray(scr->vao);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// don't rmv
	glfwSwapBuffers(m_window.getWindowHandle());
}