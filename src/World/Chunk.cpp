#include "Chunk.h"

Chunk::Chunk(glm::ivec2 chunk_position)
	: m_chunkPosition{ chunk_position }
{
}

Chunk::~Chunk()
{
}

void Chunk::setBlock(glm::vec3& pos, Block::BlockType block_type)
{
	m_chunkData[pos.x][pos.y][pos.z] = Block(block_type);
}

Block* Chunk::getBlock(glm::vec3& pos)
{
	return &m_chunkData[pos.x][pos.y][pos.z];
}

void Chunk::render()
{
	for (int x = 0; x <= CHUNK_SIZE_X; x++) {
		for (int y = 0; y <= CHUNK_SIZE_X; y++) {
			for (int z = 0; z <= CHUNK_SIZE_X; z++) {
				m_chunkData[x][y][z].render();
			}
		}
	}
}
