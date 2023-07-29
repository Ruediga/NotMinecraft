#include "RenderMaster.h"

#include "../window.h"
#include "../Game.h"

extern Game Minecraft;

RenderMaster::RenderMaster()
{
	glfwMakeContextCurrent(Minecraft.window()->getWindowHandle());

	// only draw outside triangles
	glEnable(GL_CULL_FACE);
	// depth testing
	glEnable(GL_DEPTH_TEST);
}

void RenderMaster::render()
{
	
}

void RenderMaster::finishFrame()
{
	// bg color
	glClearColor(1.0, 0.0, 0.0, 1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(Minecraft.window()->getWindowHandle());
}
