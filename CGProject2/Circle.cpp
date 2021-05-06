#include "Circle.h"
#define PI 3.14159265358979323846f

Circle::Circle() {
	this->position = Interactions::Coordinate();
	this->radius = 1;
}
Circle::Circle(Interactions::Coordinate center, int radius) {
	this->position = center;
	this->radius   = radius;
	float x,y;
	for (int i = 0; i < 50; ++i) {
		x = radius * cos(2 * i * PI / 50) + center.coords[0];
		y = radius * sin(2 * i * PI / 50) + center.coords[1];
		this->vertices.push_back(Interactions::Coordinate((GLfloat) x,(GLfloat) y));
	}
	this->acceleration[0] = 0;
	this->acceleration[1] = 0;
	this->velocity[0] = 0;
	this->velocity[1] = 0;
};
void Circle::drawCircle(float r, float g, float b) {
	glColor3f(r, g, b);
	glBegin(GL_POLYGON);
	for (auto& vertex : vertices) {
		glVertex2f(vertex.coords[0], vertex.coords[1]);
	}
	glEnd();
}
void Circle::rotate(float theta) {
	
	//Build component matrices
	CompositeMatrix compositeTransformation = CompositeMatrix();
	TranslationMatrix toOrigin   = TranslationMatrix(float(-this->position.coords[0]),
												     float(-this->position.coords[1]));
	RotationMatrix rotate = RotationMatrix(theta);
	TranslationMatrix toOriginal = TranslationMatrix(float(this->position.coords[0]),
											         float(this->position.coords[1]));
	//Compose component matrices

	compositeTransformation.composeWith(&toOriginal);
	compositeTransformation.composeWith(&rotate);
	compositeTransformation.composeWith(&toOrigin);
	//Apply component matrices to all circle vertices
	for (auto& vertex : this->vertices) {
		compositeTransformation.applyTo(vertex.coords);
	}
	compositeTransformation.applyTo(this->position.coords);

}
void Circle::translate(float tx, float ty) {
	TranslationMatrix translation = TranslationMatrix(tx, ty);

	translation.applyTo(this->position.coords);
	for (auto& vertex : this->vertices) {
		translation.applyTo(vertex.coords);
	}
}
void Circle::applyForce(float force[2]) {
	this->acceleration[0] += force[0];
	this->acceleration[1] += force[1];
}
void Circle::update() {
	//Collect position pre-transformation
	float oldPosition[2];
	oldPosition[0] = this->position.coords[0];
	oldPosition[1] = this->position.coords[1];
	//Handle Physics
	this->velocity[0] += this->acceleration[0];
	this->velocity[1] += this->acceleration[1];
	this->acceleration[0] = 0;
	this->acceleration[1] = 0;
	//Move object
	this->translate(this->velocity[0], this->velocity[1]);
	//Rotate object by distance moved:
	float deltaX = (oldPosition[0] - this->position.coords[0]);
	float deltaY = (oldPosition[1] - this->position.coords[1]);
	float distanceTravelled = std::sqrt(deltaX*deltaX + deltaY*deltaY);
	float neededRotation = distanceTravelled/this->radius;
	neededRotation *= 180/PI; // convert to degrees.
	this->rotate(neededRotation);	
}
