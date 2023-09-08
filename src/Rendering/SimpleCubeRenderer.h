#pragma once

#include "../Abstract OpenGL/Shader.h"

class SimpleCubeRenderer
{
public:
	SimpleCubeRenderer();

	Shader* shader;
	unsigned int vao, vbo;
	float vertices[180];
};