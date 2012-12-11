#ifndef __CHUNKS_VERTICES_H_INCLUDED__
#define __CHUNKS_VERTICES_H_INCLUDED__

#include "../common.h"
#include "../geometry/vector3.h"
#include <vector>

struct VerticesChunk
{
	std::vector<Vector3> vertices;

	uint32_t GetCount() const;
	uint32_t GetSize() const;
};

inline uint32_t VerticesChunk::GetCount() const
{
	return vertices.size();
}

inline uint32_t VerticesChunk::GetSize() const
{
	if (vertices.size() == 0)
		return 0;

	uint32_t verticesSize = sizeof(float) * 3;        // xyz

	uint32_t size = sizeof(uint32_t);  // count
	size += verticesSize * vertices.size();

	return size;
}

#endif
