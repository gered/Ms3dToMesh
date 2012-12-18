#ifndef __VECTOR2_H_INCLUDED__
#define __VECTOR2_H_INCLUDED__

class Vector2
{
public:
	float x;
	float y;
};

bool operator==(const Vector2 &left, const Vector2 &right);

inline bool operator==(const Vector2 &left, const Vector2 &right)
{
	return (left.x == right.x && left.y == right.y);
}


#endif