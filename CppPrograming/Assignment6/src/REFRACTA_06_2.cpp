#include "Hangman.h"
int main()
{
	Hangman	game;
	game.playByWordList();
	std::cout << std::endl << "Press ENTER to exit..."; fflush(stdin); getchar(); getchar();
}