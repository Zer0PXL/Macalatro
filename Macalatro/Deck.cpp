#include "Deck.hpp"
#include "Card.hpp"
#include "Debug.hpp"
#include "Round.hpp"
#include <random>
#include <vector>
#include <iostream>
#include <chrono>

int ucid = 0;

std::shared_ptr<Card> Deck::draw()
{
	Debug::log("[Deck.cpp] Drawing a card...");

	if (cards.size() < 1)
	{
		Debug::log("[Deck.cpp] X - No cards in deck! Can't draw!");
	}

	std::shared_ptr<Card> drawn = cards.back();
	cards.pop_back();

	return drawn;
}

Deck::Deck(Owner owner)
{
	Debug::log("[Deck.cpp] Creating deck...");
	// Add all usual cards in deck
	for (int s = 0; s < 4; s++)
		for (int r = 1; r < 14; r++)
		{
			if (r == 1)
			{
				cards.push_back(std::make_shared<Card>(r, Card::intToSuit(s), ucid, owner, COLOR, NONE));
			}
			else if (r == 2 || r == 3 || r == -1)
			{
				cards.push_back(std::make_shared<Card>(r, Card::intToSuit(s), ucid, owner, DRAWABILITY, NONE));
			}
			else if (r == 4)
			{
				cards.push_back(std::make_shared<Card>(r, Card::intToSuit(s), ucid, owner, SKIP, NONE));
			}
			else
			{
				cards.push_back(std::make_shared<Card>(r, Card::intToSuit(s), ucid, owner, BASIC, NONE));
			}
			ucid++;

//			Debug::log("[Deck.cpp] Created this:");
//			cards.back()->print();
		}

	// Add jokers
	cards.push_back(std::make_shared<Card>(-1, BLACKJOKER, ucid, owner, DRAWABILITY, NONE));
	ucid++;
	cards.push_back(std::make_shared<Card>(-1, REDJOKER, ucid, owner, DRAWABILITY, NONE));
	ucid++;
}

void Deck::shuffle()
{
	int n = cards.size();
	auto now = std::chrono::high_resolution_clock::now();
	auto seed = now.time_since_epoch().count();
	std::mt19937 engine(seed);
	int j;

	for (int i = 0; i < n; i++)
	{
		std::uniform_int_distribution<int> dist(i, n - 1);
		j = dist(engine);
		std::swap(cards[i], cards[j]);
	}
}

void Deck::addCard(std::shared_ptr<Card> c)
{
	cards.push_back(c);
}

int Deck::getSize()
{
	return cards.size();
}