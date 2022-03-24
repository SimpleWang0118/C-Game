#include "Random.h"

void Random::Init()
{
}

void Random::Seed(unsigned int seed)
{
}

float Random::GetFloat()
{
	return GetFloatRange(0.0f, 1.0f);
}

float Random::GetFloatRange(float min, float max)
{
	uniform_real_distribution<float> dist(min, max);
	return dist(sGenerator);
}

int Random::GetIntRange(int min, int max)
{
	return 0;
}

Vector2 Random::GetVector(const Vector2& min, const Vector2& max)
{
	Vector2 r = Vector2(GetFloat(), GetFloat());
	return min + (max - min) * r;
}

Vector3 Random::GetVector(const Vector3& min, const Vector3& max)
{
	return Vector3();
}