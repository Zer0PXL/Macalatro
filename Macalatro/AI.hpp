#pragma once
#include "Card.hpp"
#include <vector>
#include <memory>

enum Difficulty
{
	DUMB,
	SMART,
	CHEATER
};

class AI
{
private:
	std::vector<std::shared_ptr<Card>> heartCards;
	std::vector<std::shared_ptr<Card>> spadeCards;
	std::vector<std::shared_ptr<Card>> diamondCards;
	std::vector<std::shared_ptr<Card>> clubCards;
	std::vector<std::shared_ptr<Card>> bestSuit;

	Difficulty difficulty = SMART;
public:
	void changeDifficulty(Difficulty difficulty);
	void playTurn(GameState& gs);
	Suit determineBestSuit();
	Difficulty getDifficulty();
};

