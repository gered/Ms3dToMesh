#ifndef __ASSETS_ANIMATIONSEQUENCE_H_INCLUDED__
#define __ASSETS_ANIMATIONSEQUENCE_H_INCLUDED__

#include "../common.h"
#include <string>

class AnimationSequence
{
public:
	std::string name;
	uint32_t start;
	uint32_t end;
};

#endif
