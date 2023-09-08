#include "Chunk.h"

uint8_t* Chunk::genMesh()
{
	return nullptr;
}

void Chunk::setBlock(glm::uvec3 pos, uint8_t block)
{
	m_chunk_array[pos.x + pos.z * ChunkData::CHUNK_SIZE_X + pos.y * ChunkData::CHUNK_SIZE_X * ChunkData::CHUNK_SIZE_Z] = block;
}

uint8_t Chunk::getBlock(glm::uvec3 pos)
{
	return m_chunk_array[pos.x + pos.z * ChunkData::CHUNK_SIZE_X + pos.y * ChunkData::CHUNK_SIZE_X * ChunkData::CHUNK_SIZE_Z];
}
