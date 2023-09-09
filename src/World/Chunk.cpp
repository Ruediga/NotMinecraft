#include "Chunk.h"

#include <iostream>
#include <sstream>
#include <bitset>

Chunk::Chunk(int x, int y)
	: m_x{ x }, m_y{ y }
{
	// init array
	//for (int i = 0; i < ChunkData::CHUNK_VOLUME; ++i) {
	//	m_chunk_array[i] = 0;
	//}
}

void Chunk::setBlock(glm::uvec3 pos, uint8_t block)
{
	m_chunk_array[pos.x + pos.z * ChunkData::CHUNK_SIZE_X + pos.y * ChunkData::CHUNK_SIZE_X * ChunkData::CHUNK_SIZE_Z] = block;
}

void Chunk::setBlock(int x, int y, int z, uint8_t block)
{
	std::cout << m_chunk_array[x];
	m_chunk_array[x + z * ChunkData::CHUNK_SIZE_X + y * ChunkData::CHUNK_SIZE_X * ChunkData::CHUNK_SIZE_Z] = block;
}

uint8_t Chunk::getBlock(glm::uvec3 pos)
{
	return m_chunk_array[pos.x + pos.z * ChunkData::CHUNK_SIZE_X + pos.y * ChunkData::CHUNK_SIZE_X * ChunkData::CHUNK_SIZE_Z];
}

void Chunk::printChunk()
{
	for (int i = 0; i < 2000; i++) {
		uint8_t blockData = m_chunk_array[i];
		std::bitset<8> binary(blockData); // Convert the blockData to a binary string.
		std::cout << binary << "\n";
	}
}