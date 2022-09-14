#include "MonsterWorld.h"
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
	game.add(new Monster("Integral", "��", rand() % w, rand() % h));
	game.add(new Monster("PartialD", "��", rand() % w, rand() % h));
	game.add(new Monster("Delta", "��", rand() % w, rand() % h));
	game.add(new Monster("Del", "��", rand() % w, rand() % h));
	game.add(new Monster("Plus", "��", rand() % w, rand() % h));
	game.play(500, 10);
	printf("------���� ����-------------------\n");
	std::cout << std::endl << "Press ENTER to exit..."; fflush(stdin); getchar();
	return 0;
}