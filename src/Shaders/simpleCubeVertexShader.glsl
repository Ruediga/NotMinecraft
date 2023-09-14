#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in float aFaceID;
layout (location = 2) in float aVertexID;
layout (location = 3) in float aTexID;

uniform mat4 view;
uniform mat4 projection;
uniform float blockSize;

out vec2 TexCoord;
out float TexID;


vec2 backfacetexCoords[6] = vec2[6](
    vec2(0.0f, 0.0f),
    vec2(1.0f, 1.0f),
    vec2(1.0f, 0.0f),
    vec2(1.0f, 1.0f),
    vec2(0.0f, 0.0f),
    vec2(0.0f, 1.0f)
);

vec2 frontfacetexCoords[6] = vec2[6](
    vec2(0.0f, 0.0f),
    vec2(1.0f, 0.0f),
    vec2(1.0f, 1.0f),
    vec2(1.0f, 1.0f),
    vec2(0.0f, 1.0f),
    vec2(0.0f, 0.0f)
);

vec2 leftfacetexCoords[6] = vec2[6](
    vec2(0.0f, 1.0f),
    vec2(1.0f, 1.0f),
    vec2(1.0f, 0.0f),
    vec2(1.0f, 0.0f),
    vec2(0.0f, 0.0f),
    vec2(0.0f, 1.0f)
);

vec2 rightfacetexCoords[6] = vec2[6](
    vec2(0.0f, 1.0f),
    vec2(1.0f, 0.0f),
    vec2(1.0f, 1.0f),
    vec2(1.0f, 0.0f),
    vec2(0.0f, 1.0f),
    vec2(0.0f, 0.0f)
);

vec2 topfacetexCoords[6] = vec2[6](
    vec2(0.0f, 1.0f),
    vec2(1.0f, 0.0f),
    vec2(1.0f, 1.0f),
    vec2(1.0f, 0.0f),
    vec2(0.0f, 1.0f),
    vec2(0.0f, 0.0f)
);

vec2 bottomfacetexCoords[6] = vec2[6](
    vec2(0.0f, 1.0f),
    vec2(1.0f, 1.0f),
    vec2(1.0f, 0.0f),
    vec2(1.0f, 0.0f),
    vec2(0.0f, 0.0f),
    vec2(0.0f, 1.0f)
);



// winding order 0, 1, 2, 1, 0, 3 (outdated)
vec3 backFacePositions[6] = vec3[6](
	vec3(-0.5f, -0.5f, -0.5f),
	vec3( 0.5f,  0.5f, -0.5f),
	vec3( 0.5f, -0.5f, -0.5f),
	vec3( 0.5f,  0.5f, -0.5f),
    vec3(-0.5f, -0.5f, -0.5f),
	vec3(-0.5f,  0.5f, -0.5f)
);

vec3 frontFacePositions[6] = vec3[6](
	vec3(-0.5f, -0.5f,  0.5f),
	vec3( 0.5f, -0.5f,  0.5f),
	vec3( 0.5f,  0.5f,  0.5f),
	vec3( 0.5f,  0.5f,  0.5f),
    vec3(-0.5f,  0.5f,  0.5f),
	vec3(-0.5f, -0.5f,  0.5f)
);

vec3 leftFacePositions[6] = vec3[6](
	vec3(-0.5f,  0.5f,  0.5f),
	vec3(-0.5f,  0.5f, -0.5f),
	vec3(-0.5f, -0.5f, -0.5f),
	vec3(-0.5f, -0.5f, -0.5f),
    vec3(-0.5f, -0.5f,  0.5f),
	vec3(-0.5f,  0.5f,  0.5f)
);

vec3 rightFacePositions[6] = vec3[6](
	vec3(0.5f,  0.5f,  0.5f),
	vec3(0.5f, -0.5f, -0.5f),
	vec3(0.5f,  0.5f, -0.5f),
	vec3(0.5f, -0.5f, -0.5f),
    vec3(0.5f,  0.5f,  0.5f),
	vec3(0.5f, -0.5f,  0.5f)
);

vec3 topFacePositions[6] = vec3[6](
	vec3(-0.5f,  0.5f, -0.5f),
	vec3( 0.5f,  0.5f,  0.5f),
	vec3( 0.5f,  0.5f, -0.5f),
	vec3( 0.5f,  0.5f,  0.5f),
    vec3(-0.5f,  0.5f, -0.5f),
	vec3(-0.5f,  0.5f,  0.5f)
);

vec3 bottomFacePositions[6] = vec3[6](
	vec3(-0.5f, -0.5f, -0.5f),
	vec3( 0.5f, -0.5f, -0.5f),
	vec3( 0.5f, -0.5f,  0.5f),
	vec3( 0.5f, -0.5f,  0.5f),
    vec3(-0.5f, -0.5f,  0.5f),
	vec3(-0.5f, -0.5f, -0.5f)
);

// of the six vertices per face send, depending on the face,
// figure out which vertex we are at and get the corresponding vertex local vector
void main()
{
	// position for the vertex in world space
	vec3 vertexPosition = aPos * blockSize;

	uint id = uint(aFaceID);
	int vid = int(aVertexID);

	// vertex position
	switch(id) {
		case 0u: // 0 is Index for Back face
			vertexPosition += backFacePositions[vid] * blockSize;
			TexCoord = backfacetexCoords[vid];
			break;
		case 1u: // 1 is Index for Front face
			vertexPosition += frontFacePositions[vid] * blockSize;
			TexCoord = frontfacetexCoords[vid];
			break;
		case 2u: // 2 is Index for Left face
			vertexPosition += leftFacePositions[vid] * blockSize;
			TexCoord = leftfacetexCoords[vid];
			break;
		case 3u: // 3 is Index for Right face
			vertexPosition += rightFacePositions[vid] * blockSize;
			TexCoord = rightfacetexCoords[vid];
			break;
		case 4u: // 4 is Index for Top face
			vertexPosition += topFacePositions[vid] * blockSize;
			TexCoord = topfacetexCoords[vid];
			break;
		case 5u: // 5 is Index for Bottom face
			vertexPosition += bottomFacePositions[vid] * blockSize;
			TexCoord = bottomfacetexCoords[vid];
			break;
	}

	TexID = aTexID;

	gl_Position = projection * view * vec4(vertexPosition, 1.0f);
}