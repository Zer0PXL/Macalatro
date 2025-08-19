#include <random>
#include <iostream>
#include "Round.hpp"
#include "Hand.hpp"
#include "Chance.hpp"
#include "Debug.hpp"


Round::Round(GameState& gs)
{
	Debug::log("[Round.cpp] Starting round...");

	// Shuffle decks
	gs.playerDeck.shuffle();
	gs.aiDeck.shuffle();

	// Each player draws 5 cards
	if (gs.playerDeck.getSize() < 1)
	{
		gameOver = NOPLAYERDECK;
	}
	for (int i = 1; i <= 5; i++)
	{
		gs.playerHand.addCard(gs.playerDeck.draw());
		gs.aiHand.addCard(gs.aiDeck.draw());
	}

	// Flip a coin to determine first-goer
	if (Chance::chance(1, 2) == 1) gs.turn = PLAYERTURN;
	else gs.turn = AITURN;

	// Draw a card to the pile
	Debug::log("[Round.cpp] Drawing a card from the loser's deck...");
	if (gs.turn == PLAYERTURN) gs.pile.addCard(gs.aiDeck.draw());
	else gs.pile.addCard(gs.playerDeck.draw());
}

// Deprecated
// Turn Round::playTurn(Turn& turn)
/*{
	if (turn) Debug::log("[Round.cpp] It's the AI's turn");
	else Debug::log("[Round.cpp] It's the Player's turn");

	//std::vector<Card>& hand = (turn == PLAYERTURN) ? pHand.getHand() : aHand.getHand();
	const std::vector<std::shared_ptr<Card>>& hand = aHand.getHand();
	std::vector<std::shared_ptr<Card>> playable;
	std::vector<std::shared_ptr<Card>> multiPlayable;
	std::shared_ptr<Card> topCard = pile.getCard();

	// Check for playable cards
	for (int i = 0; i < hand.size(); i++)
	{
		if (topCard->getRank() == -1) playable.push_back(hand[i]); // When a Joker is down, you can play whatever you want
		if (topCard->getRank() == hand[i]->getRank()) playable.push_back(hand[i]); // By rank
		if (topCard->getSuit() == hand[i]->getSuit()) playable.push_back(hand[i]); // By suit
		if (hand[i]->getRank() == -1) playable.push_back(hand[i]); // Jokers are always playable
	}

	// Old debugging AI
	if (turn == PLAYERTURN)
	{
		// Old Player-AI debugging thing
		if (topCard.getRank() == -1)
		{
			pile.addCard(pHand.playCard(playable[0])); // If there's a Joker down, though, you can't play your whole goddamn hand...
		}
		else if (playable.size() < 1)
		{
			// Check for deck
			if (pDeck.getSize() == 0)
			{
				gameOver = NOPLAYERDECK;
			}
			else pHand.addCard(pDeck.draw());
		}
		else if (playable.size() == 1) pile.addCard(pHand.playCard(playable[0]));
		else if (playable.size() > 1)
		{
			int baseRank = playable[0].getRank();
			for (int i = 0; i < playable.size(); i++)
			{
				if (playable[i].getRank() == baseRank) multiPlayable.push_back(playable[i]);
			}
			pile.addMultiCard(pHand.playMultiCard(multiPlayable));
		}

		return AITURN;
	}
	else
	{
		std::shared_ptr<Card> temporaryCard = std::make_shared<Card>(0, 0, 0, NONE, BASIC);
		std::vector<std::shared_ptr<Card>> temporaryCards;

		if (playable.size() < 1)
		{
			// Check for deck
			if (aDeck.getSize() == 0)
			{
				gameOver = NOAIDECK;
			}
			else
			{
				aHand.addCard(aDeck.draw());
				turn = PLAYERTURN;
			}
		}
		else if (playable.size() == 1) 
		{
			temporaryCard = playable[0];
			pile.addCard(aHand.playCard(playable[0]));
            turn = temporaryCard->actAbility(pHand, aHand, pDeck, aDeck, pile, turn);
		}
		else if (playable.size() > 1) 
		{
			for (int i = 0; i < playable.size(); i++)
			{
				if (playable[0]->getRank() == playable[i]->getRank())
				{
					temporaryCards.push_back(playable[i]);
				}
			}
			pile.addMultiCard(aHand.playMultiCard(playable));
			for (int i = 0; i < temporaryCards.size(); i++)
			{
				turn = temporaryCards[i]->actAbility(pHand, aHand, pDeck, aDeck, pile, turn);
			}
		}

		Debug::log("[Round.cpp] AI's turn is over.");

		return turn;
	}
}*/

GameOver Round::isGameOver(GameState& gs)
{	
	if (gs.gameOver == NOTOVER)
	{
		if (gs.playerHand.getHand().size() == 0)
		{
			return PLAYERWIN;
		}
		else if (gs.aiHand.getHand().size() == 0)
		{
			return AIWIN;
		}
		else
		{
			return NOTOVER;
		}
	}
	else return gs.gameOver;
}

void Round::endRound(GameState& gs)
{
	int kings = 0;
	int jokers = 0;
	
	// Shuffle the cards in hand back into their respective decks
	for (int i = gs.playerHand.getSize() - 1; i >= 0; i--)
	{
		gs.playerDeck.addCard(gs.playerHand.getHand()[i]);
	}
	gs.playerHand.getHand().clear();
	
	for (int i = gs.aiHand.getSize() - 1; i >= 0; i--)
	{
		gs.aiDeck.addCard(gs.aiHand.getHand()[i]);
	}
	gs.aiHand.getHand().clear();

	// Checking for bonuses...
	for (int i = 0; i < gs.pile.getPile().size(); i++)
	{
		if (gs.pile.getPile()[i]->getOwner() == PLAYER)
		{
			if (gs.pile.getPile()[i]->getRank() == 13) kings++;
			if (gs.pile.getPile()[i]->getRank() == -1) jokers++;
		}
	}
	if (kings >= 4) gs.bonuses.royalty = true;
	if (jokers >= 2) gs.bonuses.jokester = true;

	for (int i = 0; i < gs.pile.getPile().size(); i++)
	{
		if (gs.pile.getPile()[i]->getOwner() == PLAYER) gs.playerDeck.addCard(gs.pile.getPile()[i]);
		else if (gs.pile.getPile()[i]->getOwner() == OWNERAI) gs.aiDeck.addCard(gs.pile.getPile()[i]);
	}

	// Clearing the pile and adding the cards back in their respective decks (check function)
	gs.pile.clearPile(gs.playerDeck, gs.aiDeck);
}

void Round::switchTurn(GameState& gs)
{
	if (gs.turn == PLAYERTURN) gs.turn = AITURN;
	else gs.turn = PLAYERTURN;
}

void Round::calculateBonuses(GameState& gs)
{
	std::cout << "=====================BREAKDOWN=====================" << std::endl;
	
	if (gs.variables.draws > 0)
	{
		gs.score += gs.variables.draws * 10;
		std::cout << "+ " << gs.variables.draws * 10 << " - Drawn cards\n";
	}
	if (gs.variables.skips > 0)
	{
		gs.score += gs.variables.skips * 50;
		std::cout << "+ " << gs.variables.skips * 50 << " - Skip cards\n";
	}
	if (gs.variables.attacks > 0)
	{
		gs.score += gs.variables.attacks * 10;
		std::cout << "+ " << gs.variables.attacks * 10 << " - Attack cards\n";
	}

	if (gs.gameOver == PLAYERWIN || gs.gameOver == NOAIDECK)
	{
		gs.score += 100;
		std::cout << "+ 100 - Won!\n";
	}

	if (gs.bonuses.comeback)
	{
		gs.score += 75;
		std::cout << "+ 75 - Comeback!\n";
	}
	if (gs.bonuses.jokester)
	{
		gs.score += 100;
		std::cout << "+ 100 - Jokester!\n";
	}
	if (gs.bonuses.royalty)
	{
		gs.score += 200;
		std::cout << "+ 200 - Royalty!\n";
	}
	if (gs.bonuses.noDraw)
	{
		gs.score += 150;
		std::cout << "+ 150 - No Deck Needed!\n";
	}
	if (gs.bonuses.oneManShow)
	{
		gs.score += 200;
		std::cout << "+ 200 - One Man Show!?\n";
	}
	if (gs.bonuses.oneShotWonder)
	{
		gs.score += 300;
		std::cout << "+ 300 - ONE SHOT WONDER!?\n";
	}
	if (!gs.bonuses.comeback &&
		!gs.bonuses.jokester &&
		!gs.bonuses.royalty &&
		!gs.bonuses.noDraw &&
		!gs.bonuses.oneManShow &&
		!gs.bonuses.oneShotWonder)
	{
		std::cout << "No bonuses :(\n";
	}

	std::cout << "===================================================" << std::endl;
}

void Round::resetBonuses(GameState& gs) {
	gs.bonuses = Bonuses();
	gs.variables = Variables();
}