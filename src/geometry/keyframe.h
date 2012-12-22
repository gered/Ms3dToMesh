#ifndef __GEOMETRY_KEYFRAME_H_INCLUDED__
#define __GEOMETRY_KEYFRAME_H_INCLUDED__

#include "../common.h"
#include "vector3.h"

struct Keyframe
{
	Keyframe(uint32_t numJoints);
	virtual ~Keyframe();

	uint32_t numJoints;
	Vector3 *position;
	Vector3 *rotation;

	uint32_t GetSize() const;
};

inline Keyframe::Keyframe(uint32_t numJoints)
{
	this->numJoints = numJoints;
	position = new Vector3[numJoints];
	rotation = new Vector3[numJoints];
}

inline Keyframe::~Keyframe()
{
	SAFE_DELETE_ARRAY(position);
	SAFE_DELETE_ARRAY(rotation);
}

inline uint32_t Keyframe::GetSize() const
{
	uint32_t singleJointFrameSize = 0;

	singleJointFrameSize += sizeof(float) * 3;               // position (xyz)
	singleJointFrameSize += sizeof(float) * 3;               // rotation (xyz)

	uint32_t size = 0;

	size += numJoints * singleJointFrameSize;

	return size;
}

#endif
