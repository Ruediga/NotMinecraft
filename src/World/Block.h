#pragma once

// for uint8_t
#include <iostream>

struct Block
{
public:
	enum class BlockType : std::uint8_t
	{
		type_unkown = 0,
		grass_block = 1,
		dirt_block = 2,
		cobblestone = 3,
		stone = 4,
		oak_log = 5,
		oak_leaves = 6
	};

	Block();
	Block(BlockType block_type);

	BlockType p_block_type = BlockType::type_unkown;

	void render();
};