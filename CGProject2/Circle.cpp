#include "Circle.h"
#define PI 3.14159265358979323846f
Circle::Circle(Interactions::Coordinate center, int radius) {
	this->position = center;
	this->radius   = radius;
	float x,y;
	for (int i = 0; i < 50; ++i) {
		x = radius * cos(2 * i * PI / 50) + center.coords[0]/2;
		y = radius * sin(2 * i * PI / 50) + center.coords[1]/2;
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
	compositeTransformation.composeWith(&toOrigin);
	compositeTransformation.composeWith(&rotate);
	compositeTransformation.composeWith(&toOriginal);
	//Apply component matrices to all circle vertices
	for (auto& vertex : this->vertices) {
		compositeTransformation.applyTo(vertex.coords);
	}
}
void Circle::translate(float tx, float ty) {
	TranslationMatrix translation = TranslationMatrix(tx, ty);
	
	for (auto& vertex : this->vertices) {
		translation.applyTo(vertex.coords);
	}
	translation.applyTo(this->position.coords);
}
void Circle::applyForce(float force[2]) {
	this->acceleration[0] += force[0];
	this->acceleration[1] += force[1];
}
void Circle::update() {
	this->velocity[0] += this->acceleration[0];
	this->velocity[1] += this->acceleration[1];
	this->position.coords[0] += this->velocity[0];
	this->position.coords[1] += this->velocity[1];
	this->acceleration[0] = 0;
	this->acceleration[1] = 0;
}