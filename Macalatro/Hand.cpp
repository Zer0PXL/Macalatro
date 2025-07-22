#include "Hand.hpp"
#include "Card.hpp"
#include "Debug.hpp"
#include "Round.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <memory>

void Hand::addCard(std::shared_ptr<Card> card)
{
	hand.push_back(card);
}

// Deprecated
std::shared_ptr<Card> Hand::playCard(const std::shared_ptr<Card> card)
{
	Debug::log("[Hand.cpp] ! - Use of deprecated function! Use playCards instead!");
	
	int size = hand.size();
	int cardID = -1;
	Card invalidCard(0, HEARTS, -1, NONE, BASIC);

	for (int i = 0; i < size; i++)
	{
		Debug::log("[Hand.cpp] Searching for card with ID ", std::to_string(card->getID()));
		if (hand[i]->getID() == card->getID())
		{
			Debug::log("[Hand.cpp] Found card!"); hand[i]->print();
			cardID = i;
			break;
		}
	}
	
	if (cardID == -1)
	{
		Debug::log("! - Invalid card selected (how?)");

		return std::make_shared<Card>(invalidCard);
	}
	else
	{
		auto& playedCard = hand[cardID];
		
		Debug::log("[Hand.cpp] Playing card..."); hand[cardID]->print();

		std::cout << "Played a "; playedCard->print();

		hand.erase(hand.begin() + cardID);

		Debug::log("[Hand.cpp] Deleted card from hand. Card is:"); playedCard->print();

		return playedCard;
	}
}

void Hand::playCards(const std::vector<std::shared_ptr<Card>> cards, GameState& gs)
{
	std::vector<std::shared_ptr<Card>> toPlay;
	std::vector<int> toBeDeleted;

	for (int i = 0; i < hand.size(); i++)
	{
		for (int j = 0; j < cards.size(); j++)
		{
			if (cards[j]->getID() == hand[i]->getID())
			{
				toPlay.push_back(hand[i]);
				toBeDeleted.push_back(i);

				break;
			}
		}
	}

	if (toPlay.size() < 1)
	{
		Debug::log("! - No cards for playCards (how?)");

		toPlay = { std::make_shared<Card>(0, HEARTS, -1, NONE, BASIC) };
	}

	int rankCheck = toPlay[0]->getRank();
	for (int i = toPlay.size()-1; i >= 0; i--)
	{
		if (toPlay[i]->getRank() != rankCheck)
		{
			toPlay.erase(toPlay.begin() + i);
			toBeDeleted.erase(toBeDeleted.begin() + i);
		}
	}

	std::shared_ptr<Card> currentTop = gs.pile.getCard();

	for (int i = 0; i < toPlay.size(); i++)
	{
		Debug::log("[Hand.cpp] Checking if the card is playable...");
		if (Card::isPlayable(toPlay[i], currentTop))
		{
			if (!(toPlay[i]->getAbility() == COLOR))
			{
				gs.pile.addCard(toPlay[i]);
			}
			if (toPlay[i]->getAbility() == COLOR && !(gs.pile.getCard()->getOwner() == NONE))
			{
				gs.pile.addCard(toPlay[i]);
			}
			std::cout << "Played: "; toPlay[i]->print(); std::cout << "\n";
			currentTop = gs.pile.getCard();
		}
		else
		{
			std::cout << "Not playable!\n";
			if (gs.turn == AITURN) gs.turn = PLAYERTURN;
		}
	}

	for (int i = toBeDeleted.size() - 1; i >= 0; i--)
	{
		hand.erase(hand.begin() + toBeDeleted[i]);
	}
}

int Hand::getSize()
{
	return hand.size();
}

std::vector<std::shared_ptr<Card>> Hand::getHand()
{
	return hand;
}