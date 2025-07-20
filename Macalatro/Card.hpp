#pragma once
#include <memory>

struct GameState;
enum Turn;

enum Suit
{
	HEARTS,
	SPADES,
	DIAMONDS,
	CLUBS,
	BLACKJOKER,
	REDJOKER
};

enum Owner
{
	PLAYER,
	OWNERAI,
	NONE
};

enum Ability
{
	BASIC,
	DRAWABILITY,
	COLOR,
	SKIP
};

class Card
{
private:
	int rank;
	Suit suit;
	int id;
	Owner owner;
	Ability ability;
public:
	Card(int r, Suit s, int id, Owner o, Ability a);
	void print() const;
	int getSuit() const;
	void setSuit(Suit s);
	int getRank() const;
	void setRank(int r);
	int getID() const;
	Owner getOwner() const;
	void setOwner(Owner o);
	Ability getAbility() const;
	void setAbility(Ability a);
	static bool isPlayable(std::shared_ptr<Card> cardToPlay, std::shared_ptr<Card> pileCard);
	void actAbility(GameState& gs);
	static Suit intToSuit(int interger);
};