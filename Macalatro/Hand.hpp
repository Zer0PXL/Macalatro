#pragma once
#include <iostream>
#include <vector>
#include "Card.hpp"
#include "Deck.hpp"
#include <memory>

class Hand
{
private:
	std::vector<std::shared_ptr<Card>> hand;
public:
	void addCard(std::shared_ptr<Card> card);
	std::shared_ptr<Card> playCard(const std::shared_ptr<Card> card);
	std::vector<std::shared_ptr<Card>> playMultiCard(const std::vector<std::shared_ptr<Card>> cards);
	int getSize();
	std::vector<std::shared_ptr<Card>> getHand();
};

