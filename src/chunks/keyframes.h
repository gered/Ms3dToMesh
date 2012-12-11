#ifndef __CHUNKS_KEYFRAMES_H_INCLUDED__
#define __CHUNKS_KEYFRAMES_H_INCLUDED__

#include "../common.h"
#include "../geometry/keyframe.h"
#include <vector>

struct KeyframesChunk
{
	KeyframesChunk(uint32_t numJointsPerFrame);
	virtual ~KeyframesChunk();

	uint32_t numJointsPerFrame;
	std::vector<Keyframe*> frames;

	Keyframe* AddFrame();

	uint32_t GetCount() const;
	uint32_t GetSize() const;
};

inline KeyframesChunk::KeyframesChunk(uint32_t numJointsPerFrame)
{
	this->numJointsPerFrame = numJointsPerFrame;
}

inline KeyframesChunk::~KeyframesChunk()
{
	for (uint32_t i = 0; i < frames.size(); ++i)
	{
		Keyframe *frame = frames[i];
		SAFE_DELETE(frame);
	}
}

inline Keyframe* KeyframesChunk::AddFrame()
{
	Keyframe *newFrame = new Keyframe(numJointsPerFrame);
	frames.push_back(newFrame);
	return newFrame;
}

inline uint32_t KeyframesChunk::GetCount() const
{
	return frames.size();
}

inline uint32_t KeyframesChunk::GetSize() const
{
	if (frames.size() == 0)
		return 0;

	uint32_t size = sizeof(uint32_t);  // count

	for (uint32_t i = 0; i < frames.size(); ++i)
	{
		Keyframe *frame = frames[i];
		size += frame->GetSize();
	}

	return size;
}


#endif
