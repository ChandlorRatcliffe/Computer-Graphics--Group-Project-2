#pragma once
#include "commonLibs.h"
#include "interactions.h"
class Circle
{
public:
	Circle(Interactions::Coordinate, int radius);
	void drawCircle(float r, float g, float b);
	Interactions::Coordinate getPosition() { return this->position; }
	int getRadius() { return this->radius; }
	void rotate(float theta);
	void translate(float tx, float ty);
	void applyForce(float force[2]);
	void update();
private:
	int radius;
	Interactions::Coordinate position;
	std::vector<Interactions::Coordinate> vertices;
	float velocity[2];
	float acceleration[2];
};

