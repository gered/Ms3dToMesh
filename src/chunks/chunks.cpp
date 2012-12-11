#include "chunks.h"

#include "vertices.h"
#include "normals.h"
#include "texcoords.h"
#include "triangles.h"
#include "groups.h"
#include "joints.h"
#include "jointtovertices.h"
#include "keyframes.h"
#include "animations.h"
#include "../assets/animationsequence.h"
#include "../geometry/group.h"
#include "../geometry/joint.h"
#include "../geometry/jointvertexinfo.h"
#include "../geometry/keyframe.h"
#include "../geometry/triangle.h"
#include "../geometry/vector2.h"
#include "../geometry/vector3.h"

void WriteFileHeader(FILE *fp)
{
	fputs("MESH", fp);
	uint8_t version = 1;
	fwrite(&version, 1, 1, fp);
}

void WriteChunk(VerticesChunk *chunk, FILE *fp)
{
	uint32_t size = chunk->GetSize();
	if (size == 0)
		return;

	fputs("VTX", fp);
	fwrite(&size, sizeof(uint32_t), 1, fp);
	uint32_t count = chunk->GetCount();
	fwrite(&count, sizeof(uint32_t), 1, fp);

	for (uint32_t i = 0; i < count; ++i)
	{
		const Vector3 *vertex = &chunk->vertices[i];

		fwrite(&vertex->x, sizeof(float), 1, fp);
		fwrite(&vertex->y, sizeof(float), 1, fp);
		fwrite(&vertex->z, sizeof(float), 1, fp);
	}
}

void WriteChunk(NormalsChunk *chunk, FILE *fp)
{
	uint32_t size = chunk->GetSize();
	if (size == 0)
		return;

	fputs("NRL", fp);
	fwrite(&size, sizeof(uint32_t), 1, fp);
	uint32_t count = chunk->GetCount();
	fwrite(&count, sizeof(uint32_t), 1, fp);

	for (uint32_t i = 0; i < count; ++i)
	{
		const Vector3 *normal = &chunk->normals[i];

		fwrite(&normal->x, sizeof(float), 1, fp);
		fwrite(&normal->y, sizeof(float), 1, fp);
		fwrite(&normal->z, sizeof(float), 1, fp);
	}
}

void WriteChunk(TexCoordsChunk *chunk, FILE *fp)
{
	uint32_t size = chunk->GetSize();
	if (size == 0)
		return;

	fputs("TXT", fp);
	fwrite(&size, sizeof(uint32_t), 1, fp);
	uint32_t count = chunk->GetCount();
	fwrite(&count, sizeof(uint32_t), 1, fp);

	for (uint32_t i = 0; i < count; ++i)
	{
		const Vector2 *texCoord = &chunk->texCoords[i];

		fwrite(&texCoord->x, sizeof(float), 1, fp);
		fwrite(&texCoord->y, sizeof(float), 1, fp);
	}
}

void WriteChunk(TrianglesChunk *chunk, FILE *fp)
{
	uint32_t size = chunk->GetSize();
	if (size == 0)
		return;

	fputs("TRI", fp);
	fwrite(&size, sizeof(uint32_t), 1, fp);
	uint32_t count = chunk->GetCount();
	fwrite(&count, sizeof(uint32_t), 1, fp);

	for (uint32_t i = 0; i < count; ++i)
	{
		const Triangle *triangle = &chunk->triangles[i];

		fwrite(&triangle->vertices[0], sizeof(uint32_t), 1, fp);
		fwrite(&triangle->vertices[1], sizeof(uint32_t), 1, fp);
		fwrite(&triangle->vertices[2], sizeof(uint32_t), 1, fp);

		fwrite(&triangle->groupIndex, sizeof(uint32_t), 1, fp);

		for (int j = 0; j < 3; ++j)
		{
			fwrite(&triangle->normals[j].x, sizeof(float), 1, fp);
			fwrite(&triangle->normals[j].y, sizeof(float), 1, fp);
			fwrite(&triangle->normals[j].z, sizeof(float), 1, fp);
		}
		for (int j = 0; j < 3; ++j)
		{
			fwrite(&triangle->texCoords[j].x, sizeof(float), 1, fp);
			fwrite(&triangle->texCoords[j].y, sizeof(float), 1, fp);
		}
	}
}

void WriteChunk(GroupsChunk *chunk, FILE *fp)
{
	uint32_t size = chunk->GetSize();
	if (size == 0)
		return;

	fputs("GRP", fp);
	fwrite(&size, sizeof(uint32_t), 1, fp);
	uint32_t count = chunk->GetCount();
	fwrite(&count, sizeof(uint32_t), 1, fp);

	for (uint32_t i = 0; i < count; ++i)
	{
		const Group *group = &chunk->groups[i];

		fwrite(group->name.c_str(), group->name.size(), 1, fp);
		char c = '\0';
		fwrite(&c, 1, 1, fp);
		
		fwrite(&group->numTriangles, sizeof(uint32_t), 1, fp);
	}
}

void WriteChunk(JointsChunk *chunk, FILE *fp)
{
	uint32_t size = chunk->GetSize();
	if (size == 0)
		return;

	fputs("JNT", fp);
	fwrite(&size, sizeof(uint32_t), 1, fp);
	uint32_t count = chunk->GetCount();
	fwrite(&count, sizeof(uint32_t), 1, fp);

	for (uint32_t i = 0; i < count; ++i)
	{
		const Joint *joint = &chunk->joints[i];

		fwrite(joint->name.c_str(), joint->name.size(), 1, fp);
		char c = '\0';
		fwrite(&c, 1, 1, fp);

		fwrite(&joint->parentJointIndex, sizeof(int32_t), 1, fp);

		fwrite(&joint->position.x, sizeof(float), 1, fp);
		fwrite(&joint->position.y, sizeof(float), 1, fp);
		fwrite(&joint->position.z, sizeof(float), 1, fp);

		fwrite(&joint->rotation.x, sizeof(float), 1, fp);
		fwrite(&joint->rotation.y, sizeof(float), 1, fp);
		fwrite(&joint->rotation.z, sizeof(float), 1, fp);
	}
}

void WriteChunk(JointToVerticesChunk *chunk, FILE *fp)
{
	uint32_t size = chunk->GetSize();
	if (size == 0)
		return;

	fputs("JNT", fp);
	fwrite(&size, sizeof(uint32_t), 1, fp);
	uint32_t count = chunk->GetCount();
	fwrite(&count, sizeof(uint32_t), 1, fp);

	for (uint32_t i = 0; i < count; ++i)
	{
		const JointVertexInfo *jointVertexInfo = &chunk->jointVertexInfo[i];

		fwrite(&jointVertexInfo->jointIndex, sizeof(uint32_t), 1, fp);
		fwrite(&jointVertexInfo->weight, sizeof(float), 1, fp);
	}
}

void WriteChunk(KeyframesChunk *chunk, FILE *fp)
{
	uint32_t size = chunk->GetSize();
	if (size == 0)
		return;

	fputs("JKF", fp);
	fwrite(&size, sizeof(uint32_t), 1, fp);
	uint32_t count = chunk->GetCount();
	fwrite(&count, sizeof(uint32_t), 1, fp);

	for (uint32_t i = 0; i < count; ++i)
	{
		const Keyframe *frame = chunk->frames[i];

		for (uint32_t j = 0; j < frame->numJoints; ++j)
		{
			const Vector3 *position = &frame->position[j];
			const Vector3 *rotation = &frame->rotation[j];

			fwrite(&position->x, sizeof(float), 1, fp);
			fwrite(&position->y, sizeof(float), 1, fp);
			fwrite(&position->z, sizeof(float), 1, fp);

			fwrite(&rotation->x, sizeof(float), 1, fp);
			fwrite(&rotation->y, sizeof(float), 1, fp);
			fwrite(&rotation->z, sizeof(float), 1, fp);
		}
	}
}

void WriteChunk(AnimationsChunk *chunk, FILE *fp)
{
	uint32_t size = chunk->GetSize();
	if (size == 0)
		return;

	fputs("ANI", fp);
	fwrite(&size, sizeof(uint32_t), 1, fp);
	uint32_t count = chunk->GetCount();
	fwrite(&count, sizeof(uint32_t), 1, fp);

	for (uint32_t i = 0; i < count; ++i)
	{
		AnimationSequence *a = &chunk->animations[i];

		fwrite(a->name.c_str(), a->name.length(), 1, fp);
		char ch = '\0';
		fwrite(&ch, 1, 1, fp);

		fwrite(&a->start, 4, 1, fp);
		fwrite(&a->end, 4, 1, fp);
	}
}

