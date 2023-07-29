#include "World.h"

World::World(int seed, const std::string& world_name)
	:
	m_seed{ seed },
	m_worldName{ world_name }
{
	// player = new Player();


}

World::~World()
{
}

void World::update()
{
}

void World::render()
{
}

void World::setBlockAt(const glm::vec3& position)
{
}

Block* World::getBlockAt(const glm::vec3& position)
{
	return nullptr;
}

Chunk* World::getChunkAt(const glm::vec2& position)
{
	return nullptr;
}

void World::unloadChunks()
{
}
