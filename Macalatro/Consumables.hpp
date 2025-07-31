#pragma once

struct GameState;

enum MAGIC
{
	EXTRA,
	GLUETUBE,
	LOVE,
	HATE,
	RICH,
	TREE,
	MORE,
	LESS,
	SWORD,
	SPEAR,
	SHIELD,
	PEEKABOO,
	BLANK,
	LOSTCRAYON,
	RIP,
	WILDACE,
	ADOLLAH,
	COINFLIP,
	SMOKEBOMB
};

class Consumables
{
private:

public:
	static void useMAGIC(MAGIC magic, GameState& gs);
};

