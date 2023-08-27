#pragma once

#include <iostream>

float mapRange(float value, float inMin, float inMax, float outMin, float outMax);

float aSquareRoot(float x);

struct vector2f
{
	vector2f() {}

	vector2f(float x, float y)
		: x(x), y(y)
	{
		//std::cout << "x: " << x << " y: " << y << std::endl;
	}

	void print();

	void normalize();



	float distance(vector2f b);

	void addVector(vector2f addend);
	void addFloat(float addend);
	vector2f returnAddVector(vector2f addend);
	vector2f returnAddFloat(float addend);

	void subtractVector(vector2f subtrahend);
	void subtractFloat(float subtrahend);
	vector2f returnSubtractVector(vector2f subtrahend);
	vector2f returnSubtractFloat(float subtrahend);

	void multiplyVector(vector2f multiplicand);
	void multiplyFloat(float multiplicand);
	vector2f returnMultiplyVector(vector2f multiplicand);
	vector2f returnMultiplyFloat(float multiplicand);

	void divideVector(vector2f divisor);
	void divideFloat(float divisor);
	vector2f returnDivideVector(vector2f divisor);
	vector2f returnDivideFloat(float divisor);

	float x, y;
};

