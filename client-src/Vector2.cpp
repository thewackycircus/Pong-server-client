#include "Vector2.h"
Vector2::Vector2(int _x, int _y) {
	x = _x; 
	y = _y;
}

// getters
int Vector2::getX() {
	return x;
}

int Vector2::getY() {
	return y;
}

// setters
void Vector2::setX(int value) {
	x = value;
}

void Vector2::setY(int value) {
	y = value;
}