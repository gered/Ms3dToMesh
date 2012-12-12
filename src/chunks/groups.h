#ifndef __CHUNKS_GROUPS_H_INCLUDED__
#define __CHUNKS_GROUPS_H_INCLUDED__

#include "../common.h"
#include "../geometry/group.h"
#include <vector>

struct GroupsChunk
{
	std::vector<Group> groups;

	uint32_t GetCount() const;
	uint32_t GetSize() const;
};

inline uint32_t GroupsChunk::GetCount() const
{
	return groups.size();
}

inline uint32_t GroupsChunk::GetSize() const
{
	if (groups.size() == 0)
		return 0;

	uint32_t size = sizeof(uint32_t);  // count

	for (uint32_t i = 0; i < groups.size(); ++i)
	{
		const Group *group = &groups[i];
		size += group->GetSize();
	}

	return size;
}

#endif
