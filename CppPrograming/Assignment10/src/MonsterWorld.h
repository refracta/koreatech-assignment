#pragma once
#include "Canvas.h"
#include "Monster.h"
#include "Matrix.h"
#include "Human.h"
#include <windows.h>
#include <conio.h>
#include "DeprecatedController.h"
#define DIM  40
#define MAXMONS 7
#define WASD_TO_DIRECTION(ch) (ch == 'a' ? Left : (ch == 'd' ? Right : (ch == 'w' ? Up : (ch == 's' ? Down : ch))))

class MonsterWorld {
	Matrix world;
	int xMax, yMax, nMon, nMove;
	Monster* pMon[MAXMONS];
	Canvas canvas;

	int& Map(int x, int y) { return world.elem(x, y); }
	bool isDone() { return countItems() == 0; }
	int countItems() {
		int nItems = 0;
		for (int y = 0; y < yMax; y++)
			for (int x = 0; x < xMax; x++)
				if (Map(x, y) > 0) nItems++;
		return nItems;
	}
	void print() {
		canvas.clear();
		for (int y = 0; y < yMax; y++)
			for (int x = 0; x < xMax; x++)
				if (Map(x, y) > 0) canvas.draw(x, y, "■");
		for (int i = 0; i < nMon; i++)
			pMon[i]->draw(canvas);
		canvas.print("[ Monster World (수학 기호 몬스터들의 세상) ]");

		cerr << " 전체 이동 횟수 = " << nMove << endl;
		cerr << " 남은 아이템 수 = " << countItems() << endl;
		for (int i = 0; i < nMon; i++)
			pMon[i]->print();
		Monster::printCount();
	}
	void checkStarvation()
	{

		for (int i = 0; i < nMon; i++)
		{
			if (pMon[i]->getEnergy() == 0)
			{
				delete  pMon[i];
				pMon[i] = pMon[nMon - 1];
				nMon--;
				cerr << "Monster 하나가 굶어죽습니다." << endl;
				getchar();
			}
		}
	}
public:
	MonsterWorld(int w, int h) : world(h, w), canvas(w, h), xMax(w), yMax(h) {
		nMon = 0;
		nMove = 0;
		for (int y = 0; y < yMax; y++)
			for (int x = 0; x < xMax; x++) Map(x, y) = 1;
	}
	~MonsterWorld() {
		for (int i = 0; i < nMon; i++)
			delete pMon[i];
	}
	void add(Monster* m) {
		if (nMon < MAXMONS) pMon[nMon++] = m;
	}
	void play(int maxwalk, int wait) {
		print();
		cerr << " 엔터를 누르세요...";
		getchar();

		for (int i = 0; i < maxwalk; i++) {
			Tuman* left = NULL;
			Tuman* right = NULL;
			for (int k = 0; k < nMon; k++) {
				pMon[k]->move(world.Data(), xMax, yMax);
				if (Tuman* tuman = dynamic_cast<Tuman*>(pMon[k])) {
					if (left == NULL) {
						left = tuman;
					} else {
						right = tuman;
					}
				}
			}
				
			if (kbhit()) {
				int ch = getche();
				if (ch == 224) {
					ch = getche();
					if (right != NULL) {
						right->move(world.Data(), xMax, yMax, ch);
					}
				}
				else {
					if (left != NULL) {
						left->move(world.Data(), xMax, yMax, WASD_TO_DIRECTION(ch));
					}
				}
			}

			nMove++;
			print();
			checkStarvation();
			if (isDone()) break;
			Sleep(wait);
		}
	}
};