#ifndef __CHUNKS_CHUNKS_H_INCLUDED__
#define __CHUNKS_CHUNKS_H_INCLUDED__

#include "../common.h"
#include <stdio.h>

struct VerticesChunk;
struct NormalsChunk;
struct TexCoordsChunk;
struct TrianglesChunk;
struct GroupsChunk;
struct JointsChunk;
struct JointToVerticesChunk;
struct KeyframesChunk;
struct AnimationsChunk;

void WriteFileHeader(FILE *fp);

// to be perfectly honest, i don't care to come up with a really elegant solution for this converter tool :p

void WriteChunk(VerticesChunk *chunk, FILE *fp);
void WriteChunk(NormalsChunk *chunk, FILE *fp);
void WriteChunk(TexCoordsChunk *chunk, FILE *fp);
void WriteChunk(TrianglesChunk *chunk, FILE *fp);
void WriteChunk(GroupsChunk *chunk, FILE *fp);
void WriteChunk(JointsChunk *chunk, FILE *fp);
void WriteChunk(JointToVerticesChunk *chunk, FILE *fp);
void WriteChunk(KeyframesChunk *chunk, FILE *fp);
void WriteChunk(AnimationsChunk *chunk, FILE *fp);

#endif
