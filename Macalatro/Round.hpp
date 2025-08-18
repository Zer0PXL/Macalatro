#pragma once
#include "Deck.hpp"
#include "Hand.hpp"
#include "Table.hpp"
#include "AI.hpp"
#include "Turn.hpp"
#include <memory>

enum GameOver
{
	NOTOVER,
	PLAYERWIN,
	AIWIN,
	NOPLAYERDECK,
	NOAIDECK
};

struct Variables
{
	int draws = 0;
	int attacks = 0;
	int skips = 0;
};

struct Bonuses
{
	bool speedster = true;
	bool jokester = false;
	bool royalty = false;
	bool noDraw = true;
	bool comeback = false;
	bool oneManShow = true;
	bool oneShotWonder = true;
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
	Variables& variables;

	GameState(Deck& pDeck, Deck& aDeck, Hand& pHand, Hand& aHand, Table& _pile, Turn& _turn, GameOver& gO, AI& AI, int& s, Bonuses& b, Variables& vars) : playerDeck(pDeck), aiDeck(aDeck), playerHand(pHand), aiHand(aHand), pile(_pile), turn(_turn), gameOver(gO), ai(AI), score(s), bonuses(b), variables(vars) {}
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
	static void resetBonuses(GameState& gs);
};

