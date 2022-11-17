#pragma once

// this class represents the position of a 2D object
class Vector2 {
	private:
		int x;
		int y;

	public:

		Vector2();

		Vector2(int _x, int _y);

		// getters
		int getX();
		int getY();

		// setters
		void setX(int value);
		void setY(int value);
};