#pragma once
#include <vector>
#include "Card.hpp"
#include <memory>

// Universal Card ID
extern int ucid;

class Deck
{
private:
	std::vector<std::shared_ptr<Card>> cards;

public:
	std::shared_ptr<Card> draw();
	Deck(Owner owner);
	void shuffle();
	void addCard(std::shared_ptr<Card> c);
	int getSize();
	std::vector<std::shared_ptr<Card>> getDeck();
};