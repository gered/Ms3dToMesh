#ifndef __GEOMETRY_TRIANGLE_H_INCLUDED__
#define __GEOMETRY_TRIANGLE_H_INCLUDED__

#include "../common.h"

struct Triangle
{
	uint32_t vertices[3];
	uint32_t groupIndex;

	uint32_t GetSize() const;
};

inline uint32_t Triangle::GetSize() const
{
	uint32_t size = 0;

	size += sizeof(uint32_t) * 3;      // vertices (index)
	size += sizeof(uint32_t);          // group index

	return size;
}

#endif
