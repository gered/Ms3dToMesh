#ifndef __METADATA_METADATAFILE_H_INCLUDED__
#define __METADATA_METADATAFILE_H_INCLUDED__

#include "../common.h"
#include <string>
#include <vector>

struct AnimationSequence;
struct ExtraGroupInfo;

class MetadataFile
{
public:
	MetadataFile();
	virtual ~MetadataFile()                                { Release(); }
	
	void Release();
	BOOL Load(const std::string &file);
	
	uint32_t GetNumAnimations() const                      { return m_animations.size(); }
	const AnimationSequence* GetAnimations() const         { return &m_animations[0]; }
	uint32_t GetNumGroupInfo() const                       { return m_groupInfo.size(); }
	const ExtraGroupInfo* GetGroupInfo() const             { return &m_groupInfo[0]; }
	
	BOOL IsLoaded() const                                  { return m_isLoaded; }
	
private:
	BOOL m_isLoaded;
	
	std::vector<AnimationSequence> m_animations;
	std::vector<ExtraGroupInfo> m_groupInfo;
};

#endif
