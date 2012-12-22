#include "metadatafile.h"

#include "../common.h"
#include "../animationsequence.h"
#include "../geometry/extragroupinfo.h"
#include <string>
#include <vector>

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
	return FALSE;
}
