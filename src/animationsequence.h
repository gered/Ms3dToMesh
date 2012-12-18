#ifndef __ANIMATIONSEQUENCE_H_INCLUDED__
#define __ANIMATIONSEQUENCE_H_INCLUDED__

#include "common.h"
#include <string>

class AnimationSequence
{
public:
	std::string name;
	uint32_t start;
	uint32_t end;
};

#endif
