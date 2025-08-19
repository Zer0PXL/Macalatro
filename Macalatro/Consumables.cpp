#include "Consumables.hpp"
#include "Round.hpp"
#include "Chance.hpp"
#include <iostream>

MAGIC lastUsedMAGIC = INVALIDMAGIC;

void setEnhancement(Enhancement enhancement, int i, GameState& gs)
{
	int intInput = 0;
	bool foundIt = false;
	
	for (int j = 0; j < i; j++)
	{
		std::cout << "What card? Give ID: ";
		std::cin >> intInput;

		for (int i = 0; i < gs.playerHand.getSize(); i++)
		{
			if (gs.playerHand.getHand()[i]->getID() == intInput)
			{
				gs.playerHand.getHand()[i]->setEnhancement(enhancement);
				if (enhancement == SWORDEN || enhancement == SPEAREN) gs.playerHand.getHand()[i]->setAbility(DRAWABILITY);
				if (enhancement == SHIELDEN) gs.playerHand.getHand()[i]->setAbility(SKIP);
				foundIt = true;
				break;
			}
		}

		if (!foundIt)
		{
			std::cout << "Couldn't find it!\n";
			j--;
		}
	}
}

void setSuit(Suit suit, int i, GameState& gs)
{
	int intInput = 0;
	bool foundIt = false;

	for (int j = 0; j < i; j++)
	{
		std::cout << "What card? Give ID: ";
		std::cin >> intInput;

		for (int i = 0; i < gs.playerHand.getSize(); i++)
		{
			if (gs.playerHand.getHand()[i]->getID() == intInput)
			{
				gs.playerHand.getHand()[i]->setSuit(suit);
				foundIt = true;
				break;
			}
		}

		if (!foundIt)
		{
			std::cout << "Couldn't find it!\n";
			j--;
		}
	}
}

void Consumables::useMAGIC(MAGIC magic, GameState& gs)
{
	std::shared_ptr<Card> firstCard;
	std::shared_ptr<Card> secondCard;
	std::string stringInput;
	int intInput = 0;
	bool foundIt = false;
	int coin;
	int firstCardID;

	switch (magic)
	{
	case EXTRA:
		setEnhancement(EXTRAEN, 2, gs);
		lastUsedMAGIC = EXTRA;
		break;

	case GLUETUBE:
		setEnhancement(STICKY, 1, gs);
		lastUsedMAGIC = GLUETUBE;
		break;

	case LOVE:
		setSuit(HEARTS, 2, gs);
		lastUsedMAGIC = LOVE;
		break;

	case HATE:
		setSuit(SPADES, 2, gs);
		lastUsedMAGIC = HATE;
		break;

	case RICH:
		setSuit(DIAMONDS, 2, gs);
		lastUsedMAGIC = RICH;
		break;

	case TREE:
		setSuit(CLUBS, 2, gs);
		lastUsedMAGIC = TREE;
		break;

	case MORE:
		for (int j = 1; j < 2; j++)
		{
			std::cout << "What card? Give ID: ";
			std::cin >> intInput;

			for (int i = 0; i < gs.playerHand.getSize(); i++)
			{
				if (gs.playerHand.getHand()[i]->getID() == intInput)
				{
					gs.playerHand.getHand()[i]->setRank(gs.playerHand.getHand()[i]->getRank() + 1);
					foundIt = true;
					break;
				}
			}

			if (!foundIt)
			{
				std::cout << "Couldn't find it!\n";
				j--;
			}
		}
		lastUsedMAGIC = MORE;
		break;

	case LESS:

		for (int j = 1; j < 2; j++)
		{
			std::cout << "What card? Give ID: ";
			std::cin >> intInput;

			for (int i = 0; i < gs.playerHand.getSize(); i++)
			{
				if (gs.playerHand.getHand()[i]->getID() == intInput)
				{
					gs.playerHand.getHand()[i]->setRank(gs.playerHand.getHand()[i]->getRank() - 1);
					foundIt = true;
					break;
				}
			}

			if (!foundIt)
			{
				std::cout << "Couldn't find it!\n";
				j--;
			}
		}
		lastUsedMAGIC = LESS;
		break;

	case SWORD:
		setEnhancement(SWORDEN, 1, gs);
		lastUsedMAGIC = SWORD;
		break;

	case SPEAR:
		setEnhancement(SPEAREN, 1, gs);
		lastUsedMAGIC = SPEAR;
		break;

	case SHIELD:
		setEnhancement(SHIELDEN, 1, gs);
		lastUsedMAGIC = SHIELD;
		break;

	case PEEKABOO:
		std::cout << "Peek-a-boo! Here are the top three cards in your deck:\n";
		for (int i = 0; i <= 2; i++)
		{
			gs.playerDeck.getDeck()[gs.playerDeck.getSize() - i]->print();
		}
		lastUsedMAGIC = PEEKABOO;
		break;

	case BLANK:
		if (lastUsedMAGIC != INVALIDMAGIC && lastUsedMAGIC != BLANK)
		{
			useMAGIC(lastUsedMAGIC, gs);
			lastUsedMAGIC = BLANK;
		}
		else std::cout << "Can't used a BLANK card right now!\n";
		break;

	case LOSTCRAYON:
		std::cout << "Card to transform to: ";
		std::cin >> intInput;

		while (!foundIt)
		{
			for (int i = 0; i < gs.playerHand.getSize(); i++)
			{
				if (gs.playerHand.getHand()[i]->getID() == intInput)
				{
					firstCard = gs.playerHand.getHand()[i];
					firstCardID = firstCard->getID();
					foundIt = true;
					break;
				}
			}

			if (!foundIt)
			{
				std::cout << "Couldn't find it!\n";
			}
		}
		
		foundIt = false;

		std::cout << "Card to transform: ";
		std::cin >> intInput;

		while (!foundIt)
		{
			for (int i = 0; i < gs.playerHand.getSize(); i++)
			{
				if (gs.playerHand.getHand()[i]->getID() == intInput)
				{
					secondCard = gs.playerHand.getHand()[i];
					foundIt = true;
					break;
				}

				if (!foundIt)
				{
					std::cout << "Couldn't find it!\n";
				}
			}
		}

		*firstCard = *secondCard;
		firstCard->setID(firstCardID);

		lastUsedMAGIC = LOSTCRAYON;
		break;

	case RIP:
		std::cout << "Card to rip: ";
		std::cin >> intInput;

		while (!foundIt)
		{
			for (int i = 0; i < gs.playerHand.getSize(); i++)
			{
				if (gs.playerHand.getHand()[i]->getID() == intInput)
				{
					gs.playerHand.getHand().erase(gs.playerHand.getHand().begin() + i);
					foundIt = true;
					break;
				}

				if (!foundIt)
				{
					std::cout << "Couldn't find it!\n";
				}
			}
		}

		lastUsedMAGIC = RIP;
		break;

	case WILDACE:
		std::cout << "What suit? (hearts, spades, diamonds, clubs) ";
		std::cin >> stringInput;
		
		while (!foundIt)
		{
			if (stringInput == "hearts")
			{
				gs.pile.addCard(std::make_shared<Card>(1, HEARTS, 0, NOOWNER, BASIC, NONE));
				foundIt = true;
			}
			else if (stringInput == "spades")
			{
				gs.pile.addCard(std::make_shared<Card>(1, SPADES, 0, NOOWNER, BASIC, NONE));
				foundIt = true;
			}
			else if (stringInput == "diamonds")
			{
				gs.pile.addCard(std::make_shared<Card>(1, DIAMONDS, 0, NOOWNER, BASIC, NONE));
				foundIt = true;
			}
			else if (stringInput == "clubs")
			{
				gs.pile.addCard(std::make_shared<Card>(1, CLUBS, 0, NOOWNER, BASIC, NONE));
				foundIt = true;
			}
			else
			{
				std::cout << "Couldn't find it!\n";
			}
		}
		lastUsedMAGIC = WILDACE;
		break;

	case ADOLLAH:
		// Placeholder until money gets added
		lastUsedMAGIC = ADOLLAH;
		break;

	case COINFLIP:
		coin = Chance::chance(1, 2);

		if (coin == 2)
		{
			// Placeholder again
		}
		lastUsedMAGIC = COINFLIP;
		break;

	case SMOKEBOMB:
		gs.ai.smokeBomb();

		lastUsedMAGIC = SMOKEBOMB;
		break;

	default:
		std::cout << "X - That's not a real MAGIC card!";
	}
}