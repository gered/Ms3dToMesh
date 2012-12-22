#ifndef __GEOMETRY_EXTRAGROUPINFO_H_INCLUDED__
#define __GEOMETRY_EXTRAGROUPINFO_H_INCLUDED__

#include "../common.h"
#include <string>

struct ExtraGroupInfo
{
	std::string name;
	std::string textureFile;
	BOOL alphaBlend;
	
	ExtraGroupInfo();
};

inline ExtraGroupInfo::ExtraGroupInfo()
{
	alphaBlend = FALSE;
}

#endif
