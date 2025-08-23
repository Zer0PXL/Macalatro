#pragma once
#include "Table.hpp"
#include "Hand.hpp"
#include <memory>

extern bool debugMode;
extern bool cheats;

class Debug
{
	// man, i love cpp
private:

public:
	static void toggleDebugMode();
	static void toggleCheats();
	static void logTurn(GameState& gs);
	static void log(std::string text1, std::string text2 = "", std::string text3 = "", std::string text4 = "", std::string text5 = "");
	static void logCardVector(std::vector<Card>& cards);
	static std::string abilityToString(Ability a);
	static std::string enhancementToString(Enhancement e);
};

