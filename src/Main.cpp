#include "Game.h"
#include "Window.h"

GLFWwindow* initialize();

int main()
{
	GLFWwindow* window = initialize();

	Game Minecraft{ window };

	Minecraft.loop();

	return 0;
}

// init libraries and set up a window
GLFWwindow* initialize()
{
	// glfw and glad
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	if (!monitor) {
		glfwTerminate();
		exit(-1);
	}
	const GLFWvidmode* video_mode = glfwGetVideoMode(monitor);
	if (!monitor) {
		glfwTerminate();
		exit(-1);
	}
	GLFWwindow* window = glfwCreateWindow(video_mode->width, video_mode->height, "DEFAULT", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(-1);
	}
	
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		exit(-1);
	}

	return window;
}