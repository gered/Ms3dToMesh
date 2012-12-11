#ifndef __GEOMETRY_TRIANGLE_H_INCLUDED__
#define __GEOMETRY_TRIANGLE_H_INCLUDED__

#include "../common.h"
#include "vector2.h"
#include "vector3.h"

struct Triangle
{
	uint32_t vertices[3];
	uint32_t groupIndex;
	Vector3 normals[3];
	Vector2 texCoords[3];

	uint32_t GetSize() const;
};

inline uint32_t Triangle::GetSize() const
{
	uint32_t size = 0;

	size += sizeof(uint32_t) * 3;      // vertices (index)
	size += sizeof(uint32_t);          // group index
	size += (sizeof(float) * 3) * 3;   // normals (xyz)
	size += (sizeof(float) * 2) * 3;   // texcoords (uv)

	return size;
}

#endif
