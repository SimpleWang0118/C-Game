#pragma once
#include"Component.h"
#include"Math.h"
bool Intersect(const CircleComponent& a, const CircleComponent& b);
class CircleComponent : public Component
{
public:
	CircleComponent(class Actor* owner);
	void SetRadius(float radius) { mRadius = radius; }
	float GetRadius() const;
	const Vector2& GetCenter() const;
private:
	float mRadius;
};