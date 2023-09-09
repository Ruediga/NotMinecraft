#include "World.h"

#include <iostream>

World::World()
	: m_loadedChunks{}
{

}

void World::addChunk(int x, int y)
{
	// Check if the chunk already exists
	if (m_loadedChunks.find({ x, y }) == m_loadedChunks.end())
	{
		m_loadedChunks[{x, y}] = new Chunk(x, y);
	}
	else
	{
		std::cerr << "Chunk at " << x << ", " << y << " already exists\n";
	}
}

void World::fillExampleChunk(int x_, int y_)
{
	if (m_loadedChunks.find({ x_, y_ }) != m_loadedChunks.end())
	{
		for (int z = 0; z < 16; z++)
		{
			for (int y = 0; y < 128; y++)
			{
				for (int x = 0; x < 16; x++)
				{
					m_loadedChunks[{x_, y_}]->setBlock(x, y, z, 5);
				}
			}
		}
	}
	else
	{
		std::cerr << "Chunk at " << x_ << ", " << y_ << " does not exist\n";
	}
}

Chunk* World::findChunk(int x, int y)
{
	// Check if the chunk exists
	if (m_loadedChunks.find({ x, y }) != m_loadedChunks.end())
	{
		return m_loadedChunks[{x, y}];
	}
	else return nullptr;
}
