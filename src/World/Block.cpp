#include "Block.h"

Block::Block()
	: p_block_type{ BlockType::type_unkown }
{
}

Block::Block(BlockType block_type)
	: p_block_type{ block_type }
{
}

void Block::render()
{

}
