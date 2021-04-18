#include "MonsterWorld.h"
#include <time.h>
int main()
{
	srand((unsigned int)time(NULL));
	int w = 16, h = 8;

	MonsterWorld game(w, h);
	Monster m("Integral", "∫", rand() % w, rand() % h);
	game.add(m);
	game.add(Monster("PartialD", "∂", rand() % w, rand() % h));
	game.add(Monster("Delta", "Δ", rand() % w, rand() % h));
	game.add(Monster("Del", "∇", rand() % w, rand() % h));
	game.play(500, 10);
	printf("------게임 종료-------------------\n");
	std::cout << std::endl << "Press ENTER to exit..."; fflush(stdin); getchar(); getchar();
	return 0;
}