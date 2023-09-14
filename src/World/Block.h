#pragma once

#include <stdint.h>
#include <map>

namespace BlockData
{
	/*
	 * 0 air
	 * 1 grass
	 * 2 dirt
	*/
	constexpr bool isOpaque(uint8_t block) {
		switch (block)
		{
		case 1: {
			return false;
		}
		case 2: {
			return false;
		}
		}
		return 0;
	}

	// faceID, textureID
	std::map<float, float> blocks[] =
	{
		// air
		{},
		{ // grass
			{0.0f, 0.0f},
			{1.0f, 0.0f},
			{2.0f, 0.0f},
			{3.0f, 0.0f},
			{4.0f, 1.0f},
			{5.0f, 2.0f}
		},
		{ // dirt
			{0.0f, 2.0f},
			{1.0f, 2.0f},
			{2.0f, 2.0f},
			{3.0f, 2.0f},
			{4.0f, 2.0f},
			{5.0f, 2.0f}
		}
	};
}