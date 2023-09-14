#pragma once

#include <glm/glm.hpp>

#include <stdint.h>
#include <vector>
#include <map>

namespace ChunkData
{
	constexpr int CHUNK_SIZE_X = 16;
	constexpr int CHUNK_SIZE_Y = 64;
	constexpr int CHUNK_SIZE_Z = 16;
	constexpr int CHUNK_VOLUME = CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z;
}

class Chunk
{
public:
	Chunk(int x, int y);

	void setBlock(glm::uvec3 pos, uint8_t block);
	void setBlock(int x, int y, int z, uint8_t block);
	//uint8_t getBlock(glm::uvec3 pos);
	uint8_t getBlock(int x, int y, int z);

	void printChunk();

	// rendering and meshing
	unsigned int VAO, VBO;
	std::vector<float> meshData;
	void mesh();
	void meshOld();
	void sendDataToGPU();
	void updateRefs(std::map<std::pair<int, int>, Chunk*>& m_loadedChunks);

private:
	// keep a ref to the surrounding chunks
	Chunk* chunk_front = nullptr;
	Chunk* chunk_back = nullptr;
	Chunk* chunk_left = nullptr;
	Chunk* chunk_right = nullptr;

	int m_x, m_z;
	uint8_t m_chunk_array[ChunkData::CHUNK_VOLUME]{ 0 };
};