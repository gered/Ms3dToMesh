#ifndef __GEOMETRY_JOINT_H_INCLUDED__
#define __GEOMETRY_JOINT_H_INCLUDED__

#include "../common.h"
#include "vector3.h"
#include <string.h>

struct Joint
{
	std::string name;
	int32_t parentJointIndex;     // -1 = no parent
	Vector3 position;
	Vector3 rotation;

	uint32_t GetSize() const;
};

inline uint32_t Joint::GetSize() const
{
	uint32_t size = 0;

	size += sizeof(char) * (name.size() + 1);       // name string (including null-terminator)
	size += sizeof(int32_t);                        // parent index
	size += sizeof(float) * 3;                      // position
	size += sizeof(float) * 3;                      // rotation

	return size;
}

#endif
