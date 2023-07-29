#pragma once

class Window;
class World;

class Game
{
public:
	// constructor and destructor
	Game();
	~Game();

	// main game Loop
	void loop();

	// game state -> use as read only!!!
	enum State : unsigned char
	{
		MainMenuState,
		SelectWorldState,
		CreateWorldState,
		SettingsState,
		GameRunningState,
		GamePausedState
	};

	// receive Game state
	State getState() const { return m_state; }

	// window getter
	Window* window() { return m_window; }

private:
	// store the game state
	State m_state;

	// window specific input and display
	Window* m_window;

	// manages meshing and world rendering
	World* m_world;
};