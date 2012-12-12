#ifndef __MS3D_H_INCLUDED__
#define __MS3D_H_INCLUDED__

#include "common.h"
#include "../geometry/vector3.h"
#include "../geometry/vector2.h"
#include <string>
#include <vector>

struct Ms3dHeader
{
	char id[10];
	int32_t version;
};

struct Ms3dVertex
{
	uint8_t editorFlags;
	Vector3 vertex;
	int8_t jointIndex;
	uint8_t unused;
};

struct Ms3dTriangle
{
	uint16_t editorFlags;
	uint16_t vertices[3];
	Vector3 normals[3];
	Vector2 texCoords[3];
	uint8_t smoothingGroup;
	uint8_t meshIndex;
};

struct Ms3dMesh
{
	uint8_t editorFlags;
	std::string name;
	uint16_t numTriangles;
	uint16_t *triangles;
	int8_t materialIndex;

	Ms3dMesh()
	{
		triangles = NULL;
	}

	~Ms3dMesh()
	{
		SAFE_DELETE_ARRAY(triangles);
	}
};

struct Ms3dMaterial
{
	std::string name;
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float emissive[4];
	float shininess;
	float transparency;
	int8_t mode;
	std::string texture;
	std::string alpha;
};

struct Ms3dKeyFrame
{
	float time;
	Vector3 param;
};

struct Ms3dJoint
{
	uint8_t editorFlags;
	std::string name;
	std::string parentName;
	Vector3 rotation;
	Vector3 position;
	uint16_t numRotationFrames;
	uint16_t numTranslationFrames;
	Ms3dKeyFrame *rotationFrames;
	Ms3dKeyFrame *translationFrames;

	Ms3dJoint()
	{
		rotationFrames = NULL;
		translationFrames = NULL;
	}

	~Ms3dJoint()
	{
		SAFE_DELETE_ARRAY(rotationFrames);
		SAFE_DELETE_ARRAY(translationFrames);
	}
};

struct Ms3dAnimation
{
	std::string name;
	uint32_t startFrame;
	uint32_t endFrame;
};

class Ms3d
{
public:
	Ms3d();
	virtual ~Ms3d()                                        { Release(); }

	void Release();
	BOOL Load(const std::string &file);

	uint16_t GetNumVertices() const                        { return m_numVertices; }
	uint16_t GetNumTriangles() const                       { return m_numTriangles; }
	uint16_t GetNumMeshes() const                          { return m_numMeshes; }
	uint16_t GetNumMaterials() const                       { return m_numMaterials; }
	uint16_t GetNumJoints() const                          { return m_numJoints; }
	uint32_t GetNumAnimations() const                      { return m_animations.size(); }
	float GetAnimationFps() const                          { return m_animationFps; }
	uint32_t GetNumFrames() const                          { return m_numFrames; }
	Ms3dVertex* GetVertices() const                        { return m_vertices; }
	Ms3dTriangle* GetTriangles() const                     { return m_triangles; }
	Ms3dMesh* GetMeshes() const                            { return m_meshes; }
	Ms3dMaterial* GetMaterials() const                     { return m_materials; }
	Ms3dJoint* GetJoints() const                           { return m_joints; }
	const Ms3dAnimation* GetAnimation(int index) const     { return &m_animations[index]; }

	int32_t FindIndexOfJoint(const std::string &jointName) const;

private:

	uint16_t m_numVertices;
	uint16_t m_numTriangles;
	uint16_t m_numMeshes;
	uint16_t m_numMaterials;
	uint16_t m_numJoints;
	float m_animationFps;
	float m_editorAnimationTime;
	uint32_t m_numFrames;
	Ms3dVertex *m_vertices;
	Ms3dTriangle *m_triangles;
	Ms3dMesh *m_meshes;
	Ms3dMaterial *m_materials;
	Ms3dJoint *m_joints;
	std::vector<Ms3dAnimation> m_animations;
};

#endif
