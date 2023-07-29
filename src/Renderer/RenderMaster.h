#pragma once

#include <memory>

class Window;
struct Camera;

class RenderMaster
{
public:
	// load resources into memory, init opengl contexts
	RenderMaster();

	// updates 
	void finishFrame();

	// draw World
	void render();

private:

};