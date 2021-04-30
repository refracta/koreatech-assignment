#include "MonsterWorld.h"
#include "VariousMonsters.h"
#include <time.h>

int Monster::nMonster = 0;

void Monster::printCount() {
	cout << "  ��ü ������ �� : " << Monster::nMonster << endl;
}
int main()
{
	srand((unsigned int)time(NULL));
	int w = 20, h = 10;

	MonsterWorld game(w, h);
	game.add(new Monster("Plus", "��", rand() % w, rand() % h));
	game.add(new Zombie("Integral", "��", rand() % w, rand() % h));
	game.add(new Vampire("Delta", "��", rand() % w, rand() % h));
	game.add(new KGhost("Del", "��", rand() % w, rand() % h));
	game.add(new Smombi("Multiply", "��", rand() % w, rand() % h));
	game.add(new Siangshi("LTransform", "��", rand() % w, rand() % h));
	game.add(new BlinkSiangshi("Abs", "||", rand() % w, rand() % h));
	game.play(500, 10);
	printf("------���� ����-------------------\n");
	std::cout << std::endl << "Press ENTER to exit..."; fflush(stdin); getchar();
	return 0;
}