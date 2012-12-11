#ifndef __CHUNKS_TRIANGLES_H_INCLUDED__
#define __CHUNKS_TRIANGLES_H_INCLUDED__

#include "../common.h"
#include "../geometry/triangle.h"
#include <vector>

struct TrianglesChunk
{
	std::vector<Triangle> triangles;

	uint32_t GetCount() const;
	uint32_t GetSize() const;
};

inline uint32_t TrianglesChunk::GetCount() const
{
	return triangles.size();
}

inline uint32_t TrianglesChunk::GetSize() const
{
	if (triangles.size() == 0)
		return 0;

	uint32_t size = sizeof(uint32_t);  // count

	for (uint32_t i = 0; i < triangles.size(); ++i)
	{
		const Triangle *triangle = &triangles[i];
		size += triangle->GetSize();
	}

	return size;
}

#endif
