#pragma once
#include <vector>
#include "Card.hpp"
#include "Deck.hpp"
#include <memory>

class Table
{
private:
	std::vector<std::shared_ptr<Card>> pile;
public:
	Table();
	void addCard(std::shared_ptr<Card> card);
	std::shared_ptr<Card> getCard();
	std::vector<std::shared_ptr<Card>> getPile();
	void clearPile(Deck& playerDeck, Deck& aiDeck);
	void addMultiCard(const std::vector<std::shared_ptr<Card>> cards);
};