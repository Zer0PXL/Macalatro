#pragma once
#include "Deck.hpp"
#include "Hand.hpp"
#include "Table.hpp"
#include "AI.hpp"
#include <memory>

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

struct Bonuses
{
	bool speedster = false;
	bool jokester = false;
	bool royalty = false;
	bool noDraw = false;
	bool comeback = false;
	bool oneManShow = false;
	bool oneShotWonder = false;
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
	AI& ai;
	int& score;
	Bonuses& bonuses;

	GameState(Deck& pDeck, Deck& aDeck, Hand& pHand, Hand& aHand, Table& _pile, Turn& _turn, GameOver& gO, AI& AI, int& s, Bonuses& b) : playerDeck(pDeck), aiDeck(aDeck), playerHand(pHand), aiHand(aHand), pile(_pile), turn(_turn), gameOver(gO), ai(AI), score(s), bonuses(b) {}
};

class Round
{
private:
	GameOver gameOver = NOTOVER;
public:
	Round(GameState& gs);
	GameOver isGameOver(GameState& gs);
	void endRound(GameState& gs);
	static void switchTurn(GameState& gs);
	static void calculateBonuses(GameState& gs);
	static void scoreBreakdown(GameState& gs);
};

