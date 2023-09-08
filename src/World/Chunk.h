#pragma once

#include <glm/glm.hpp>

#include <stdint.h>

namespace ChunkData
{
	constexpr int CHUNK_SIZE_X = 16;
	constexpr int CHUNK_SIZE_Y = 128;
	constexpr int CHUNK_SIZE_Z = 16;
	constexpr int CHUNK_VOLUME = CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z;
}

class Chunk
{
public:
	uint8_t* genMesh();

	void setBlock(glm::uvec3 pos, uint8_t block);
	uint8_t getBlock(glm::uvec3 pos);

private:
	uint8_t m_chunk_array[ChunkData::CHUNK_VOLUME]{0};
};