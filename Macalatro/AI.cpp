#include "AI.hpp"
#include "Debug.hpp"

void AI::playTurn(GameState& gs)
{
	if (gs.turn == AITURN) Debug::log("============================\n", "[AI.cpp] The AI is thinking...\n", "============================");
	else Debug::log("[AI.cpp] X - It's not the AI's turn, but somehow, it's playing???");
	
	if (difficulty == DUMB)
	{
		// Just plays the first legal card(s), if it can't play anything, just draw.
		const std::vector<std::shared_ptr<Card>>& hand = gs.aiHand.getHand();
		std::vector<std::shared_ptr<Card>> playable;
		std::vector<std::shared_ptr<Card>> multiPlayable;
		std::shared_ptr<Card> topCard = gs.pile.getCard();

		// Check for playable cards
		for (int i = 0; i < hand.size(); i++)
		{
			if (topCard->getRank() == -1) playable.push_back(hand[i]); // When a Joker is down, you can play whatever you want
			if (topCard->getRank() == hand[i]->getRank()) playable.push_back(hand[i]); // By rank
			if (topCard->getSuit() == hand[i]->getSuit()) playable.push_back(hand[i]); // By suit
			if (hand[i]->getRank() == -1) playable.push_back(hand[i]); // Jokers are always playable
		}

		std::shared_ptr<Card> temporaryCard = std::make_shared<Card>(0, 0, 0, NONE, BASIC);
		std::vector<std::shared_ptr<Card>> temporaryCards;

		if (playable.size() < 1)
		{
			// Check for deck
			if (gs.aiDeck.getSize() == 0)
			{
				gs.gameOver = NOAIDECK;
			}
			else
			{
				gs.aiHand.addCard(gs.aiDeck.draw());
				gs.turn = PLAYERTURN;
			}
		}
		else if (playable.size() == 1)
		{
			temporaryCard = playable[0];
			gs.pile.addCard(gs.aiHand.playCard(playable[0]));
			gs.turn = temporaryCard->actAbility(gs);
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
			gs.pile.addMultiCard(gs.aiHand.playMultiCard(playable));
			for (int i = 0; i < temporaryCards.size(); i++)
			{
				gs.turn = temporaryCards[i]->actAbility(gs);
			}
		}
	}
	else if (difficulty == SMART)
	{
		// Priority queue-based gameplay.
		// Gathers the legal cards into multiple vectors and plays what's best.
		// Queue would look something like this:
		//		1. Basic cards with no ability
		//		2. Draw cards (2s, 3s, Jokers)
		//		3. Color changers (Aces)
		//		4. No cards? Just draw.
		// But, then, also bypassers:
		//		1. If Player has Macao (a single card) play a Draw card.
		//		2. If Player has Macao but you don't have Draw cards, change the color.
	}
	else if (difficulty == CHEATER)
	{
		gs.gameOver = AIWIN;
	}

	Debug::log("============================\n", "[AI.cpp] AI's turn is over\n", "============================");
}

void AI::changeDifficulty(Difficulty newDifficulty)
{
	difficulty = newDifficulty;
}