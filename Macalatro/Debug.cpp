#include "Debug.hpp"
#include "Table.hpp"
#include "Hand.hpp"
#include "AI.hpp"
#include <iostream>

bool debugMode = true;
bool cheats = true;
Difficulty difficulty = DUMB; //DUMB, SMART, CHEATER

void Debug::toggleDebugMode()
{
	if (debugMode) debugMode = false;
	else 
	{
		debugMode = true;
		Debug::log("i - Debug mode is now on.");
	}
}

void Debug::logTurn(Table& pile, Hand& playerHand, Hand& aiHand)
{
	//if (debugMode)
	//{
		std::cout << "Pile card: "; pile.getCard()->print();

		std::cout << "\n";

		if (cheats)
		{
			std::cout << "AI hand: ";
			for (int i = 0; i < aiHand.getHand().size(); i++)
			{
				aiHand.getHand()[i]->print();
			}

			std::cout << "\n";
		}

		std::cout << "Player hand: ";
		for (int i = 0; i < playerHand.getHand().size(); i++)
		{
			playerHand.getHand()[i]->print();
		}

		std::cout << "\n";
	//}
	//else return;
}

void Debug::log(std::string text1, std::string text2, std::string text3, std::string text4, std::string text5)
{
	if (debugMode) std::cout << text1 << text2 << text3 << text4 << text5 << std::endl;
	else return;
}

void Debug::logCardVector(std::vector<Card>& cards)
{
	std::cout << "i - Cards present in vector: \n";
	
	for (int i = 0; i < cards.size(); i++) cards[i].print();
}

void Debug::toggleCheats()
{
	if (cheats) cheats = false;
	else 
	{
		cheats = true;
		std::cout << "Cheater!\n";
	}
}

std::string Debug::abilityToString(Ability a)
{
	switch (a)
	{
	case BASIC:
		return "none";
		break;
	case DRAWABILITY:
		return "draw";
		break;
	case COLOR:
		return "color";
		break;
	case SKIP:
		return "skip";
		break;
	default:
		return "invalid?????";
		break;
	}
}