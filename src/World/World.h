#pragma once

#include <glm.hpp>

#include <string>
#include <unordered_map>

class Block;
class Chunk;
class Player;
class RenderMaster;

class World
{
public:
	// TODO: world generation types
	// seed similar to minecraft
	World(int seed, const std::string& world_name);
	~World();

	void update();
	void render();

	// world manipulation
	void setBlockAt(const glm::vec3& position);
	Block* getBlockAt(const glm::vec3& position);
	Chunk* getChunkAt(const glm::vec2& position);

	// player
	// TODO: create set of entity instances to be updated and rendered each frame
	Player* player;

private:
	// unloads chunks that are out of render distance
	void unloadChunks();

	RenderMaster* m_renderMaster;

	std::unordered_map<glm::vec2, Chunk> m_chunks;

	// others
	std::string m_worldName;
	const int m_seed;
	int render_distance;
};