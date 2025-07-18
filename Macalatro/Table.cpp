#include "Table.hpp"
#include "Deck.hpp"
#include "Debug.hpp"
#include <string>
#include <vector>
#include <iostream>

Table::Table()
{
	
}

void Table::addCard(std::shared_ptr<Card> card)
{
	Debug::log("Added to pile: "); card->print();
	pile.push_back(card);
}

void Table::addMultiCard(const std::vector<std::shared_ptr<Card>> cards)
{
	for (int i = 0; i < cards.size(); i++)
	{
		pile.push_back(cards[i]);
	}
}

std::shared_ptr<Card> Table::getCard()
{	
	if (pile.size() > 0)
	{
		return pile.back();
	}
	else
	{
		Debug::log("!- 0 cards in pile!(how?)");

		return std::make_shared<Card>(5, HEARTS, -2, NONE, BASIC);
	}
}

std::vector<std::shared_ptr<Card>> Table::getPile()
{
	return pile;
}

void Table::clearPile(Deck& playerDeck, Deck& aiDeck)
{
	for (int i = 0; i < pile.size(); i++)
	{
		if (pile[i]->getOwner() == PLAYER) playerDeck.addCard(pile[i]);
		if (pile[i]->getOwner() == OWNERAI) aiDeck.addCard(pile[i]);
	}

	pile.clear();
}