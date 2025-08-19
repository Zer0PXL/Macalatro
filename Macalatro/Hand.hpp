#pragma once
#include <iostream>
#include <vector>
#include "Card.hpp"
#include "Deck.hpp"
#include <memory>

struct GameState;

class Hand
{
private:
	std::vector<std::shared_ptr<Card>> hand;
public:
	void addCard(std::shared_ptr<Card> card);
	std::shared_ptr<Card> playCard(const std::shared_ptr<Card> card);
	void playCards(const std::vector<std::shared_ptr<Card>> cards, GameState& gs);
	int getSize();
	std::vector<std::shared_ptr<Card>> getHand();
};

