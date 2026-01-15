#include "Vector2D.h"
#include <cmath>

Vector2D::Vector2D() {
	x_ = 0;
	y_ = 0;
}

Vector2D::Vector2D(float x, float y) {
	x_ = x;
	y_ = y;
}

float Vector2D::GetX() {
	return x_;
}

void Vector2D::SetX(float x) {
	x_ = x;
}

float Vector2D::GetY() {
	return y_;
}

void Vector2D::SetY(float y) {
	y_ = y;
}

float Vector2D::Length() {
	return sqrt(x_*x_ + y_*y_);
}

Vector2D Vector2D::Add(float x, float y) {
	float newX = x_ + x;
	float newY = y_ + y;
	return Vector2D(newX, newY);
}

Vector2D Vector2D::Subtract(float x, float y) {
	float newX = x_ - x;
	float newY = y_ - y;
	return Vector2D(newX, newY);
}

Vector2D Vector2D::Multiply(float scalar) {
	float newX = x_ * scalar;
	float newY = y_ * scalar;
	return Vector2D(newX, newY);
}

Vector2D Vector2D::Normalize() {
	float newX = (Length() == 0 ? 0 : x_ / Length());
	float newY = (Length() == 0 ? 0 : y_ / Length());;
	return Vector2D(newX, newY);
}
