#pragma once

#include <fstream>
#include <string>

namespace utility
{
inline float hireTimeInSeconds()
{
	float time = SDL_GetTicks();
	time *= 0.001f;
	return time;
}
}