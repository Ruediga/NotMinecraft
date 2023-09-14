#include "Game.h"

#include <iostream>
#include <chrono>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <algorithm>

#include "Rendering/SimpleCubeRenderer.h"

Game::Game(GLFWwindow* window_) :
	m_state{ GameRunning }, m_window{ Window( window_ ) }, m_player{ Player() },
	scr{ nullptr }, m_mouse{ Mouse() }, m_keyboard{ Keyboard() }, m_world{ World() }, m_shouldGoFullscreen{ 0 }, m_enableLineDraw{ 0 }
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

	texArray = new TextureArray();
	texArray->AddTextureToArray("res/grass_side.png");
	texArray->AddTextureToArray("res/grass_top.png");
	texArray->AddTextureToArray("res/grass_bottom.png");
}

Game::~Game()
{
	m_window.close();
}

void Game::handleInput(std::chrono::milliseconds dt)
{
	// delta time in seconds
	float dts = static_cast<float>(dt.count()) / 1000.0f;
	
	// also runs key callback input handling
	glfwPollEvents();




	// raycasting test
	glm::vec3 hit_pos = { 0, 0, 0 };

	// cast a ray and check for intersections with world
	if (m_pendingRayCast) {
		glm::vec3 relative_cam_pos = { m_player.cam.position.x * 4, m_player.cam.position.y * 4, m_player.cam.position.z * 4 };
		hit_pos = m_world.castRay(relative_cam_pos, m_player.cam.getNormalizedDirectionVector());
		m_pendingRayCast = false;
		m_world.breakBlock(hit_pos.x, hit_pos.y, hit_pos.z);
		std::cout << "x: " << hit_pos.x << ", y: " << hit_pos.y << ", z: " << hit_pos.z << "\n";
	}







	// CANNOT be done from callbacks or a seperate thread other than the main one!!!
	if (m_shouldGoFullscreen) {
		m_window.maximize();
	}
	else if (m_window.isFullscreen()) {
		m_window.minimize();
	}

	if (m_keyboard.keys[GLFW_KEY_LEFT_SHIFT].pressed)
		m_player.cam.triple_speed_enabled = true;
	if (m_keyboard.keys[GLFW_KEY_W].pressed)
		m_player.cam.updateMovement(Camera::Movement::FORWARD, dts);
	if (m_keyboard.keys[GLFW_KEY_S].pressed)
		m_player.cam.updateMovement(Camera::Movement::BACKWARD, dts);
	if (m_keyboard.keys[GLFW_KEY_A].pressed)
		m_player.cam.updateMovement(Camera::Movement::LEFT, dts);
	if (m_keyboard.keys[GLFW_KEY_D].pressed)
		m_player.cam.updateMovement(Camera::Movement::RIGHT, dts);
	if (m_keyboard.keys[GLFW_KEY_SPACE].pressed)
		m_player.cam.updateMovement(Camera::Movement::UP, dts);
	if (m_keyboard.keys[GLFW_KEY_LEFT_CONTROL].pressed)
		m_player.cam.updateMovement(Camera::Movement::DOWN, dts);
	// reset triple speed
	m_player.cam.triple_speed_enabled = false;

	std::string fps = std::to_string(1.0f / dts) += " fps";
	m_window.setTitle(fps.c_str());
}

void Game::loop()
{
	std::chrono::milliseconds deltaTime{ 0 };

	const int fps{ 100 };
	const std::chrono::milliseconds timePerFrame{ 1000 / fps };

	while (!m_window.shouldClose())
	{
		auto start_time = std::chrono::steady_clock::now();
	
		handleInput(deltaTime);

		renderGame();
		
		auto frame_time = std::chrono::steady_clock::now();
		//std::chrono::duration<double> time = frame_time - start_time;
		//std::cout << time * 1000 << "\n";
		auto waitDur{ std::chrono::duration_cast<std::chrono::milliseconds>(timePerFrame - (frame_time - start_time)) };
		if (waitDur.count() > 0) {
			std::this_thread::sleep_for(waitDur);
		}

		auto end_time = std::chrono::steady_clock::now();
		deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
	}
}

void Game::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
		m_keyboard.keys[key].pressed = true;
	if (action == GLFW_RELEASE)
		m_keyboard.keys[key].pressed = false;

	if (key == GLFW_KEY_F11 && action == GLFW_PRESS) {
		if (m_shouldGoFullscreen) {
			m_shouldGoFullscreen = false;
		}
		else {
			m_shouldGoFullscreen = true;
		}
	}

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
		if (key == GLFW_KEY_L && action == GLFW_PRESS) {
			if (m_enableLineDraw) {
				m_enableLineDraw = false;
			}
			else {
				m_enableLineDraw = true;
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
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
			m_pendingRayCast = true;
		}
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
	glEnable(GL_CULL_FACE);

	glClearColor(0.5f, 0.6f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	m_world.shader->use();
	m_world.shader->setFloat("blockSize", 0.25f);

	texArray->Bind();
	texArray->ActivateShaderArray(m_world.shader->ID);

	// projection matrix
	glm::mat4 projection = glm::perspective(glm::radians(m_player.cam.getZoom()), (float)m_window.getSize().x / (float)m_window.getSize().y, 0.0025f, 1000.0f);
	glViewport(0, 0, m_window.getSize().x, m_window.getSize().y);
	m_world.shader->setMat4("projection", projection);

	// camera matrix
	glm::mat4 view = m_player.cam.getViewMatrix();
	m_world.shader->setMat4("view", view);

	// draw only the edges
	if (m_enableLineDraw) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_CULL_FACE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_CULL_FACE);
	}

	for (Chunk* chunk : m_world.chunk_vec) {
		glBindVertexArray(chunk->VAO);
		glDrawArrays(GL_TRIANGLES, 0, chunk->meshData.size());
	}

	// don't rmv
	glfwSwapBuffers(m_window.getWindowHandle());
}