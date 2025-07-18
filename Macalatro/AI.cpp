#include "AI.hpp"
#include "Debug.hpp"

Suit AI::determineBestSuit()
{
	// Determine the bestSuit
	if (heartCards.size() >= spadeCards.size() &&
		heartCards.size() >= diamondCards.size() &&
		heartCards.size() >= clubCards.size())
		return HEARTS;
	else if (spadeCards.size() >= heartCards.size() &&
		spadeCards.size() >= diamondCards.size() &&
		spadeCards.size() >= clubCards.size())
		return SPADES;
	else if (diamondCards.size() >= heartCards.size() &&
		diamondCards.size() >= spadeCards.size() &&
		diamondCards.size() >= clubCards.size())
		return DIAMONDS;
	else if (clubCards.size() >= heartCards.size() &&
		clubCards.size() >= spadeCards.size() &&
		clubCards.size() >= diamondCards.size())
		return CLUBS;
	else
	{
		std::cout << "[AI.cpp] X - The AI somehow doesn't have a best color!\n";
		return HEARTS;
	}
}

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

		std::shared_ptr<Card> temporaryCard = std::make_shared<Card>(0, HEARTS, 0, NONE, BASIC);
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
		//		1. Skip cards (4s)
		//		2. Basic cards with no ability
		//		3. Draw cards (2s, 3s, Jokers)
		//		4. Color changers (Aces)
		//		5. No cards? Just draw.
		// But, then, also bypassers:
		//		1. If Player has Macao (a single card) play a Draw card.
		//		2. If Player has Macao but you don't have Draw cards, change the color.

		heartCards.clear();
		spadeCards.clear();
		diamondCards.clear();
		clubCards.clear();
		bestSuit.clear();

		std::vector<std::shared_ptr<Card>> jokerCards;

		std::vector<std::shared_ptr<Card>> skipCards;
		std::vector<std::shared_ptr<Card>> basicCards;
		std::vector<std::shared_ptr<Card>> drawCards;
		std::vector<std::shared_ptr<Card>> colorCards;

		// Split cards per color and if they're Jokers
		for (int i = 0; i < gs.aiHand.getSize(); i++)
		{
			if (Card::isPlayable(gs.aiHand.getHand()[i], gs.pile.getCard()))
			{
				switch (gs.aiHand.getHand()[i]->getSuit())
				{
				case HEARTS:
					heartCards.push_back(gs.aiHand.getHand()[i]);
					break;
				case SPADES:
					spadeCards.push_back(gs.aiHand.getHand()[i]);
					break;
				case DIAMONDS:
					diamondCards.push_back(gs.aiHand.getHand()[i]);
					break;
				case CLUBS:
					clubCards.push_back(gs.aiHand.getHand()[i]);
					break;
				default:
					jokerCards.push_back(gs.aiHand.getHand()[i]);
					break;
				}
			}
		}

		// Determine the bestSuit (the color with the most cards)
		switch (determineBestSuit())
		{
		case HEARTS:
			bestSuit = heartCards;
			break;
		case SPADES:
			bestSuit = spadeCards;
			break;
		case DIAMONDS:
			bestSuit = diamondCards;
			break;
		case CLUBS:
			bestSuit = clubCards;
			break;
		}

		// Don't forget the Jokers!
		for (int i = 0; i < jokerCards.size(); i++)
		{
			drawCards.push_back(jokerCards[i]);
		}

		// Split the cards of the biggest color based on ability
		for (int i = 0; i < bestSuit.size(); i++)
		{
			switch (bestSuit[i]->getAbility())
			{
			case SKIP:
				skipCards.push_back(bestSuit[i]);
				break;
			case DRAWABILITY:
				drawCards.push_back(bestSuit[i]);
				break;
			case COLOR:
				colorCards.push_back(bestSuit[i]);
				break;
			default:
				basicCards.push_back(bestSuit[i]);
				break;
			}
		}

		// ======== BYPASSERS ========
		// If the Player has Macao, AI should attempt to mess up the Player's lead.
		if (gs.playerHand.getSize() < 2 && !drawCards.empty()) 
		{
			gs.turn = drawCards[0]->actAbility(gs);
			gs.pile.addMultiCard(gs.aiHand.playMultiCard(drawCards));
		}
		else if (gs.playerHand.getSize() < 2 && !colorCards.empty()) 
		{
			gs.turn = colorCards[0]->actAbility(gs);
			gs.pile.addMultiCard(gs.aiHand.playMultiCard(colorCards));
		}
		// Play based on the priority queue
		else if (!skipCards.empty()) 
		{
			gs.turn = skipCards[0]->actAbility(gs);
			gs.pile.addMultiCard(gs.aiHand.playMultiCard(skipCards));
		}
		else if (!basicCards.empty()) 
		{
			gs.turn = basicCards[0]->actAbility(gs);
			gs.pile.addMultiCard(gs.aiHand.playMultiCard(basicCards));
		}
		else if (!drawCards.empty()) 
		{
			gs.turn = drawCards[0]->actAbility(gs);
			gs.pile.addMultiCard(gs.aiHand.playMultiCard(drawCards));
		}
		else if (!colorCards.empty()) 
		{
			gs.turn = colorCards[0]->actAbility(gs);
			gs.pile.addMultiCard(gs.aiHand.playMultiCard(colorCards));
		}
		else 
		{
			gs.aiHand.addCard(gs.aiDeck.draw());
			gs.turn = PLAYERTURN;
		}

		jokerCards.clear();
		skipCards.clear();
		basicCards.clear();
		drawCards.clear();
		colorCards.clear();
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