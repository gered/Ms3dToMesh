#ifndef __METADATA_METADATAFILE_H_INCLUDED__
#define __METADATA_METADATAFILE_H_INCLUDED__

#include "../common.h"
#include "../animationsequence.h"
#include "../geometry/extragroupinfo.h"
#include <string>
#include <vector>

class MetadataFile
{
public:
	MetadataFile();
	virtual ~MetadataFile()                                { Release(); }
	
	void Release();
	BOOL Load(const std::string &file);
	
	float GetScale() const                                 { return m_scale; }
	uint32_t GetNumAnimations() const                      { return m_animations.size(); }
	const AnimationSequence* GetAnimations() const         { return &m_animations[0]; }
	uint32_t GetNumGroupInfo() const                       { return m_groupInfo.size(); }
	const ExtraGroupInfo* GetGroupInfo() const             { return &m_groupInfo[0]; }
	
	BOOL IsLoaded() const                                  { return m_isLoaded; }
	
private:
	BOOL m_isLoaded;
	
	float m_scale;
	std::vector<AnimationSequence> m_animations;
	std::vector<ExtraGroupInfo> m_groupInfo;
};

#endif
