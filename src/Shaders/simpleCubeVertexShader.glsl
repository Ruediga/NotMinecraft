#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in float aFaceID;
layout (location = 2) in float aVertexID;

uniform mat4 view;
uniform mat4 projection;

uniform float blockSize;

out vec3 vertexColor;

// winding order 0, 1, 2, 1, 0, 3
vec3 backFacePositions[4] = vec3[4](
	vec3(-0.5f, -0.5f, -0.5f), // Bottom left
	vec3(0.5f, -0.5f, -0.5f), // Top Right
	vec3(0.5f, 0.5f, -0.5f), // Top Left
	vec3(-0.5f, 0.5f, -0.5f)  // Bottom Right
);

vec3 frontFacePositions[4] = vec3[4](
	vec3(0.0f, 0.0f, 1.0f), // Bottom left
	vec3(1.0f, 1.0f, 1.0f), // Top Right
	vec3(0.0f, 1.0f, 1.0f), // Top Left
	vec3(1.0f, 0.0f, 1.0f)  // Bottom Right
);

vec3 leftFacePositions[4] = vec3[4](
	vec3(0.0f, 1.0f, 1.0f), // Top right
	vec3(0.0f, 0.0f, 0.0f), // Bottom left
	vec3(0.0f, 0.0f, 1.0f), // Top left
	vec3(0.0f, 1.0f, 0.0f)  // Bottom right
);

vec3 rightFacePositions[4] = vec3[4](
	vec3(1.0f, 1.0f, 1.0f), // Top right
	vec3(1.0f, 0.0f, 0.0f), // Bottom left
	vec3(1.0f, 1.0f, 0.0f), // Bottom right
	vec3(1.0f, 0.0f, 1.0f)  // Top left
);

vec3 topFacePositions[4] = vec3[4](
	vec3(0.0f, 1.0f, 0.0f),
	vec3(1.0f, 1.0f, 1.0f),
	vec3(1.0f, 1.0f, 0.0f),
	vec3(0.0f, 1.0f, 1.0f)
);

vec3 bottomFacePositions[4] = vec3[4](
	vec3(0.0f, 0.0f, 1.0f),
	vec3(1.0f, 0.0f, 0.0f),
	vec3(1.0f, 0.0f, 1.0f),
	vec3(0.0f, 0.0f, 0.0f)
);

// the order that vertices must be rendered
// because of the winding order required for backface culling
int indices[6] = int[6]( 0, 1, 2, 1, 0, 3 );

// of the six vertices per face send, depending on the face, figure out which vertex we are at and get the corresponding vertex local vector
void main()
{
	// position for the vertex in world space
	vec3 vertexPosition = aPos * blockSize;

	uint id = uint(aFaceID);
	int vid = int(aVertexID);

	// vertex position
	switch(id) {
		case 0u: // 0 is Index for Back face
			vertexPosition += backFacePositions[indices[vid]] * blockSize;
			break;
		case 1u: // 1 is Index for Front face
			vertexPosition += frontFacePositions[indices[vid]] * blockSize;
			break;
		case 2u: // 2 is Index for Left face
			vertexPosition += leftFacePositions[indices[vid]] * blockSize;
			break;
		case 3u: // 3 is Index for Right face
			vertexPosition += rightFacePositions[indices[vid]] * blockSize;
			break;
		case 4u: // 4 is Index for Top face
			vertexPosition += topFacePositions[indices[vid]] * blockSize;
			break;
		case 5u: // 5 is Index for Bottom face
			vertexPosition += bottomFacePositions[indices[vid]] * blockSize;
			break;
	}

	// for debugging purposes
	vertexColor = vec3(1.0f, 0.0f, 0.0f);

	gl_Position = projection * view * vec4(aPos, 1.0f);
}