#include "Hand.hpp"
#include "Card.hpp"
#include "Debug.hpp"
#include <iostream>
#include <vector>

void Hand::addCard(std::shared_ptr<Card> card)
{
	hand.push_back(card);
}

std::shared_ptr<Card> Hand::playCard(const std::shared_ptr<Card> card)
{
	int size = hand.size();
	int cardID = -1;
	Card invalidCard(0, HEARTS, -1, NONE, BASIC);

	for (int i = 0; i < size; i++)
	{
		if (hand[i]->getID() == card->getID())
		{
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
		
		std::cout << "Played a "; playedCard->print();

		hand.erase(hand.begin() + cardID);

		return playedCard;
	}
}

std::vector<std::shared_ptr<Card>> Hand::playMultiCard(const std::vector<std::shared_ptr<Card>> cards)
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
		Debug::log("! - No cards for playMultiCards (how?)");

		toPlay = { std::make_shared<Card>(0, HEARTS, -1, NONE, BASIC) };

		return toPlay;
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

	for (int i = toBeDeleted.size() - 1; i >= 0; i--)
	{
		hand.erase(hand.begin() + toBeDeleted[i]);
	}

	for (int i = 0; i < toPlay.size(); i++)
	{
		std::cout << "Played: "; toPlay[i]->print(); std::cout << "\n";
	}
	
	return toPlay;
}

int Hand::getSize()
{
	return hand.size();
}

std::vector<std::shared_ptr<Card>> Hand::getHand()
{
	return hand;
}