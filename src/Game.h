#pragma once

#include "Player.h"

#include <chrono>

#include "window.h"
#include "Abstract OpenGL/Shader.h"

#include "Rendering/SimpleCubeRenderer.h"

struct Button
{
	bool pressed;
};

struct Keyboard
{
	Button keys[GLFW_KEY_LAST]{ false };
};

struct Mouse
{
	bool first = true;

	double pos_x = 0, pos_y = 0;
	double last_x = 0, last_y = 0;

	Button buttons[GLFW_MOUSE_BUTTON_LAST]{ false };
};

class Game
{
public:
	// constructor and destructor
	Game(GLFWwindow* window_);
	~Game();

	// main game Loop
	void loop();

	// game state
	enum State : unsigned char
	{
		MainMenu,
		GameRunning,
		GamePaused
	};

	// receive Game state
	State getState() const { return m_state; }

	// window getter
	Window& window() { return m_window; }

	void renderGame();

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	Mouse m_mouse;
	Keyboard m_keyboard;

private:
	SimpleCubeRenderer* scr;

	void handleInput(std::chrono::microseconds dt);

	Player m_player;

	// store the game state
	State m_state;

	// window specific input and display
	Window m_window;
};