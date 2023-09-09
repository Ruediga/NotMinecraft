#pragma once

#include "Chunk.h"

#include <vector>
#include <map>
#include <utility>

class World
{
public:
	World();

	void addChunk(int x, int y);

	void fillExampleChunk(int x, int y);

	Chunk* findChunk(int x, int y);

private:
	// TODO: upgrade to unordered_map
	std::map<std::pair<int, int>, Chunk*> m_loadedChunks;
};