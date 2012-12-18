#ifndef __GEOMETRY_UNIQUEVERTEX_H_INCLUDED__
#define __GEOMETRY_UNIQUEVERTEX_H_INCLUDED__

#include "../common.h"
#include "vector3.h"
#include "vector2.h"

struct UniqueVertex
{
	Vector3 vertex;
	Vector3 normal;
	Vector2 texCoord;
	int32_t originalVertexIndex;
	int32_t joint;
	
	UniqueVertex();
	
	BOOL IsSameAs(const UniqueVertex &other) const;
};

inline UniqueVertex::UniqueVertex()
{
	vertex.x = 0.0f;
	vertex.y = 0.0f;
	vertex.z = 0.0f;
	normal.x = 0.0f;
	normal.y = 0.0f;
	normal.z = 0.0f;
	texCoord.x = 0.0f;
	texCoord.y = 0.0f;
	originalVertexIndex = 0;
	joint = 0;
}

inline BOOL UniqueVertex::IsSameAs(const UniqueVertex &other) const
{
	if (
		this->vertex == other.vertex &&
		this->normal == other.normal &&
		this->texCoord == other.texCoord
		)
		return TRUE;
	else
		return FALSE;
}

#endif
