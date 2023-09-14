#include "World.h"

#include <iostream>

World::World()
	: m_loadedChunks{}, shader{ new Shader("src/Shaders/simpleCubeVertexShader.glsl", "src/Shaders/simpleCubeFragmentShader.glsl") }
{
	// create a default sized world (16 x 16)
	for (int x = -7; x < 9; x++) {
		for (int z = -7; z < 9; z++) {
			addChunk(x, z);
		}
	}
	
	for (Chunk* chunk : chunk_vec)
		fillChunk(chunk);

	for (Chunk* chunk : chunk_vec) {
		chunk->updateRefs(m_loadedChunks);
		chunk->mesh();
		chunk->sendDataToGPU();
	}
}

void World::addChunk(int x, int z)
{
	// Check if the chunk already exists
	if (m_loadedChunks.find({ x, z }) == m_loadedChunks.end())
	{
		Chunk* chunk = new Chunk(x, z);
		m_loadedChunks[{x, z}] = chunk;
		chunk_vec.push_back(chunk);
	}
	else
	{
		std::cerr << "Chunk at " << x << ", " << z << " already exists\n";
	}
}

void World::fillChunk(Chunk* chunk)
{
	for (int z = 0; z < ChunkData::CHUNK_SIZE_Z; z++)
	{
		for (int y = 0; y < ChunkData::CHUNK_SIZE_Y; y++)
		{
			for (int x = 0; x < ChunkData::CHUNK_SIZE_X; x++)
			{
				if (y == (ChunkData::CHUNK_SIZE_Y - 1))
					chunk->setBlock(x, y, z, 1);
				else
					chunk->setBlock(x, y, z, 2);
			}
		}
	}
}

uint8_t World::findBlock(int x, int y, int z)
{
	int chunk_x = x / ChunkData::CHUNK_SIZE_X;
	int chunk_z = z / ChunkData::CHUNK_SIZE_Z;

	int block_x = x % ChunkData::CHUNK_SIZE_X;
	int block_y = y % ChunkData::CHUNK_SIZE_Y;
	int block_z = z % ChunkData::CHUNK_SIZE_Z;

	Chunk* chunk = findChunk(chunk_x, chunk_z);
	if (chunk)
		return chunk->getBlock(block_x, block_y, block_z);
	return 0;
}

Chunk* World::findChunk(int x, int z)
{
	// Check if the chunk exists
	if (m_loadedChunks.find({ x, z }) != m_loadedChunks.end())
	{
		return m_loadedChunks[{x, z}];
	}
	else
		std::cerr << "Chunk at x: " << x << ", z: " << z << " does not exist";
	return nullptr;
}

void World::breakBlock(int x, int y, int z)
{
	int chunk_x = x / ChunkData::CHUNK_SIZE_X;
	int chunk_z = z / ChunkData::CHUNK_SIZE_Z;

	int block_x = x % ChunkData::CHUNK_SIZE_X;
	int block_y = y % ChunkData::CHUNK_SIZE_Y;
	int block_z = z % ChunkData::CHUNK_SIZE_Z;

	Chunk* chunk = findChunk(chunk_x, chunk_z);
	if (chunk) {
		chunk->setBlock(block_x, block_y, block_z, 0);
		chunk->mesh();
		chunk->sendDataToGPU();
	}
}

glm::vec3 World::castRay(const glm::vec3& camera_pos, const glm::vec3& direction)
{
	// ray length
	float length = 5.0f;
	// step accuracy
	float accuracy = 0.025f;

	glm::vec3 currentPos = camera_pos;

	for (int i = 0; i < length / accuracy; i++) {
		if (findBlock((int)currentPos.x, (int)currentPos.y, (int)currentPos.z) != 0) {
			return glm::vec3((int)currentPos.x, (int)currentPos.y, (int)currentPos.z);
		}
		currentPos += accuracy * direction;
	}
	return {};
}
