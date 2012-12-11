#include "meshfile.h"

#include "assets/animationsequence.h"
#include "ms3d/ms3d.h"
#include "chunks/animations.h"
#include "chunks/chunks.h"
#include "chunks/groups.h"
#include "chunks/joints.h"
#include "chunks/jointtovertices.h"
#include "chunks/keyframes.h"
#include "chunks/normals.h"
#include "chunks/texcoords.h"
#include "chunks/triangles.h"
#include "chunks/vertices.h"
#include "geometry/group.h"
#include "geometry/joint.h"
#include "geometry/jointvertexinfo.h"
#include "geometry/keyframe.h"
#include "geometry/triangle.h"
#include "geometry/vector2.h"
#include "geometry/vector3.h"
#include <string>

BOOL ConvertToMeshFile(const std::string &meshFilename, const Ms3d *source)
{
	return FALSE;
}
