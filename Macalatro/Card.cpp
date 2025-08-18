#include "Card.hpp"
#include "Debug.hpp"
#include "Chance.hpp"
#include "Round.hpp"
#include <iostream>
#include <string>

Card::Card(int r, Suit s, int id, Owner o, Ability a, Enhancement e) : rank(r), suit(s), id(id), owner(o), ability(a), enhancement(e) {}

void Card::print() const
{
	std::string ownerString = (owner == PLAYER ? "Player" : "AI");
	
	if (debugMode)
	{
		if (suit == HEARTS)
			std::cout << rank << " of Hearts (ID: " << id << ", Owner: " << ownerString << ", Ability: " << Debug::abilityToString(ability) << ", Enhancement: " << Debug::enhancementToString(enhancement) << ")" << std::endl;
		else if (suit == SPADES)
			std::cout << rank << " of Spades (ID: " << id << ", Owner: " << ownerString << ", Ability: " << Debug::abilityToString(ability) << ", Enhancement: " << Debug::enhancementToString(enhancement) << ")" << std::endl;
		else if (suit == DIAMONDS)
			std::cout << rank << " of Diamonds (ID: " << id << ", Owner: " << ownerString << ", Ability: " << Debug::abilityToString(ability) << ", Enhancement: " << Debug::enhancementToString(enhancement) << ")" << std::endl;
		else if (suit == CLUBS)
			std::cout << rank << " of Clubs (ID: " << id << ", Owner: " << ownerString << ", Ability: " << Debug::abilityToString(ability) << ", Enhancement: " << Debug::enhancementToString(enhancement) << ")" << std::endl;
		else if (suit == BLACKJOKER)
			std::cout << "Black Joker (ID: " << id << ", Owner: " << ownerString << ", Ability: " << Debug::abilityToString(ability) << ", Enhancement: " << Debug::enhancementToString(enhancement) << ")" << std::endl;
		else if (suit == REDJOKER)
			std::cout << "Red Joker (ID: " << id << ", Owner: " << ownerString << ", Ability: " << Debug::abilityToString(ability) << ", Enhancement: " << Debug::enhancementToString(enhancement) << ")" << std::endl;
		else
			std::cout << "Invalid card (ID: " << id << ")" << std::endl;
	}
	else
	{
		if (suit == HEARTS)
			std::cout << rank << " of Hearts (ID: " << id << ")" << std::endl;
		else if (suit == SPADES)
			std::cout << rank << " of Spades (ID: " << id << ")" << std::endl;
		else if (suit == DIAMONDS)
			std::cout << rank << " of Diamonds (ID: " << id << ")" << std::endl;
		else if (suit == CLUBS)
			std::cout << rank << " of Clubs (ID: " << id << ")" << std::endl;
		else if (suit == BLACKJOKER)
			std::cout << "Black Joker (ID: " << id << ")" << std::endl;
		else if (suit == REDJOKER)
			std::cout << "Red Joker (ID: " << id << ")" << std::endl;
		else
			std::cout << "Invalid card (ID: " << id << ")" << std::endl;
	}
}

int Card::getSuit() const
{
	return suit;
}

void Card::setSuit(Suit s)
{
	suit = s;
}

int Card::getRank() const
{
	return rank;
}

void Card::setRank(int r)
{
	rank = r;
}

int Card::getID() const
{
	return id;
}

Owner Card::getOwner() const
{
	return owner;
}

void Card::setOwner(Owner o)
{
	owner = o;
}

bool Card::isPlayable(std::shared_ptr<Card> cardToPlay, std::shared_ptr<Card> pileCard)
{
	Debug::log("[Card.cpp] Checking if these two cards are playable:");
	cardToPlay->print();
	pileCard->print();
	
	if (cardToPlay->getRank() == pileCard->getRank()) Debug::log("[Card.hpp] That card has the same rank as the card on the pile!");
	else if (cardToPlay->getSuit() == pileCard->getSuit()) Debug::log("[Card.hpp] That card has the same suit as the card on the pile!");
	else if (cardToPlay->getRank() == -1) Debug::log("[Card.hpp] That card is a Joker!");
	else if (pileCard->getRank() == -1) Debug::log("[Card.hpp] The pile card is a Joker!");
	else Debug::log("[Card.hpp] X - Unplayable.");
	
	if (cardToPlay->getRank() == pileCard->getRank() || // IF the card you're about to play has the same rank
		cardToPlay->getSuit() == pileCard->getSuit() || // OR the cards have the same suit
		cardToPlay->getRank() == -1 || // OR the card to play is a Joker
		pileCard->getRank() == -1) // OR the card on the pile is a Joker
	{
		return true; // Then, yeah, it's playable :thumbs up:
	}
	else return false; // Otherwise, you can't play random cards :sad:
}

Ability Card::getAbility() const
{
	return ability;
}

void Card::setAbility(Ability a)
{
	ability = a;
}

void Card::actAbility(GameState& gs)
{
	Hand* targetHand = &gs.playerHand;
	Deck* targetDeck = &gs.playerDeck;
	
	if (owner == PLAYER)
	{
		targetHand = &gs.aiHand;
		targetDeck = &gs.aiDeck;
	}

	switch (ability)
	{
	case DRAWABILITY:
		Debug::log("[Card.cpp] DRAWABILITY");
		switch (rank)
		{
		case 2:
			for (int i = 1; i <= 2; i++)
			{
				if (targetDeck->getSize() > 0)
				{
					targetHand->addCard(targetDeck->draw());
					if (owner == PLAYER) gs.variables.attacks++;
				}
				else
				{
					if (owner == OWNERAI)
					{
						gs.gameOver = NOPLAYERDECK;
					}
					else gs.gameOver = NOAIDECK;
				}
			}
			break;
		case 3:
			for (int i = 1; i <= 3; i++)
			{
				if (targetDeck->getSize() > 0)
				{
					targetHand->addCard(targetDeck->draw());
					if (owner == PLAYER) gs.variables.attacks++;
				}
				else
				{
					if (owner == OWNERAI)
					{
						gs.gameOver = NOPLAYERDECK;
					}
					else gs.gameOver = NOAIDECK;
				}
			}
			break;
		case -1:
			for (int i = 1; i <= 5; i++)
			{
				if (targetDeck->getSize() > 0)
				{
					targetHand->addCard(targetDeck->draw());
					if (owner == PLAYER) gs.variables.attacks++;
				}
				else
				{
					if (owner == OWNERAI)
					{
						gs.gameOver = NOPLAYERDECK;
					}
					else gs.gameOver = NOAIDECK;
				}
			}
			break;
		default:
			std::cout << "X - Invalid rank for DRAWABILITY (how!?!)\n";
		}

		if (owner == PLAYER) 
		{
			Debug::log("i - The Player should be next, since they played a draw card.");
			gs.turn = PLAYERTURN;
		}
		else gs.turn = AITURN;
		break;
	case COLOR:
		Debug::log("[Card.cpp] COLOR");
		if (owner == PLAYER)
		{
			std::string stringInput;
			Suit suitToChangeTo = HEARTS;
			std::cout << "What suit do you want? (hearts, spades, diamonds, clubs)";
			std::cin >> stringInput;

			if (stringInput == "hearts") suitToChangeTo = HEARTS;
			else if (stringInput == "spades") suitToChangeTo = SPADES;
			else if (stringInput == "diamonds") suitToChangeTo = DIAMONDS;
			else if (stringInput == "clubs") suitToChangeTo = CLUBS;
			else std::cout << "That's not a suit!";

			gs.pile.addCard(std::make_shared<Card>(1, suitToChangeTo, 0, NOOWNER, BASIC, NONE));
		}
		else
		{
			if (gs.ai.getDifficulty() == DUMB)
			{
				int randomChance = Chance::chance(0, 3);
				Suit randomSuit;
				switch (randomChance)
				{
				case 0:
					randomSuit = HEARTS;
					break;
				case 1:
					randomSuit = SPADES;
					break;
				case 2:
					randomSuit = DIAMONDS;
					break;
				case 3:
					randomSuit = CLUBS;
					break;
				default:
					randomSuit = HEARTS;
					std::cout << "X - Random chance broken???\n";
					break;
				}
				gs.pile.addCard(std::make_shared<Card>(1, randomSuit, 0, NOOWNER, BASIC, NONE));
			}
			else if (gs.ai.getDifficulty() == SMART)
			{
				Suit suitToChangeTo;
				switch (gs.ai.determineBestSuit())
				{
				case HEARTS:
					suitToChangeTo = HEARTS;
					break;
				case SPADES:
					suitToChangeTo = SPADES;
					break;
				case DIAMONDS:
					suitToChangeTo = DIAMONDS;
					break;
				case CLUBS:
					suitToChangeTo = CLUBS;
					break;
				default:
					suitToChangeTo = HEARTS;
					std::cout << "X - Invalid best suit!\n";
					break;
				}
				gs.pile.addCard(std::make_shared<Card>(1, suitToChangeTo, 0, NOOWNER, BASIC, NONE));
			}
		}
		break;
	case SKIP:
		Debug::log("[Card.cpp] SKIP");
		if (owner == PLAYER)
		{
			gs.turn = PLAYERTURN;
			//gs.score += 50;
		}
		else if (owner == OWNERAI) gs.turn = AITURN;
		else std::cout << "X - uh... SKIP ability called by invalid card with no owner?\n";
		break;
	default:
		Debug::log("[Card.cpp] BASIC or other ability card. Skipping...");
		return;
		break;
	}
}

Suit Card::intToSuit(int interger)
{
	switch (interger)
	{
	case 0:
		return HEARTS;
		break;
	case 1:
		return SPADES;
		break;
	case 2:
		return DIAMONDS;
		break;
	case 3:
		return CLUBS;
		break;
	default:
		std::cout << "X - Invalid interger for intToSuit()\n";
		return HEARTS;
		break;
	}
}

Enhancement Card::getEnhancement()
{
	return enhancement;
}

void Card::setEnhancement(Enhancement e)
{
	enhancement = e;
}

void Card::actEnhancement(GameState& gs)
{
	if (enhancement == EXTRAEN)
	{
		gs.score += 10;
	}
}