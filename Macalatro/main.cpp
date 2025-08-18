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
#include "Consumables.hpp"
#include <memory>

#ifdef DEBUG
bool debugMode = true;
bool cheats = true;
#else
bool debugMode = false;
bool cheats = false;
#endif

enum Choice
{
	PLAY,
	PLAYMULTI,
	DRAW,
	INVALID,
	BYPASS
};

int main()
{
	std::cout << "Macalatro CLI v1.1\n";
	
	// Game objects
	AI ai;
	Deck playerDeck = Deck(PLAYER);
	Deck aiDeck = Deck(OWNERAI);
	Hand playerHand;
	Hand aiHand;
	Table pile;
	Turn turn;
	GameOver gameOver = NOTOVER;
	int turnNr = 0;

	// Player inputs
	Choice choice = INVALID;
	std::vector<std::shared_ptr<Card>> multiPlay;
	std::string stringInput = "";
	int intInput = 0;
	bool playing = true;
	int score = 0;
	Bonuses bonuses;
	Variables variables;

	// GameState and Round creation
	GameState gs{ playerDeck, aiDeck, playerHand, aiHand, pile, turn, gameOver, ai, score, bonuses, variables };
	Round round = Round(gs);
	Round::resetBonuses(gs);

	// Begining of game loop
	while (round.isGameOver(gs) == NOTOVER)
	{	
		turnNr++;
		
		Debug::logTurn(gs);
	
		if (turn == PLAYERTURN)
		{
			Round::switchTurn(gs);

			std::cout << "It's your turn!\n";

			playing = true;

			while (playing)
			{
				std::cout << "What would you like to do? play or draw: ";

				std::cin >> stringInput;

				if (stringInput == "debug") 
				{
					Debug::toggleDebugMode();
					choice = INVALID;
				}
				if (stringInput == "cheats") 
				{
					Debug::toggleCheats();
					choice = INVALID;
				}
				if (debugMode && stringInput == "difficulty=dumb") 
				{
					gs.ai.changeDifficulty(DUMB);
					choice = INVALID;
				}
				if (debugMode && stringInput == "difficulty=smart") 
				{
					gs.ai.changeDifficulty(SMART);
					choice = INVALID;
				}
				if (debugMode && stringInput == "difficulty=cheater") 
				{
					gs.ai.changeDifficulty(CHEATER);
					choice = INVALID;
				}
				if (debugMode && stringInput == "logturn") 
				{
					Debug::logTurn(gs);
					choice = INVALID;
				}
				if (debugMode && stringInput == "iwinbtw")
				{
					gs.gameOver = PLAYERWIN;
					choice = BYPASS;
				}
				if (debugMode && stringInput == "useExtra")
				{
					Consumables::useMAGIC(EXTRA, gs);
				}

				if (stringInput == "play") choice = PLAYMULTI;
				else if (stringInput == "draw") choice = DRAW;

				switch (choice)
				{

				case PLAYMULTI:
					std::cout << "Play what? Give IDs, then type -1: ";

					do
					{
						std::cin >> intInput;
						for (int i = 0; i < gs.playerHand.getSize(); i++)
						{
							if (gs.playerHand.getHand()[i]->getID() == intInput)
							{
								gs.playerHand.getHand()[i]->actAbility(gs);
								gs.playerHand.getHand()[i]->actEnhancement(gs);
								multiPlay.push_back(playerHand.getHand()[i]);

								break;
							}
						}
					} while (intInput != -1);

					if (!multiPlay.empty())
					{
						gs.playerHand.playCards(multiPlay, gs);
						playing = false;
					}

					if (playing) std::cout << "Couldn't play those cards!\n";

					break;
				case DRAW:
					if (!(gs.playerDeck.getSize() < 1))
					{
						gs.playerHand.addCard(playerDeck.draw());
						gs.variables.draws++;
						gs.bonuses.noDraw = false;
					}
					else
					{
						gs.gameOver = NOPLAYERDECK;
					}
					playing = false;
					break;
				case BYPASS:
					playing = false;
					break;
				}
			}
		}
		else
		{
			Round::switchTurn(gs);
			gs.ai.playTurn(gs);
		}

		if (gs.playerHand.getSize() >= 10)
		{
			gs.bonuses.comeback = true;
		}

	}

	if (turnNr > 1) gs.bonuses.oneShotWonder = false;
	if (turnNr > 5) gs.bonuses.speedster = false;

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

	Round::calculateBonuses(gs);


	std::cout << "Your score!" << std::endl;
	std::cout << "=============================\n| " << gs.score << "|\n=============================\n";

	std::cout << "Press any letter (then enter) to continue...";
	std::cin >> stringInput;

	return 0;
}