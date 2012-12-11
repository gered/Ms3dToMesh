#ifndef __CHUNKS_NORMALS_H_INCLUDED__
#define __CHUNKS_NORMALS_H_INCLUDED__

#include "../common.h"
#include "../geometry/vector3.h"
#include <vector>

struct NormalsChunk
{
	std::vector<Vector3> normals;

	uint32_t GetCount() const;
	uint32_t GetSize() const;
};

inline uint32_t NormalsChunk::GetCount() const
{
	return normals.size();
}

inline uint32_t NormalsChunk::GetSize() const
{
	if (normals.size() == 0)
		return 0;

	uint32_t normalsSize = sizeof(float) * 3;        // xyz

	uint32_t size = sizeof(uint32_t);  // count
	size += normalsSize * normals.size();

	return size;
}

#endif
