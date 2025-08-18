#include "Chance.hpp"
#include "Debug.hpp"
#include <random>
#include <ctime>
#include <string>

int Chance::chance(int x, int y)
{
	int random;
	
	Debug::log("[Chance.cpp] Random chance of ", std::to_string(x), " in ", std::to_string(y));
	
	std::mt19937 engine(std::time(nullptr));
	std::uniform_int_distribution<int> dist(x, y);

	random = dist(engine);

	Debug::log("[Chance.cpp] Resulted in ", std::to_string(random));

	return random;
}