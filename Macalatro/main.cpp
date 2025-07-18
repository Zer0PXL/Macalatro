#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "Card.hpp"
#include "Hand.hpp"
#include "Deck.hpp"
#include "Table.hpp"
#include "Round.hpp"
#include "Debug.hpp"
#include "AI.hpp"
#include <memory>

enum Choice
{
	PLAY,
	PLAYMULTI,
	DRAW,
	INVALID
};

int main()
{
	// Game objects
	AI ai;
	Deck playerDeck = Deck(PLAYER);
	Deck aiDeck = Deck(OWNERAI);
	Hand playerHand;
	Hand aiHand;
	Table pile;
	Turn turn;
	GameOver gameOver = NOTOVER;

	// Player inputs
	Choice choice = INVALID;
	std::vector<std::shared_ptr<Card>> multiPlay;
	std::string stringInput = "";
	int intInput = 0;
	bool playing = true;

	// GameState and Round creation
	GameState gs{ playerDeck, aiDeck, playerHand, aiHand, pile, turn, gameOver };
	Round round = Round(gs);

	// Begining of game loop
	while (round.isGameOver(gs) == NOTOVER)
	{	
		Debug::logTurn(pile, playerHand, aiHand);
	
		if (turn == PLAYERTURN)
		{
			std::cout << "It's your turn!\n";

			playing = true;

			while (playing)
			{
				std::cout << "What would you like to do? play or draw: ";

				std::cin >> stringInput;

				if (stringInput == "debug") Debug::toggleDebugMode();
				if (stringInput == "cheats") Debug::toggleCheats();
				if (debugMode && stringInput == "difficulty=dumb") ai.changeDifficulty(DUMB);
				if (debugMode && stringInput == "difficulty=smart") ai.changeDifficulty(SMART);
				if (debugMode && stringInput == "difficulty=cheater") ai.changeDifficulty(CHEATER);

				if (stringInput == "play")
				{
					std::cout << "How many cards would you like to play? one or more: ";

					std::cin >> stringInput;

					if (stringInput == "one") choice = PLAY;
					else choice = PLAYMULTI;
				}
				else if (stringInput == "draw") choice = DRAW;

				switch (choice)
				{
				case PLAY:
					std::cout << "Play what? Give ID: ";
					std::cin >> intInput;

					for (int i = 0; i < playerHand.getSize(); i++)
					{
						if (playerHand.getHand()[i]->getID() == intInput)
						{
							// If the card's rank or suit matches the pile's top card, then play it.
							if (Card::isPlayable(playerHand.getHand()[i], pile.getCard()))
							{
								turn = playerHand.getHand()[i]->actAbility(gs);
								pile.addCard(playerHand.playCard(playerHand.getHand()[i]));
								playing = false;
							}
							break;
						}
					}

					if (playing) std::cout << "Couldn't play that card!\n";
					break;
				case PLAYMULTI:
					std::cout << "Play what? Give IDs, then type -1: ";

					do
					{
						std::cin >> intInput;
						for (int i = 0; i < playerHand.getSize(); i++)
						{
							if (playerHand.getHand()[i]->getID() == intInput)
							{
								turn = playerHand.getHand()[i]->actAbility(gs);
								multiPlay.push_back(playerHand.getHand()[i]);

								break;
							}
						}
					} while (intInput != -1);

					if (Card::isPlayable(multiPlay[0], pile.getCard()))
					{
						pile.addMultiCard(playerHand.playMultiCard(multiPlay));
						playing = false;
					}

					if (playing) std::cout << "Couldn't play those cards!\n";

					break;
				case DRAW:
				if (!(gs.playerDeck.getSize() < 1))
				{
					gs.playerHand.addCard(playerDeck.draw());
				}
				else
				{
					playing = false;
					gameOver = NOPLAYERDECK;
				}
					playing = false;
					turn = AITURN;
					break;
				}
			}
		}

		else
		{
			ai.playTurn(gs);
		}
	}

	round.endRound(gs);

	std::cout << "\nGame Over!\n";

    switch (round.isGameOver(gs))
    {
    case NOTOVER:
					std::cout << "! - Uhh... The game wasn't supposed to end...\n";
					break;
    case PLAYERWIN:
					std::cout << "The Player wins!\n";
					break;
    case AIWIN:
					std::cout << "The AI wins!\n";
					break;
    case NOPLAYERDECK:
					std::cout << "The Player ran out of cards! AI wins!\n";
					break;
    case NOAIDECK:
					std::cout << "The AI ran out of cards! Player wins!\n";
					break;
    default:
					std::cout << "X - Garbage data in GameOver???\n";
					break;
    }

	std::cout << "Press enter to continue...";
	std::cin >> stringInput;

	return 0;
}