#pragma once
#include "Monster.h"
#include <conio.h>
#include "DeprecatedController.h"
enum Direction { Left = 75, Right = 77, Up = 72, Down = 80 };

class Human : public Monster {
public:
	Human(string n = "미래인류", string i = "♀", int px = 0, int py = 0)
		: Monster(n, i, px, py) {}
	virtual ~Human() { cout << " [Human   ]"; }
	virtual int getDirKey() { return kbhit() && getche() == 224 ? getche() : 0; }
	virtual void move(int** map, int maxx, int maxy) {
		char ch = getDirKey();
		if (ch == Left) x--;
		else if (ch == Right) x++;
		else if (ch == Up) y--;
		else if (ch == Down) y++;
		else return;
		clip(maxx, maxy);
		eat(map);
	}
};

class Tuman : public Human {
protected:
	int dirKey = 0;
private:
	void setDirKey(int ch) { 
		dirKey = ch;
	}
public:
	Tuman(string n = "미래투맨", string i = "♂", int px = 0, int py = 0): Human(n, i, px, py){ }
	~Tuman() { cout << " [Tuman   ]"; }
	virtual int getDirKey() { return dirKey; }
	virtual void move(int** map, int maxx, int maxy, char ch) {
		setDirKey(ch);
		Human::move(map, maxx, maxy);
		setDirKey(0);
	}
};