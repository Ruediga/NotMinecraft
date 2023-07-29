#pragma once

#include <array>

#include <glm.hpp>

#include "Block.h"

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 128
#define CHUNK_SIZE_Z 16

class Chunk
{
public:
	Chunk(glm::ivec2 chunk_position);
	~Chunk();

	// chunk manipulation
	void setBlock(glm::vec3& pos, Block::BlockType block_type);
	Block* getBlock(glm::vec3& pos);

	void render();

private:
	glm::ivec2 m_chunkPosition;
	std::array<std::array<std::array<Block, CHUNK_SIZE_X>, CHUNK_SIZE_Y>, CHUNK_SIZE_Z> m_chunkData;
};