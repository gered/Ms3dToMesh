#include "ms3d.h"

#include <stdio.h>

#include "../util/files.h"

Ms3d::Ms3d()
{
	m_numVertices = 0;
	m_numTriangles = 0;
	m_numMeshes = 0;
	m_numMaterials = 0;
	m_numJoints = 0;
	m_vertices = NULL;
	m_triangles = NULL;
	m_meshes = NULL;
	m_materials = NULL;
	m_joints = NULL;
}

void Ms3d::Release()
{
	SAFE_DELETE_ARRAY(m_vertices);
	SAFE_DELETE_ARRAY(m_triangles);
	SAFE_DELETE_ARRAY(m_meshes);
	SAFE_DELETE_ARRAY(m_materials);
	SAFE_DELETE_ARRAY(m_joints);
	m_numVertices = 0;
	m_numTriangles = 0;
	m_numMeshes = 0;
	m_numMaterials = 0;
	m_numJoints = 0;
}

BOOL Ms3d::Load(const std::string &file)
{
	FILE *fp;
	Ms3dHeader header;

	fp = fopen(file.c_str(), "rb");
	if (!fp)
		return FALSE;

	// filetype verification
	fread(&header.id, 10, 1, fp);
	if (strncmp(header.id, "MS3D000000", 10) != 0)
	{
		fclose(fp);
		return FALSE;
	}
	fread(&header.version, 4, 1, fp);
	if (header.version != 4)
	{
		fclose(fp);
		return FALSE;
	}

	// read vertices
	fread(&m_numVertices, 2, 1, fp);
	m_vertices = new Ms3dVertex[m_numVertices];

	for (uint16_t i = 0; i < m_numVertices; ++i)
	{
		Ms3dVertex *vertex = &m_vertices[i];

		fread(&vertex->editorFlags, 1, 1, fp);
		fread(&vertex->vertex.x, 4, 1, fp);
		fread(&vertex->vertex.y, 4, 1, fp);
		fread(&vertex->vertex.z, 4, 1, fp);
		fread(&vertex->jointIndex, 1, 1, fp);
		fread(&vertex->unused, 1, 1, fp);
	}

	// read triangle definitions
	fread(&m_numTriangles, 2, 1, fp);
	m_triangles = new Ms3dTriangle[m_numTriangles];

	for (uint16_t i = 0; i < m_numTriangles; ++i)
	{
		Ms3dTriangle *triangle = &m_triangles[i];

		fread(&triangle->editorFlags, 2, 1, fp);
		for (int j = 0; j < 3; ++j)
			fread(&triangle->vertices[j], 2, 1, fp);
		for (int j = 0; j < 3; ++j)
		{
			fread(&triangle->normals[j].x, 4, 1, fp);
			fread(&triangle->normals[j].y, 4, 1, fp);
			fread(&triangle->normals[j].z, 4, 1, fp);
		}
		for (int j = 0; j < 3; ++j)
			fread(&triangle->texCoords[j].x, 4, 1, fp);
		for (int j = 0; j < 3; ++j)
			fread(&triangle->texCoords[j].y, 4, 1, fp);
		fread(&triangle->smoothingGroup, 1, 1, fp);
		fread(&triangle->meshIndex, 1, 1, fp);
	}

	// read mesh information
	fread(&m_numMeshes, 2, 1, fp);
	m_meshes = new Ms3dMesh[m_numMeshes];

	for (uint16_t i = 0; i < m_numMeshes; ++i)
	{
		Ms3dMesh *mesh = &m_meshes[i];

		fread(&mesh->editorFlags, 1, 1, fp);
		ReadString(fp, mesh->name, 32);
		fread(&mesh->numTriangles, 2, 1, fp);
		mesh->triangles = new uint16_t[mesh->numTriangles];
		for (int j = 0; j < mesh->numTriangles; ++j)
			fread(&mesh->triangles[j], 2, 1, fp);
		fread(&mesh->materialIndex, 1, 1, fp);
	}

	// read material information
	fread(&m_numMaterials, 2, 1, fp);
	if (m_numMaterials > 0)
	{
		m_materials = new Ms3dMaterial[m_numMaterials];

		for (uint16_t i = 0; i < m_numMaterials; ++i)
		{
			Ms3dMaterial *material = &m_materials[i];

			ReadString(fp, material->name, 32);
			for (int j = 0; j < 4; ++j)
				fread(&material->ambient[j], 4, 1, fp);
			for (int j = 0; j < 4; ++j)
				fread(&material->diffuse[j], 4, 1, fp);
			for (int j = 0; j < 4; ++j)
				fread(&material->specular[j], 4, 1, fp);
			for (int j = 0; j < 4; ++j)
				fread(&material->emissive[j], 4, 1, fp);
			fread(&material->shininess, 4, 1, fp);
			fread(&material->transparency, 4, 1, fp);
			fread(&material->mode, 1, 1, fp);
			ReadString(fp, material->texture, 128);
			ReadString(fp, material->alpha, 128);
		}
	}

	// read joints
	fread(&m_animationFps, 4, 1, fp);
	fread(&m_editorAnimationTime, 4, 1, fp);
	fread(&m_numFrames, 4, 1, fp);
	fread(&m_numJoints, 2, 1, fp);
	if (m_numJoints > 0)
	{
		m_joints = new Ms3dJoint[m_numJoints];

		for (uint16_t i = 0; i < m_numJoints; ++i)
		{
			Ms3dJoint *joint = &m_joints[i];

			fread(&joint->editorFlags, 1, 1, fp);
			ReadString(fp, joint->name, 32);
			ReadString(fp, joint->parentName, 32);
			fread(&joint->rotation.x, 4, 1, fp);
			fread(&joint->rotation.y, 4, 1, fp);
			fread(&joint->rotation.z, 4, 1, fp);
			fread(&joint->position.x, 4, 1, fp);
			fread(&joint->position.y, 4, 1, fp);
			fread(&joint->position.z, 4, 1, fp);
			fread(&joint->numRotationFrames, 2, 1, fp);
			fread(&joint->numTranslationFrames, 2, 1, fp);
			joint->rotationFrames = new Ms3dKeyFrame[joint->numRotationFrames];
			for (uint16_t j = 0; j < joint->numRotationFrames; ++j)
			{
				Ms3dKeyFrame *frame = &joint->rotationFrames[j];
				fread(&frame->time, 4, 1, fp);
				fread(&frame->param.x, 4, 1, fp);
				fread(&frame->param.y, 4, 1, fp);
				fread(&frame->param.z, 4, 1, fp);
			}
			joint->translationFrames = new Ms3dKeyFrame[joint->numTranslationFrames];
			for (uint16_t j = 0; j < joint->numTranslationFrames; ++j)
			{
				Ms3dKeyFrame *frame = &joint->translationFrames[j];
				fread(&frame->time, 4, 1, fp);
				fread(&frame->param.x, 4, 1, fp);
				fread(&frame->param.y, 4, 1, fp);
				fread(&frame->param.z, 4, 1, fp);
			}
		}
	}

	fclose(fp);

	// check for an animation definition file
	std::string animationFile = file;
	animationFile.erase(animationFile.find_last_of('.', std::string::npos));
	animationFile.append(".animations");

	fp = fopen(animationFile.c_str(), "r");
	if (fp != NULL)
	{
		char *buffer = new char[80];
		std::string line;
		std::string name;
		std::string temp;
		int32_t start;
		int32_t end;

		while (!feof(fp))
		{
			fgets(buffer, 80, fp);
			line = buffer;

			if (strlen(buffer) > 5)		// minimum length for a viable frame definition
			{
				// get animation name
				int nameEnd = line.find_first_of(',');
				if (nameEnd == std::string::npos)
					continue;
				name = line.substr(0, nameEnd);

				// get start frame index
				int startEnd = line.find_first_of(',', nameEnd + 1);
				if (startEnd == std::string::npos)
					continue;
				temp = line.substr(nameEnd + 1, startEnd);
				start = atoi(temp.c_str());

				// get end frame index
				temp = line.substr(startEnd + 1, std::string::npos);
				end = atoi(temp.c_str());

				Ms3dAnimation *animation = new Ms3dAnimation();
				animation->name = name;
				animation->startFrame = start;
				animation->endFrame = end;
				m_animations.push_back(*animation);
			}
		}
		SAFE_DELETE_ARRAY(buffer);

		fclose(fp);
	}
	return TRUE;
}

int32_t Ms3d::FindIndexOfJoint(const std::string &jointName) const
{
	if (jointName.length() == 0)
		return -1;

	for (uint16_t i = 0; i < m_numJoints; ++i)
	{
		Ms3dJoint *joint = &m_joints[i];
		if (joint->name == jointName)
			return i;
	}

	return -1;
}
