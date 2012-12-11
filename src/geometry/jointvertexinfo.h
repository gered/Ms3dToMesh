#ifndef __GEOMETRY_JOINTVERTEXINFO_H_INCLUDED__
#define __GEOMETRY_JOINTVERTEXINFO_H_INCLUDED__

#include "../common.h"

struct JointVertexInfo
{
	uint32_t jointIndex;
	float weight;

	uint32_t GetSize() const;
};

inline uint32_t JointVertexInfo::GetSize() const
{
	uint32_t size = 0;

	size += sizeof(uint32_t);                // joint index
	size += sizeof(float);                   // weight

	return size;
}

#endif
