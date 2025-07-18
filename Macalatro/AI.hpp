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
	std::vector<std::shared_ptr<Card>> heartCards;
	std::vector<std::shared_ptr<Card>> spadeCards;
	std::vector<std::shared_ptr<Card>> diamondCards;
	std::vector<std::shared_ptr<Card>> clubCards;
	std::vector<std::shared_ptr<Card>> bestSuit;
public:
	void changeDifficulty(Difficulty difficulty);
	void playTurn(GameState& gs);
	Suit determineBestSuit();
};

