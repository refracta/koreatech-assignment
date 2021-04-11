#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>

#if defined(_WIN32) || defined(WIN32)
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#endif
#define BIG_RAND() (((long) rand() << 15) | rand())

using namespace std;

class Hangman {
	string	progress[88];
	string	problem;
	string	answer;
	string	guessed;
	int	nTries;
	const int maxTries = 7;

	void load(const char* progName = "HangmanProgress.txt") {
		ifstream fs(progName);
		if (fs) {
			getline(fs, progress[0]);
			for (int i = 0; i < 88; i++)
				getline(fs, progress[i]);
		}
	}
	void print() {
		system("cls");
		cout << "     <Hangman Game>\n";
		for (int i = 0; i < 11; i++)
			cout << '\t' << progress[nTries * 11 + i] << endl;
		cout << "\n\t" << answer;
		cout << "\n\n " << guessed;
	}
	int countMatched(char ch) {
		int nMatched = 0;
		for (int pos = -1; ; ) {
			pos = problem.find(ch, pos + 1);
			if (pos < 0) break;
			answer[pos] = ch;
			nMatched++;
		}
		return nMatched;
	}
	void guess() {
		char ch = getch();
		if (ch >= 'a' && ch <= 'z') {
			int pos = guessed.find(ch);
			if (pos < 0) {
				guessed[ch - 'a'] = ch;
				if (countMatched(ch) == 0) nTries++;
			}
		}
	}
public:
	void play(string prob) {
		load();
		problem = prob;
		answer = string(problem.length(), '-');
		guessed = string(26, '.');
		nTries = 0;
		while (nTries < maxTries && answer != problem) {
			print();
			guess();
		}
		print();
		cout << "\n\t" << ((nTries == maxTries) ? "실패" : "정답") << endl;
	}
	void playByWordList() {
		srand((unsigned int)time(NULL));
		ifstream fs("WordList.txt");
		if (fs) {
			string line;
			long maxLine;
			for (maxLine = 0; getline(fs, line); ++maxLine);
			long targetLine = BIG_RAND() % maxLine;
			fs.clear();
			fs.seekg(0);
			for (long i = 0; i < targetLine; i++) {
				getline(fs, line);
			}
			play(line);
		}
	}
};