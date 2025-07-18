#include "Card.hpp"
#include "Debug.hpp"
#include "Chance.hpp"
#include "Round.hpp"
#include <iostream>
#include <string>

Card::Card(int r, Suit s, int id, Owner o, Ability a) : rank(r), suit(s), id(id), owner(o), ability (a) {}

void Card::print() const
{
	if (suit == 0) std::cout << id << " is a " << rank << " of Hearts belonging to " << owner << " with ability " << Debug::abilityToString(ability) << std::endl;
	else if (suit == 1) std::cout << id << " is a " << rank << " of Spades belonging to " << owner << " with ability " << Debug::abilityToString(ability) << std::endl;
	else if (suit == 2) std::cout << id << " is a " << rank << " of Diamonds belonging to " << owner << " with ability " << Debug::abilityToString(ability) << std::endl;
	else if (suit == 3) std::cout << id << " is a " << rank << " of Clubs belonging to " << owner << " with ability " << Debug::abilityToString(ability) << std::endl;
	else if (suit == 4) std::cout << id << " is a Black Joker belonging to " << owner << " with ability " << Debug::abilityToString(ability) << std::endl;
	else if (suit == 5) std::cout << id << " is a Red Joker belonging to " << owner << " with ability " << Debug::abilityToString(ability) << std::endl;
	else Debug::log("! - That card invalid af (as frick)");

	// Note to self, don't be a fucking idiot.
	/*if (suit == 0) { Debug::log(std::to_string(id), " is a ", std::to_string(rank), " of Hearts belonging to ", std::to_string(owner)); std::cout << std::endl; }
	else if (suit == 1) { Debug::log(std::to_string(id), " is a ", std::to_string(rank), " of Spades belonging to ", std::to_string(owner)); std::cout << std::endl; }
	else if (suit == 2) { Debug::log(std::to_string(id), " is a ", std::to_string(rank), " of Diamonds belonging to ", std::to_string(owner)); std::cout << std::endl; }
	else if (suit == 3) { Debug::log(std::to_string(id), " is a ", std::to_string(rank), " of Clubs belonging to ", std::to_string(owner)); std::cout << std::endl; }
	else if (suit == -1) { Debug::log(std::to_string(id), " is a Black Joker belonging to ", std::to_string(owner)); std::cout << std::endl; }
	else if (suit == -2) { Debug::log(std::to_string(id), " is a Red Joker belonging to ", std::to_string(owner)); std::cout << std::endl; }
	else Debug::log("! - That card invalid af (as frick)");*/
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

Turn Card::actAbility(GameState& gs)
{
	Hand* targetHand = &gs.playerHand;
	Deck* targetDeck = &gs.playerDeck;
	
	if (gs.turn == PLAYERTURN)
	{
		targetHand = &gs.aiHand;
		targetDeck = &gs.aiDeck;
	}
	
	switch (ability)
	{
	case DRAWABILITY:
		Debug::log("[Card.cpp] DRAWABILITY");
		Debug::log("[Card.cpp] Drawing as many cards as the rank of this card: ");
		print();
		switch (rank)
		{
		case 2:
			for (int i = 1; i <= 2; i++)
			{
				targetHand->addCard(targetDeck->draw());
			}
			break;
		case 3:
			for (int i = 1; i <= 3; i++)
			{
				targetHand->addCard(targetDeck->draw());
			}
			break;
		case -1:
			for (int i = 1; i <= 5; i++)
			{
				targetHand->addCard(targetDeck->draw());
			}
			break;
		default:
			std::cout << "X - Invalid rank for DRAWABILITY (how!?!)\n";
		}
		return gs.turn;
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

			gs.pile.addCard(std::make_shared<Card>(1, suitToChangeTo, 0, NONE, BASIC));

			return AITURN;
		}
		else
		{
			// Yeah, I'm not programming anything interesting rn. Later, when I'll have to make a proper AI.
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

			gs.pile.addCard(std::make_shared<Card>(1, randomSuit, 0, NONE, BASIC));

			return PLAYERTURN;
		}
		break;
	case SKIP:
		Debug::log("[Card.cpp] SKIP");
		if (owner == PLAYER) return PLAYERTURN;
		else if (owner == OWNERAI) return AITURN;
		else std::cout << "X - uh... SKIP ability called by invalid card with no owner?\n";
		break;
	default:
		Debug::log("[Card.cpp] BASIC or other ability card. Skipping...");
		if (gs.turn == PLAYERTURN) 
		{
			Debug::log("[Card.cpp] It's the Player's turn, so it'll OBVIOUSLY be the AI's turn next!");
			gs.turn = AITURN;
		}
		else gs.turn = PLAYERTURN;
		return gs.turn;
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