#pragma once
#include "commonLibs.h"
#include "interactions.h"
class Circle
{
public:
	/**
	 * Constructors. 
	 * Default gives circle at the default coordinate
	 * with radius 1.
	 * Overloaded constructor takes a center and radius.
	 */
	Circle();
	Circle(Interactions::Coordinate center, int radius);
	/**
	 * Draw the circle with the given color in RGB format.
	 */
	void drawCircle(float r, float g, float b);
	/**
	 * Returns current position.
	 */
	Interactions::Coordinate getPosition() { return this->position; }
	/**
	 * Returns current radius.
	 */
	int getRadius() { return this->radius; }
	/**
	 * Rotate the circle by theta degrees. 
	 */
	void rotate(float theta);
	/**
	 * Translate the circle by (tx,ty)
	 */
	void translate(float tx, float ty);
	/**
	 * Apply a two dimensional force to the circle. 
	 * This is used to start the circle moving, and in 
	 * collision handling to change the direction of the circle.
	 * It's written such that it could be used for any 
	 * instantaneous force, or to be used each update loop for
	 * continuous forces like gravity. This program doesn't need
	 * to have this functionality, but it's easier for me to think
	 * about this with physics than it is to imagine something else.
	 */
	void applyForce(float force[2]);
	/**
	 * Calculates new velocity from acceleration.
	 * Calculates new position from velocity.
	 * Calculates rotation based on distance traveled. 
	 * Applies apporpriate transformations to achieve the effect.
	 */
	void update();
private:
	int radius;
	Interactions::Coordinate position;
	std::vector<Interactions::Coordinate> vertices;
	float velocity[2];
	float acceleration[2];
};

