#pragma once
#include "Round.hpp"

enum Difficulty
{
	DUMB,
	SMART,
	CHEATER
};

extern Difficulty difficulty;

class AI
{
private:

public:
	void changeDifficulty(Difficulty difficulty);
	void playTurn(GameState& gs);
};

