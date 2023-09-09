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
	Chunk(int x, int y);

	void setBlock(glm::uvec3 pos, uint8_t block);
	void setBlock(int x, int y, int z, uint8_t block);
	uint8_t getBlock(glm::uvec3 pos);

	void printChunk();

private:
	int m_x, m_y;
	uint8_t m_chunk_array[ChunkData::CHUNK_VOLUME]{ 0 };
};