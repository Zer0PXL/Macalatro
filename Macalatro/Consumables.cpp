#include "Consumables.hpp"
#include "Round.hpp"
#include <iostream>
#include <string>

void Consumables::useMAGIC(MAGIC magic, GameState& gs)
{
	int intInput = 0;
	std::string stringInput;
	
	switch (magic)
	{
	case EXTRA:
		for (int j = 1; j < 2; j++)
		{
			std::cout << "What card should become EXTRA? Give ID: ";
			std::cin >> intInput;

			for (int i = 0; i < gs.playerHand.getSize(); i++)
			{
				if (gs.playerHand.getHand()[i]->getID() == intInput) gs.playerHand.getHand()[i]->setEnhancement(EXTRAEN);
			}
		}
		break;

	default:
		std::cout << "X - That's not a real MAGIC card!";
	}
}