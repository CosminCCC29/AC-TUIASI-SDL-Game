#include "Movement.h"
#include "Game.h"

Movement::Movement(float x, float y, int speedx, int speedy) : position(x, y), speed(speedx, speedy) {};

Movement::Movement() : position(0.0f, 0.0f), velocity(0, 0), speed(0, 0) {};

void Movement::setPositionx(float x) { position.x = x; }
void Movement::setPositiony(float y) { position.y = y; }
void Movement::setVelocityx(float x) { velocity.x = x; }
void Movement::setVelocityy(float y) { velocity.y = y; }
void Movement::setSpeedx(float x) { speed.x = x; }
void Movement::setSpeedy(float y) { speed.y = y; }

float Movement::getPositionx() { return position.x; }
float Movement::getPositiony() { return position.y; }

float Movement::getSpeedx() { return speed.x; };
float Movement::getSpeedy() { return speed.y; };
float Movement::getVelocityx() { return velocity.x; }
float Movement::getVelocityy() { return velocity.y; }

void Movement::update()
{

	position.x += velocity.x * speed.x;
	position.y += velocity.y * speed.y;

};
