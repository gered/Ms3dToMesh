#ifndef __GEOMETRY_UNIQUEVERTEXCOLLECTION_H_INCLUDED__
#define __GEOMETRY_UNIQUEVERTEXCOLLECTION_H_INCLUDED__

#include "../common.h"
#include "vector2.h"
#include "vector3.h"
#include "uniquevertex.h"
#include <vector>

typedef std::vector<UniqueVertex> UniqueVertices;

class UniqueVertexCollection
{
public:
	UniqueVertexCollection();
	virtual ~UniqueVertexCollection();

	int32_t Add(const Vector3 &vertex, const Vector3 &normal, const Vector2 &texCoord, uint32_t originalIndex);
	int32_t Find(const Vector3 &vertex, const Vector3 &normal, const Vector2 &texCoord) const;
	int32_t Find(uint32_t originalIndex) const;
	uint32_t GetCountSharing(uint32_t originalIndex) const;
	
	uint32_t GetCount() const                              { return m_vertices.size(); }
	const UniqueVertex* GetVertex(uint32_t i) const        { return &m_vertices[i]; }
	UniqueVertex* GetVertex(uint32_t i)                    { return &m_vertices[i]; }

private:
	int32_t Find(const UniqueVertex &vertex) const;

	UniqueVertices m_vertices;
};

inline UniqueVertexCollection::UniqueVertexCollection()
{
}

inline UniqueVertexCollection::~UniqueVertexCollection()
{
}

int32_t UniqueVertexCollection::Add(const Vector3 &vertex, const Vector3 &normal, const Vector2 &texCoord, uint32_t originalIndex)
{
	UniqueVertex newVertex;
	newVertex.vertex = vertex;
	newVertex.normal = normal;
	newVertex.texCoord = texCoord;
	newVertex.originalVertexIndex = originalIndex;
	
	int32_t existingIndex = Find(newVertex);
	if (existingIndex > -1)
		return existingIndex;
	
	m_vertices.push_back(newVertex);
	return m_vertices.size() - 1;
}

int32_t UniqueVertexCollection::Find(const Vector3 &vertex, const Vector3 &normal, const Vector2 &texCoord) const
{
	for (int32_t i = 0; i < m_vertices.size(); ++i)
	{
		const UniqueVertex *v = &m_vertices[i];
		if (
			vertex == v->vertex &&
			normal == v->normal &&
			texCoord == v->texCoord
			)
			return i;
	}
	
	return -1;
}

int32_t UniqueVertexCollection::Find(uint32_t originalIndex) const
{
	for (int32_t i = 0; i < m_vertices.size(); ++i)
	{
		if (m_vertices[i].originalVertexIndex == originalIndex)
			return i;
	}
	
	return -1;
}

uint32_t UniqueVertexCollection::GetCountSharing(uint32_t originalIndex) const
{
	uint32_t count = 0;
	
	for (uint32_t i = 0; i < m_vertices.size(); ++i)
	{
		if (m_vertices[i].originalVertexIndex == originalIndex)
			++count;
	}
	
	return count;
}

int32_t UniqueVertexCollection::Find(const UniqueVertex &vertex) const
{
	for (int32_t i = 0; i < m_vertices.size(); ++i)
	{
		if (vertex.IsSameAs(m_vertices[i]))
			return i;
	}
	
	return -1;
}

#endif
