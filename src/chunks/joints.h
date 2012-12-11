#ifndef __CHUNKS_JOINTS_H_INCLUDED__
#define __CHUNKS_JOINTS_H_INCLUDED__

#include "../common.h"
#include "../geometry/joint.h"
#include <vector>

struct JointsChunk
{
	std::vector<Joint> joints;

	uint32_t GetCount() const;
	uint32_t GetSize() const;
};

inline uint32_t JointsChunk::GetCount() const
{
	return joints.size();
}

inline uint32_t JointsChunk::GetSize() const
{
	if (joints.size() == 0)
		return 0;

	uint32_t size = sizeof(uint32_t);  // count

	for (uint32_t i = 0; i < joints.size(); ++i)
	{
		const Joint *joint = &joints[i];
		size += joint->GetSize();
	}

	return size;
}

#endif
