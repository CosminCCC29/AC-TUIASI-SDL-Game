#pragma once
#include "Vector2D.h"
#include "Component.h"
#include "Collision.h"

class Movement
{
	Vector2D position;
	Vector2D velocity;
	Vector2D speed;

public:

	Movement();
	Movement(float x, float y, int speedx, int speedy);

	~Movement() = default;

	void setPositionx(float x);
	void setPositiony(float y);
	void setVelocityx(float x);
	void setVelocityy(float y);
	void setSpeedx(float x);
	void setSpeedy(float x);

	float getSpeedx();
	float getSpeedy();
	float getVelocityx();
	float getVelocityy();

	float getPositionx();
	float getPositiony();

	void update();

};
