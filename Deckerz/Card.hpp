#pragma once
#include <memory>

struct GameState;

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
	NOOWNER
};

enum Ability
{
	BASIC,
	DRAWABILITY,
	COLOR,
	SKIP
};

enum Enhancement
{
	NONE,
	EXTRAEN,
	STICKY,
	SWORDEN,
	SPEAREN,
	SHIELDEN
};

class Card
{
private:
	int rank;
	Suit suit;
	int id;
	Owner owner;
	Ability ability;
	Enhancement enhancement;
public:
	Card(int r, Suit s, int id, Owner o, Ability a, Enhancement e);
	void print() const;
	int getSuit() const;
	void setSuit(Suit s);
	int getRank() const;
	void setRank(int r);
	int getID() const;
	void setID(int newID);
	Owner getOwner() const;
	void setOwner(Owner o);
	Ability getAbility() const;
	void setAbility(Ability a);
	static bool isPlayable(std::shared_ptr<Card> cardToPlay, std::shared_ptr<Card> pileCard);
	void actAbility(GameState& gs);
	static Suit intToSuit(int interger);
	Enhancement getEnhancement();
	void setEnhancement(Enhancement e);
	void actEnhancement(GameState& gs);
	void resetAbility();
};