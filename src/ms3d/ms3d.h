#ifndef __MS3D_H_INCLUDED__
#define __MS3D_H_INCLUDED__

#include <string>
#include "../geometry/vector3.h"
#include "../geometry/vector2.h"
#include <vector>

struct Ms3dHeader
{
	char id[10];
	long version;
};

struct Ms3dVertex
{
	unsigned char editorFlags;
	Vector3 vertex;
	char jointIndex;
	unsigned char unused;
};

struct Ms3dTriangle
{
	unsigned short editorFlags;
	unsigned short vertices[3];
	Vector3 normals[3];
	Vector2 texCoords[3];
	unsigned char smoothingGroup;
	unsigned char meshIndex;
};

struct Ms3dMesh
{
	unsigned char editorFlags;
	std::string name;
	unsigned short numTriangles;
	unsigned short *triangles;
	char materialIndex;

	Ms3dMesh()
	{
		triangles = NULL;
	}

	~Ms3dMesh()
	{
		delete[] triangles;
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
	char mode;
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
	unsigned char editorFlags;
	std::string name;
	std::string parentName;
	Vector3 rotation;
	Vector3 position;
	unsigned short numRotationFrames;
	unsigned short numTranslationFrames;
	Ms3dKeyFrame *rotationFrames;
	Ms3dKeyFrame *translationFrames;

	Ms3dJoint()
	{
		rotationFrames = NULL;
		translationFrames = NULL;
	}

	~Ms3dJoint()
	{
		delete[] rotationFrames;
		delete[] translationFrames;
	}
};

struct Ms3dAnimation
{
	std::string name;
	unsigned int startFrame;
	unsigned int endFrame;
};

class Ms3d
{
public:
	Ms3d();
	virtual ~Ms3d()                                        { Release(); }

	void Release();
	bool Load(const std::string &file);
	bool ConvertToMesh(const std::string &file, float scaleFactor);

	unsigned short GetNumVertices() const                  { return m_numVertices; }
	unsigned short GetNumTriangles() const                 { return m_numTriangles; }
	unsigned short GetNumMeshes() const                    { return m_numMeshes; }
	unsigned short GetNumMaterials() const                 { return m_numMaterials; }
	unsigned short GetNumJoints() const                    { return m_numJoints; }
	int GetNumAnimations() const                           { return m_animations.size(); }
	float GetAnimationFps() const                          { return m_animationFps; }
	int GetNumFrames() const                               { return m_numFrames; }
	Ms3dVertex* GetVertices() const                        { return m_vertices; }
	Ms3dTriangle* GetTriangles() const                     { return m_triangles; }
	Ms3dMesh* GetMeshes() const                            { return m_meshes; }
	Ms3dMaterial* GetMaterials() const                     { return m_materials; }
	Ms3dJoint* GetJoints() const                           { return m_joints; }
	const Ms3dAnimation* GetAnimation(int index) const     { return &m_animations[index]; }

	int FindIndexOfJoint(const std::string &jointName) const;

private:

	unsigned short m_numVertices;
	unsigned short m_numTriangles;
	unsigned short m_numMeshes;
	unsigned short m_numMaterials;
	unsigned short m_numJoints;
	float m_animationFps;
	float m_editorAnimationTime;
	int m_numFrames;
	Ms3dVertex *m_vertices;
	Ms3dTriangle *m_triangles;
	Ms3dMesh *m_meshes;
	Ms3dMaterial *m_materials;
	Ms3dJoint *m_joints;
	std::vector<Ms3dAnimation> m_animations;
};

#endif
