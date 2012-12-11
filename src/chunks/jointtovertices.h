#ifndef __CHUNKS_JOINTTOVERTICES_H_INCLUDED__
#define __CHUNKS_JOINTTOVERTICES_H_INCLUDED__

#include "../common.h"
#include "../geometry/jointvertexinfo.h"
#include <vector>

struct JointToVerticesChunk
{
	std::vector<JointVertexInfo> jointVertexInfo;

	uint32_t GetCount() const;
	uint32_t GetSize() const;
};

inline uint32_t JointToVerticesChunk::GetCount() const
{
	return jointVertexInfo.size();
}

inline uint32_t JointToVerticesChunk::GetSize() const
{
	if (jointVertexInfo.size() == 0)
		return 0;

	uint32_t size = sizeof(uint32_t);  // count

	for (uint32_t i = 0; i < jointVertexInfo.size(); ++i)
	{
		const JointVertexInfo *info = &jointVertexInfo[i];
		size += info->GetSize();
	}

	return size;
}

#endif
