#ifndef __GEOMETRY_GROUP_H_INCLUDED__
#define __GEOMETRY_GROUP_H_INCLUDED__

#include "../common.h"
#include <string>

struct Group
{
	std::string name;
	std::string texture;
	uint8_t alpha;
	uint32_t numTriangles;

	uint32_t GetSize() const;
};

inline uint32_t Group::GetSize() const
{
	uint32_t size = 0;

	size += sizeof(char) * (name.size() + 1);       // name string (including null-terminator)
	size += sizeof(char) * (texture.size() + 1);    // texture file (including null-terminator)
	size += sizeof(uint8_t);                        // alpha flag (boolean)
	size += sizeof(uint32_t);                       // number of triangles

	return size;
}

#endif
