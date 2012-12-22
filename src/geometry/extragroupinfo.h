#ifndef __GEOMETRY_EXTRAGROUPINFO_H_INCLUDED__
#define __GEOMETRY_EXTRAGROUPINFO_H_INCLUDED__

#include "../common.h"
#include <string>

struct ExtraGroupInfo
{
	BOOL specifiedByName;
	std::string name;
	uint32_t index;
	std::string textureFile;
	BOOL alphaBlend;
	
	ExtraGroupInfo();
};

inline ExtraGroupInfo::ExtraGroupInfo()
{
	specifiedByName = FALSE;
	index = 0;
	alphaBlend = FALSE;
}

#endif
