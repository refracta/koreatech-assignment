#pragma once
#include "Monster.h"

class Zombie : public Monster {
public:
	Zombie(string n = "ÇãÁ¢Á»ºñ", string i = "¡×", int x = 0, int y = 0)
		: Monster(n, i, x, y) {}
	virtual ~Zombie() { cout << " Zombie"; }
};

class Vampire : public Monster {
public:
	Vampire(string n = "¹ìÆÄÀÌ¾î", string i = "¡Ú", int x = 0, int y = 0)
		: Monster(n, i, x, y) {}
	virtual ~Vampire() { cout << " Vampire"; }

	virtual void move(int** map, int maxx, int maxy) {
		int dir = rand() % 4;
		if (dir == 0) x--;
		else if (dir == 1) x++;
		else if (dir == 2) y--;
		else y++;
		clip(maxx, maxy);
		eat(map);
	}
};

class KGhost : public Monster {
public:
	KGhost(string n = "Ã³³à±Í½Å", string i = "¢¾", int x = 0, int y = 0)
		: Monster(n, i, x, y) {}
	virtual ~KGhost() { cout << " KGhost"; }

	virtual void move(int** map, int maxx, int maxy) {
		x = rand() % maxx;
		y = rand() % maxy;
		clip(maxx, maxy);
		eat(map);
	}
};

class Jiangshi : public Monster {
protected:
	bool	bHori;
public:
	Jiangshi(string n = "´ë·ú°­½Ã", string i = "¡ê", int x = 0, int y = 0, bool bH = true)
		: Monster(n, i, x, y), bHori(bH) {}
	virtual ~Jiangshi() { cout << " Jiangshi"; }

	virtual void move(int** map, int maxx, int maxy) {
		int dir = rand() % 2;
		int jump = rand() % 2 + 1;
		if (bHori) x += ((dir == 0) ? -jump : jump);
		else y += ((dir == 0) ? -jump : jump);
		clip(maxx, maxy);
		eat(map);
	}
};

class Smombi : public Monster {
public:
	Smombi(string n = "½º¸öºñ", string i = "¢Ã", int x = 0, int y = 0)
		: Monster(n, i, x, y) {}
	virtual ~Smombi() { cout << " Smombi"; }

	virtual void move(int** map, int maxx, int maxy) {
		x += (rand() % 2) * 2 - 1;
		y += (rand() % 2) * 2 - 1;
		clip(maxx, maxy);
		eat(map);
	}
};

class Siangshi : public Jiangshi {
protected:
	int moveCount = 0;
	int actionPeroid;
public:
	Siangshi(string n = "¼§½Ã", string i = "¢¼", int x = 0, int y = 0, bool bH = true, int aP = 50)
		: Jiangshi(n, i, x, y, bH), actionPeroid(aP) {}
	virtual ~Siangshi() { cout << " Siangshi"; }

	virtual void moveCountAction(int** map, int maxx, int maxy) {
		bHori = !bHori;
	}

	virtual void move(int** map, int maxx, int maxy) {
		if (++moveCount % (actionPeroid + 1) == 0) {
			moveCountAction(map, maxx, maxy);
		}
		 Jiangshi::move(map, maxx, maxy);
	}
};

class BlinkSiangshi : public Siangshi {
public:
	BlinkSiangshi(string n = "Á¡¸ê¼§½Ã", string i = "¢»", int x = 0, int y = 0, bool bH = true, int aP = 50)
		: Siangshi(n, i, x, y, bH, aP) {}
	virtual ~BlinkSiangshi() { cout << " BlinkSiangshi"; }

	virtual void moveCountAction(int** map, int maxx, int maxy) {
		Siangshi::moveCountAction(map, maxx, maxy);
		x = rand() % maxx;
		x = rand() % maxy;
	}
};