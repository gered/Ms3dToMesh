#ifndef __CHUNKS_ANIMATIONS_H_INCLUDED__
#define __CHUNKS_ANIMATIONS_H_INCLUDED__

#include "../common.h"
#include "../animationsequence.h"
#include <vector>

struct AnimationsChunk
{
	std::vector<AnimationSequence> animations;

	uint32_t GetCount() const;
	uint32_t GetSize() const;
};

inline uint32_t AnimationsChunk::GetCount() const
{
	return animations.size();
}

inline uint32_t AnimationsChunk::GetSize() const
{
	if (animations.size() == 0)
		return 0;

	uint32_t size = sizeof(uint32_t);
	for (uint32_t i = 0; i < animations.size(); ++i)
	{
		size += animations[i].name.length() + 1;   // include null terminator
		size += sizeof(uint32_t) * 2;              // start + end
	}

	return size;
}

#endif
