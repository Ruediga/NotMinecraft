#include "Chunk.h"
#include "Block.h"

#include <iostream>
#include <sstream>
#include <bitset>

#include <glad/glad.h>

Chunk::Chunk(int x, int y)
	: m_x{ x }, m_z{ y }, m_chunk_array{ 0 }
{

}

void Chunk::setBlock(glm::uvec3 pos, uint8_t block)
{
	m_chunk_array[pos.x + pos.z * ChunkData::CHUNK_SIZE_X + pos.y * ChunkData::CHUNK_SIZE_X * ChunkData::CHUNK_SIZE_Z] = block;
}

void Chunk::setBlock(int x, int y, int z, uint8_t block)
{
	m_chunk_array[x + z * ChunkData::CHUNK_SIZE_X + y * ChunkData::CHUNK_SIZE_X * ChunkData::CHUNK_SIZE_Z] = block;
}

/* fix
uint8_t Chunk::getBlock(glm::uvec3 pos)
{
	return m_chunk_array[pos.x + pos.z * ChunkData::CHUNK_SIZE_X + pos.y * ChunkData::CHUNK_SIZE_X * ChunkData::CHUNK_SIZE_Z];
}
*/

uint8_t Chunk::getBlock(int x, int y, int z)
{
	// if block out of range
	// right
	if (x >= ChunkData::CHUNK_SIZE_X) {
		if (chunk_right) {
			return chunk_right->getBlock(ChunkData::CHUNK_SIZE_X - 1, y, z);
		}
		else return 0;
	}
	// left
	else if (x < 0) {
		if (chunk_left) {
			return chunk_left->getBlock(0, y, z);
		}
		else return 0;
	}
	// front
	else if (z >= ChunkData::CHUNK_SIZE_Z) {
		if (chunk_front) {
			return chunk_front->getBlock(x, y, ChunkData::CHUNK_SIZE_Z - 1);
		}
		else return 0;
	}
	// back
	else if (z < 0) {
		if (chunk_back) {
			return chunk_back->getBlock(x, y, 0);
		}
		else return 0;
	}
	else if (y < 0) {
		return 0;
	}
	else if (y >= ChunkData::CHUNK_SIZE_Y) {
		return 0;
	}
	return m_chunk_array[x + z * ChunkData::CHUNK_SIZE_X + y * ChunkData::CHUNK_SIZE_X * ChunkData::CHUNK_SIZE_Z];
}

void Chunk::printChunk()
{
	for (int i = 0; i < 2000; i++) {
		uint8_t blockData = m_chunk_array[i];
		std::bitset<8> binary(blockData); // blockData to binary string
		std::cout << binary << "\n";
	}
}

void Chunk::mesh()
{
	meshData.erase(meshData.begin(), meshData.end());
	for (float z = 0; z < ChunkData::CHUNK_SIZE_Z; z++)
	{
		for (float y = 0; y < ChunkData::CHUNK_SIZE_Y; y++)
		{
			for (float x = 0; x < ChunkData::CHUNK_SIZE_X; x++)
			{
				int block = getBlock(x, y, z);
				float xc = x + m_x * ChunkData::CHUNK_SIZE_X;
				float zc = z + m_z * ChunkData::CHUNK_SIZE_Z;

				if (getBlock(x - 1, y, z) == 0) {
					for (float vID = 0.0f; vID < 6.0f; vID++) {
						float faceID = 2;
						meshData.push_back(xc);
						meshData.push_back(y);
						meshData.push_back(zc);
						// face ID
						meshData.push_back(2);
						meshData.push_back(vID);
						meshData.push_back(BlockData::blocks[block][faceID]);
					}
				}
				if (getBlock(x + 1, y, z) == 0) {
					for (float vID = 0.0f; vID < 6.0f; vID++) {
						float faceID = 3;
						meshData.push_back(xc);
						meshData.push_back(y);
						meshData.push_back(zc);
						// face ID
						meshData.push_back(faceID);
						meshData.push_back(vID);
						meshData.push_back(BlockData::blocks[block][faceID]);
					}
				}
				if (getBlock(x, y + 1, z) == 0) {
					for (float vID = 0.0f; vID < 6.0f; vID++) {
						float faceID = 4;
						meshData.push_back(xc);
						meshData.push_back(y);
						meshData.push_back(zc);
						// face ID
						meshData.push_back(faceID);
						meshData.push_back(vID);
						meshData.push_back(BlockData::blocks[block][faceID]);
					}
				}
				if (getBlock(x, y - 1, z) == 0) {
					for (float vID = 0.0f; vID < 6.0f; vID++) {
						float faceID = 5;
						meshData.push_back(xc);
						meshData.push_back(y);
						meshData.push_back(zc);
						// face ID
						meshData.push_back(faceID);
						meshData.push_back(vID);
						meshData.push_back(BlockData::blocks[block][faceID]);
					}
				}
				if (getBlock(x, y, z - 1) == 0) {
					for (float vID = 0.0f; vID < 6.0f; vID++) {
						float faceID = 0;
						meshData.push_back(xc);
						meshData.push_back(y);
						meshData.push_back(zc);
						// face ID
						meshData.push_back(faceID);
						meshData.push_back(vID);
						meshData.push_back(BlockData::blocks[block][faceID]);
					}
				}
				if (getBlock(x, y, z + 1) == 0) {
					for (float vID = 0.0f; vID < 6.0f; vID++) {
						float faceID = 1;
						meshData.push_back(xc);
						meshData.push_back(y);
						meshData.push_back(zc);
						// face ID
						meshData.push_back(faceID);
						meshData.push_back(vID);
						meshData.push_back(BlockData::blocks[block][faceID]);
					}
				}
			}
		}
	}
}

void Chunk::meshOld()
{
	for (float z = 0; z < ChunkData::CHUNK_SIZE_Z; z++)
	{
		for (float y = 0; y < ChunkData::CHUNK_SIZE_Y; y++)
		{
			for (float x = 0; x < ChunkData::CHUNK_SIZE_X; x++)
			{
				for (float face = 0; face < 7.0f; face++)
				{
					for (float vID = 0.0f; vID < 6.0f; vID++) {
						meshData.push_back(x);
						meshData.push_back(y);
						meshData.push_back(z);
						// face ID
						meshData.push_back(face);
						meshData.push_back(vID);
						if (face == 4)
							meshData.push_back(1);
						else if (face == 5)
							meshData.push_back(2);
						else
							meshData.push_back(0);
					}
				}
			}
		}
	}
}

void Chunk::sendDataToGPU()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, meshData.size() * sizeof(float), &meshData[0], GL_STATIC_DRAW);

	/// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// FaceID
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// VertexID
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(4 * sizeof(float)));
	glEnableVertexAttribArray(2);
	// TextureID
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(3);
}

void Chunk::updateRefs(std::map<std::pair<int, int>, Chunk*>& loadedChunks)
{
	// Check if the chunk exists
	if (loadedChunks.find({ m_x, m_z + 1 }) != loadedChunks.end()) {
		chunk_front = loadedChunks[{m_x, m_z + 1}];
	}
	if (loadedChunks.find({ m_x, m_z - 1 }) != loadedChunks.end()) {
		chunk_back = loadedChunks[{m_x, m_z - 1}];
	}
	if (loadedChunks.find({ m_x + 1, m_z }) != loadedChunks.end()) {
		chunk_right = loadedChunks[{m_x + 1, m_z}];
	}
	if (loadedChunks.find({ m_x - 1, m_z }) != loadedChunks.end()) {
		chunk_left = loadedChunks[{m_x - 1, m_z}];
	}
}
