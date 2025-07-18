#pragma once
#include "Deck.hpp"
#include "Hand.hpp"
#include "Table.hpp"
#include <memory>

extern int roundNum;

enum Turn
{
	PLAYERTURN,
	AITURN
};

enum GameOver
{
	NOTOVER,
	PLAYERWIN,
	AIWIN,
	NOPLAYERDECK,
	NOAIDECK
};

struct GameState
{
	Deck& playerDeck;
	Deck& aiDeck;
	Hand& playerHand;
	Hand& aiHand;
	Table& pile;
	Turn& turn;
	GameOver& gameOver;

	GameState(Deck& pDeck, Deck& aDeck, Hand& pHand, Hand& aHand, Table& _pile, Turn& _turn, GameOver gO) : playerDeck(pDeck), aiDeck(aDeck), playerHand(pHand), aiHand(aHand), pile(_pile), turn(_turn), gameOver(gO) {}
};

class Round
{
private:
	GameOver gameOver = NOTOVER;
public:
	Round(GameState& gs);
	GameOver isGameOver(GameState& gs);
	void endRound(GameState& gs);
};

