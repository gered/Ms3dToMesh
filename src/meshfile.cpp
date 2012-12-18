#include "meshfile.h"

#include "animationsequence.h"
#include "ms3d/ms3d.h"
#include "chunks/animations.h"
#include "chunks/chunks.h"
#include "chunks/groups.h"
#include "chunks/joints.h"
#include "chunks/jointtovertices.h"
#include "chunks/keyframes.h"
#include "chunks/normals.h"
#include "chunks/texcoords.h"
#include "chunks/triangles.h"
#include "chunks/vertices.h"
#include "geometry/group.h"
#include "geometry/joint.h"
#include "geometry/jointvertexinfo.h"
#include "geometry/keyframe.h"
#include "geometry/triangle.h"
#include "geometry/vector2.h"
#include "geometry/vector3.h"
#include "geometry/uniquevertex.h"
#include "geometry/uniquevertexcollection.h"
#include <string>
#include <vector>
#include <assert.h>

BOOL ConvertToMeshFile(const std::string &meshFilename, const Ms3d *source, float scaleFactor)
{
	FILE *fp = fopen(meshFilename.c_str(), "wb");
	if (fp == NULL)
		return FALSE;
	
	// collect all unique vertices (position + normal + texcoord) and the 
	// original MS3D file data vertex index each one was originally from based 
	// on the MS3D triangle data. In MS3D the triangle data can give the same
	// vertex index different normals/texcoords based on which triangle the
	// vertex is associated with... this however, is not a VBO-friendly 
	// arrangement of vertex data.
	// later on we can use uniqueVertices to look up the original MS3D vertex
	// indices to find the new vertex index in our new collection to re-do
	// the triangle and joint-to-vertex mappings.
	// (TL;DR - here we make the MS3D vertices+triangles VBO-friendly)
	UniqueVertexCollection uniqueVertices;
	for (uint32_t i = 0; i < source->GetNumTriangles(); ++i)
	{
		const Ms3dTriangle *triangle = &source->GetTriangles()[i];
		
		Vector3 vertex;
		Vector3 normal;
		Vector2 texCoord;
		
		for (int v = 0; v < 3; ++v)
		{
			uint32_t vertexIndex = triangle->vertices[v];
			const Ms3dVertex *originalVertex = &source->GetVertices()[vertexIndex];
			
			vertex = originalVertex->vertex;
			normal = triangle->normals[v];
			texCoord = triangle->texCoords[v];
			
			// attempt to add new unique vertex with this data (if a vertex
			// already exists in uniqueVertices with this same data, this Add
			// call won't add anything new, but will just return the existing
			// index)
			int32_t newIndex = uniqueVertices.Add(vertex, normal, texCoord, vertexIndex);
			assert(newIndex > -1);
			
			// set the joint index as well since it's right here...
			uniqueVertices.GetVertex(newIndex)->joint = originalVertex->jointIndex;
		}
	}
	

	
	// now we start writing out the file

	WriteFileHeader(fp);

	VerticesChunk *vertices = new VerticesChunk();
	for (uint32_t i = 0; i < source->GetNumVertices(); ++i)
	{
		const Ms3dVertex *vertex = &source->GetVertices()[i];

		Vector3 v = vertex->vertex;
		v *= scaleFactor;

		vertices->vertices.push_back(v);
	}
	WriteChunk(vertices, fp);

	NormalsChunk *normals = new NormalsChunk();
	normals->normals.resize(source->GetNumVertices());
	// MS3D normals are stored per-triangle, but we want them to be stored
	// per vertex instead (so if there are 'n' unique vertices in this model
	// then we also want 'n' unique normals).
	// This takes the normals from the MS3D triangles, gets the corresponding
	// vertex index, and then stores the normal in our normals array at the
	// same index location (thereby mapping normals to vertices).
	for (uint32_t i = 0; i < source->GetNumTriangles(); ++i)
	{
		const Ms3dTriangle *triangle = &source->GetTriangles()[i];

		for (int j = 0; j < 3; ++j)
		{
			uint16_t index = triangle->vertices[j];
			Vector3 n = triangle->normals[j];
			normals->normals[index] = n;
		}
	}
	WriteChunk(normals, fp);

	TexCoordsChunk *texCoords = new TexCoordsChunk();
	texCoords->texCoords.resize(source->GetNumVertices());
	// this works the same as the normals above
	for (uint32_t i = 0; i < source->GetNumTriangles(); ++i)
	{
		const Ms3dTriangle *triangle = &source->GetTriangles()[i];

		for (int j = 0; j < 3; ++j)
		{
			uint16_t index = triangle->vertices[j];
			Vector2 t = triangle->texCoords[j];
			texCoords->texCoords[index] = t;
		}
	}

	TrianglesChunk *triangles = new TrianglesChunk();
	for (uint32_t i = 0; i < source->GetNumTriangles(); ++i)
	{
		const Ms3dTriangle *triangle = &source->GetTriangles()[i];

		Triangle t;
		t.vertices[0] = triangle->vertices[0];
		t.vertices[1] = triangle->vertices[1];
		t.vertices[2] = triangle->vertices[2];
		t.groupIndex = triangle->meshIndex;
		t.normals[0] = triangle->normals[0];
		t.normals[1] = triangle->normals[1];
		t.normals[2] = triangle->normals[2];
		t.texCoords[0] = triangle->texCoords[0];
		t.texCoords[1] = triangle->texCoords[1];
		t.texCoords[2] = triangle->texCoords[2];

		triangles->triangles.push_back(t);
	}
	WriteChunk(triangles, fp);

	GroupsChunk *groups = new GroupsChunk();
	for (uint32_t i = 0; i < source->GetNumMeshes(); ++i)
	{
		const Ms3dMesh *mesh = &source->GetMeshes()[i];

		Group g;
		g.name = mesh->name;
		g.numTriangles = mesh->numTriangles;

		groups->groups.push_back(g);
	}
	WriteChunk(groups, fp);

	JointsChunk *joints = new JointsChunk();
	for (uint32_t i = 0; i < source->GetNumJoints(); ++i)
	{
		const Ms3dJoint *joint = &source->GetJoints()[i];

		Joint j;
		j.name = joint->name;
		j.parentJointIndex = source->FindIndexOfJoint(joint->parentName);
		j.position = joint->position * scaleFactor;
		j.rotation = joint->rotation;

		joints->joints.push_back(j);
	}
	WriteChunk(joints, fp);

	JointToVerticesChunk *jointToVertices = new JointToVerticesChunk();
	for (uint32_t i = 0; i < source->GetNumVertices(); ++i)
	{
		const Ms3dVertex *vertex = &source->GetVertices()[i];

		JointVertexInfo jvi;
		jvi.jointIndex = vertex->jointIndex;
		jvi.weight = 1.0f;

		jointToVertices->jointVertexInfo.push_back(jvi);
	}
	WriteChunk(jointToVertices, fp);

	KeyframesChunk *keyframes = new KeyframesChunk(source->GetNumJoints());
	for (int32_t i = 0; i < source->GetNumFrames(); ++i)
	{
		Keyframe *f = keyframes->AddFrame();

		for (uint32_t j = 0; j < source->GetNumJoints(); ++j)
		{
			const Ms3dJoint *joint = &source->GetJoints()[j];
			const Ms3dKeyFrame *position;
			const Ms3dKeyFrame *rotation;

			// In MS3D joint keyframes, some joints could have less frames then
			// others (e.g. if for some animations, some joints don't animate).
			// We would prefer it (to make animation/rendering simpler) to have
			// all joints have the same number of frames. In the event that a
			// joint has less frames then the frame we're at now, we just copy
			// the first frame in this spot. This repeats data unnecessarily,
			// but makes animation/rendering code simpler (no need to check for
			// frame counts on each joint, etc).
			// TODO: is copying frame 0 the best idea here? maybe we should copy
			//       the last frame instead (i.e. joint->numXxxFrames - 1)?
			if (i >= joint->numTranslationFrames)
				position = &joint->translationFrames[0];
			else
				position = &joint->translationFrames[i];
			if (i >= joint->numRotationFrames)
				rotation = &joint->rotationFrames[0];
			else
				rotation = &joint->rotationFrames[i];


			f->position[j] = position->param * scaleFactor;
			f->rotation[j] = rotation->param;
		}
	}
	WriteChunk(keyframes, fp);

	AnimationsChunk *animations = new AnimationsChunk();
	for (int i = 0; i < source->GetNumAnimations(); ++i)
	{
		const Ms3dAnimation *animation = source->GetAnimation(i);

		AnimationSequence a;
		a.name = animation->name;
		a.start = animation->startFrame;
		a.end = animation->endFrame;

		animations->animations.push_back(a);
	}
	WriteChunk(animations, fp);

	return TRUE;
}
