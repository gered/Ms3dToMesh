#include "metadatafile.h"

#include "../common.h"
#include "../animationsequence.h"
#include "../geometry/extragroupinfo.h"
#include <pugixml.hpp>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

MetadataFile::MetadataFile()
{
	m_isLoaded = FALSE;
}

void MetadataFile::Release()
{
	m_isLoaded = FALSE;
}

BOOL MetadataFile::Load(const std::string &file)
{
	if (access(file.c_str(), F_OK) == -1)
		// file doesn't exist, but this isn't an error as metadata is optional
		return TRUE;
	
	pugi::xml_document doc;
	pugi::xml_parse_result parsed = doc.load_file(file.c_str());
	
	if (!parsed)
	{
		printf("Metadata XML parse error: %ld:%s\n", parsed.offset, parsed.description());
		return FALSE;
	}
	
	pugi::xml_node rootNode = doc.child("metadata");
	if (rootNode.type() == pugi::node_null)
		return FALSE;
	
	pugi::xml_node animationsNode = rootNode.child("animations");
	for (pugi::xml_node animation = animationsNode.child("add"); animation; animation = animation.next_sibling("add"))
	{
		const char *name = animation.attribute("name").value();
		uint32_t firstFrame = animation.attribute("first").as_uint();
		uint32_t lastFrame = animation.attribute("last").as_uint();
		
		if (strlen(name) == 0)
		{
			printf("Metadata XML error: missing or empty animation name\n");
			return FALSE;
		}
		if (firstFrame == lastFrame)
		{
			printf("Metadata XML error: zero-length animation\n");
			return FALSE;
		}
		if (firstFrame > lastFrame)
		{
			printf("Metadata XML error: negative-length animation\n");
			return FALSE;
		}
		
		AnimationSequence newAnimation;
		newAnimation.name = name;
		newAnimation.start = firstFrame;
		newAnimation.end = lastFrame;
		
		m_animations.push_back(newAnimation);
	}
	
	pugi::xml_node groupsNode = rootNode.child("groups");
	for (pugi::xml_node group = groupsNode.child("group"); group; group = group.next_sibling("group"))
	{
		bool hasName = !group.attribute("name").empty();
		bool hasIndex = !group.attribute("index").empty();
		bool hasTexture = !group.attribute("texture").empty();
		const char *name = group.attribute("name").value();
		uint32_t index = group.attribute("index").as_uint();
		bool isAlpha = group.attribute("alpha").as_bool();
		const char *texture = group.attribute("texture").value();
		
		if (!hasName && !hasIndex)
		{
			printf("Metadata XML error: group name or index required\n");
			return FALSE;
		}
		if (hasName && strlen(name) == 0)
		{
			printf("Metadata XML error: empty group name\n");
			return FALSE;
		}
		if (hasTexture && strlen(texture) == 0)
		{
			printf("Metadata XML error: empty texture name\n");
			return FALSE;
		}
		
		ExtraGroupInfo groupInfo;
		groupInfo.specifiedByName = (BOOL)hasName;
		if (hasName)
			groupInfo.name = name;
		else
			groupInfo.index = index;
		groupInfo.alphaBlend = isAlpha;
		if (hasTexture)
			groupInfo.textureFile = texture;
		
		m_groupInfo.push_back(groupInfo);
	}
	
	m_isLoaded = TRUE;
	return TRUE;
}
