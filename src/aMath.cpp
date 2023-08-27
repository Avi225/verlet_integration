#include <aMath.hpp>
#include <iostream>
#include <cmath>

void vector2f::print()
{
	std::cout << x << ", " << y << std::endl;
}

void vector2f::normalize()
{
	float i = aSquareRoot(x * x + y * y);
	x = x / i;
	y = y / i;
}


float mapRange(float value, float inMin, float inMax, float outMin, float outMax)
{
	return ((value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin);
}

float aSquareRoot(const float x)  
{
  union
  {
    int i;
    float x;
  } u;

  u.x = x;
  u.i = (1<<29) + (u.i >> 1) - (1<<22); 
  return u.x;
} 

float vector2f::distance(vector2f b)
{
	return (aSquareRoot((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y)));
}

void vector2f::addVector(vector2f addend)
{
	x += addend.x;
	y += addend.y;
}

void vector2f::addFloat(float addend)
{
	x += addend;
	y += addend;
}

vector2f vector2f::returnAddVector(vector2f addend)
{
	return (vector2f(x + addend.x, y + addend.y));
}

vector2f vector2f::returnAddFloat(float addend)
{
	return (vector2f(x + addend, y + addend));
}

void vector2f::subtractVector(vector2f subtrahend)
{
	x -= subtrahend.x;
	y -= subtrahend.y;
}

void vector2f::subtractFloat(float subtrahend)
{
	x -= subtrahend;
	y -= subtrahend;
}

vector2f vector2f::returnSubtractVector(vector2f subtrahend)
{
	return (vector2f(x - subtrahend.x, y - subtrahend.y));
}

vector2f vector2f::returnSubtractFloat(float subtrahend)
{
	return (vector2f(x - subtrahend, y - subtrahend));
}

void vector2f::multiplyVector(vector2f multiplicand)
{
	x *= multiplicand.x;
	y *= multiplicand.y;
}

void vector2f::multiplyFloat(float multiplicand)
{
	x *= multiplicand;
	y *= multiplicand;
}

vector2f vector2f::returnMultiplyVector(vector2f multiplicand)
{
	return (vector2f(x *= multiplicand.x, y *= multiplicand.y));
}

vector2f vector2f::returnMultiplyFloat(float multiplicand)
{
	return (vector2f(x *= multiplicand, y *= multiplicand));
}

void vector2f::divideVector(vector2f divisor)
{
	x /= divisor.x;
	y /= divisor.y;
}

void vector2f::divideFloat(float divisor)
{
	x /= divisor;
	y /= divisor;
}

vector2f vector2f::returnDivideVector(vector2f divisor)
{
	return (vector2f(x /= divisor.x, y /= divisor.y));
}

vector2f vector2f::returnDivideFloat(float divisor)
{
	return (vector2f(x /= divisor, y /= divisor));
}
