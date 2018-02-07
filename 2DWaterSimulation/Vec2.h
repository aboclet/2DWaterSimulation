#pragma once
#include <cmath>

struct Vec2
{
	float x;
	float y;
};

inline Vec2 add(Vec2 a, Vec2 b)
{
	a.x += b.x;
	a.y += b.y;
	return a;
}

inline Vec2 minus(Vec2 a, Vec2 b)
{
	a.x -= b.x;
	a.y -= b.y;
	return a;
}

inline float dot(Vec2 a, Vec2 b)
{
	return (a.x * b.x) + (a.y * b.y);
}

inline float distance(Vec2 a, Vec2 b)
{
	return std::sqrt(((a.x - b.x) * (a.x - b.x)) + ((a.y - b.y) * (a.y - b.y)));
}

inline float Length(Vec2 a)
{
	return std::sqrt(a.x * a.x) + (a.y * a.y);
}

inline Vec2 Normalise(Vec2 a)
{
	float length = Length(a);

	return Vec2{ a.x / length, a.y / length };
}

inline void Reverse(Vec2 a)
{
	a.x = -a.x;
	a.y = -a.y;
}

inline float GetAngle(Vec2 a)
{
	float angle = atan2f(a.y, a.x);
	return angle;
}

