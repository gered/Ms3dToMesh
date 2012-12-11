#ifndef __MESHFILE_H_INCLUDED__
#define __MESHFILE_H_INCLUDED__

#include "common.h"
#include <string>

class Ms3d;

BOOL ConvertToMeshFile(const std::string &meshFilename, const Ms3d *source, float scaleFactor);

#endif
