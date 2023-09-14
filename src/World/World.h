#pragma once

#include "Chunk.h"
#include "../Abstract OpenGL/Shader.h"

#include <vector>
#include <map>
#include <utility>

class World
{
public:
	World();

	void addChunk(int x, int z);

	void fillChunk(Chunk* chunk);

	Chunk* findChunk(int x, int z);
	uint8_t findBlock(int x, int y, int z);
	void breakBlock(int x, int y, int z);

	Shader* shader;

	std::vector<Chunk*> chunk_vec;

	glm::vec3 castRay(const glm::vec3& camera_pos, const glm::vec3& direction);

private:
	// TODO: upgrade to unordered_map
	std::map<std::pair<int, int>, Chunk*> m_loadedChunks;
};