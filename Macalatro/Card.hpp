#pragma once
#include <memory>

struct GameState;
enum Turn;

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
	int suit;
	int id;
	Owner owner;
	Ability ability;
public:
	Card(int r, int s, int id, Owner o, Ability a);
	void print() const;
	int getSuit() const;
	void setSuit(int s);
	int getRank() const;
	void setRank(int r);
	int getID() const;
	Owner getOwner() const;
	void setOwner(Owner o);
	Ability getAbility() const;
	void setAbility(Ability a);
	static bool isPlayable(std::shared_ptr<Card> cardToPlay, std::shared_ptr<Card> pileCard);
	Turn actAbility(GameState& gs);
};