#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <Windows.h>
#include <vector>

#include "Console.h"
#include "Dictionary.h"

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4

using namespace std;

//게임시작 화면
int DrawReadyGame() {
	system("cls");

	Console::gotoxy(10, 2);
	cout << "#   #   #   #   # ##### #   #   #   #   #";
	Console::gotoxy(10, 3);
	cout << "#   #  # #  ##  # #     ## ##  # #  ##  #";
	Console::gotoxy(10, 4);
	cout << "##### ##### # # # #  ## # # # ##### # # #";
	Console::gotoxy(10, 5);
	cout << "#   # #   # #  ## #   # #   # #   # #  ##";
	Console::gotoxy(10, 6);
	cout << "#   # #   # #   # ##### #   # #   # #   #";

	Console::gotoxy(15, 10);
	cout << "move : wasd, select : spacebar";

	int x = 20; int y = 13;

	Console::gotoxy(x, y);
	cout << "☞  게 임 시 작";
	Console::gotoxy(x, y + 1);
	cout << "    게 임 설 명";
	Console::gotoxy(x, y + 2);
	cout << "    게 임 종 료";

	//메뉴선택, 화살표 표시
	while (1) {
		int n = Console::keyControl();
		switch (n) {
		case UP: {
			if (y > 13) {
				Console::gotoxy(x, y);
				printf("   ");
				Console::gotoxy(x, --y);
				printf("☞");
			}
			break;
		}
		case DOWN: {
			if (y < 15) {
				Console::gotoxy(x, y);
				printf("   ");
				Console::gotoxy(x, ++y);
				printf("☞");
			}
			break;
		}
		case SUBMIT: {
			return y - 13; //게임시작=0 게임정보=1 게임종료=2
		}
		}
	}
}

//카테고리선택 화면
int DrawCategory() {
	system("cls");

	Console::gotoxy(22, 7);
	cout << "select category";

	int x = 22; int y = 10;

	Console::gotoxy(x, y);
	cout << "☞  FRUIT";
	Console::gotoxy(x, y + 1);
	cout << "    ANIMAL";
	Console::gotoxy(x, y + 2);
	cout << "    COUNTRY";
	Console::gotoxy(x, y + 3);
	cout << "    OOP CONCEPT";

	//메뉴 선택, 화살표 표시
	while (1) {
		int n = Console::keyControl();
		switch (n) {
		case UP: {
			if (y > 10) {
				Console::gotoxy(x, y);
				printf("   ");
				Console::gotoxy(x, --y);
				printf("☞");
			}
			break;
		}
		case DOWN: {
			if (y < 13) {
				Console::gotoxy(x, y);
				printf("   ");
				Console::gotoxy(x, ++y);
				printf("☞");
			}
			break;
		}
		case SUBMIT: {
			return y - 10;	// 0: FRUIT, 1: ANIMAL, 2: COUNTRY, 3: OOP CONCEPT
		}
		}
	}

}

//게임화면
void DrawStartGame(int life, int score, int correct, vector<string>& pastWord, int warning, int hint, string strOriginal, int category) {
	system("cls");

	Dictionary dic = Dictionary();

	Console::gotoxy(10, 1);
	for (int i = 0; i < (life + 1); i++) {
		if (i % 5 == 4) {
			printf("♥");
		}
		else {
			printf("♥");
		}
	}
	Console::gotoxy(10, 3);
	cout << "TotalScore = " << score;	//게임 합산 점수

	Console::gotoxy(30, 3);
	cout << "Correct = " << correct;	//맞춘 단어 개수

	Console::gotoxy(10, 8);
	cout << "History = ";
	for (int i = 0; i < static_cast<int>(pastWord.size()); ++i) {
		cout << pastWord[i] << " ";
	}

	Console::gotoxy(10, 11);
	cout << "Input = ";

	Console::gotoxy(1, 13);				//경고문
	if (warning == 1) {
		cout << "※ Please enter one letter at a time or the whole word ※";
	}

	//현재 진행중인 게임의 카테고리를 보여준다
	Console::gotoxy(10, 14);
	if (category == 0) {
		cout << "Category : FRUIT";
	}
	else if (category == 1) {
		cout << "Category : ANIMALS";
	}
	else if (category == 2) {
		cout << "Category : COUNTRY";
	}
	else if (category == 3) {
		cout << "Category : OOP CONCEPTS";
	}

	Console::gotoxy(10, 15);
	cout << "☞  Type 'hint' to return to the menu";
	Console::gotoxy(10, 16);
	cout << "☞  Type 'quit' to return to the menu";

	Console::gotoxy(10, 18);
	if (hint == 1) {
		dic.StatementHint(strOriginal);	//문장 힌트 출력
	}
	else if (hint == 2) {
		dic.AlphabetHint(strOriginal);	//알파벳 힌트 출력
	}
}

//게임정보 화면
void GameInfo() {
	system("cls");

	//pg 1
	Console::gotoxy(5, 2);
	cout << "What is hangman game?";
	Console::gotoxy(5, 4);
	cout << " Guess a word,phrase or sentence by suggesting";
	Console::gotoxy(5, 5);
	cout << "letters within a certain number of guesses.";

	Console::gotoxy(5, 7);
	cout << "How to Play?";
	Console::gotoxy(5, 8);
	cout << " Press an alphabet in keyboard and press 'Enter'.";
	Console::gotoxy(5, 9);
	cout << " You can play until you type 'quit'";


	Console::gotoxy(35, 13);
	cout << "☞  next page (1/2)";

	//pg 2
	while (1) {
		if (Console::keyControl() == SUBMIT) {
			system("cls");

			Console::gotoxy(5, 2);
			cout << "Life? ♥";
			Console::gotoxy(5, 3);
			cout << " Chance to type answer.";

			Console::gotoxy(5, 5);
			cout << "Total Score? ";
			Console::gotoxy(5, 6);
			cout << " If you match the whole word, score goes up.";
			Console::gotoxy(5, 7);
			cout << " If you don't get it right, goes down.";

			Console::gotoxy(5, 9);
			cout << "History?";
			Console::gotoxy(5, 10);
			cout << " History of your input answers.";

			Console::gotoxy(35, 13);
			cout << "☞  go back to MENU";

			while (1) {
				if (Console::keyControl() == SUBMIT) {
					break;
				}
			}
			break;
		}
	}
}

//게임 함수
void StartGame(int category) {

	int score = 0;
	int correct = 0;
	int warning = 0;
	int hint = 0;

	vector<string> pastWord;
	vector<string> strArr;

	Dictionary dic = Dictionary();
	dic.SetDictionary(strArr, category);

	while (true) {
		//1 play
		int num = 0;
		srand((unsigned int)time(NULL));
		num = rand() % static_cast<int>(strArr.size());

		string strQuestion;
		const string strOriginal = strArr[num];	//단어가 맞는지 정답확인용으로 저장
		const int originLen = static_cast<int>(strOriginal.length());

		//init
		for (int i = 0; i < originLen; ++i) {
			strQuestion += "_";
		}

		int life = originLen + 2;
		int count = 0;

		//1 question
		while (true) {

			DrawStartGame(life, score, correct, pastWord, warning, hint, strOriginal, category);

			//문제
			Console::gotoxy(10, 5);
			for (int i = 0; i < originLen; ++i) {
				cout << strQuestion[i] << " ";
			}
			cout << endl;

			//input
			Console::gotoxy(18, 11);
			string strInput;
			cin >> strInput;

			//quit 입력 -> 메뉴로 돌아간다.
			if (strInput == "quit") {
				hint = 0;
				return;
			}

			pastWord.push_back(strInput);

			//input : 알파벳
			if (strInput.length() == 1) {
				for (int i = 0; i < originLen; ++i) {
					if (strOriginal[i] == strInput[0]) {
						strQuestion[i] = strInput[0];
						count++;
						cout << count << endl;
					}
				}
				// 알파벳 하나씩 입력하여 단어를 맞출 경우 -> 점수 5점 카운트하고 다음단어로 넘어감
				if (count == originLen) {
					if (hint == 0) {		//hint 미사용 -> 5점 증가
						score += 5;
						correct += 1;
						pastWord.clear();	//init
						break;
					}
					else if (hint == 1) {
						score += 2;			//hint1(문장힌트) 사용 -> 2점 증가
						correct += 1;
						hint = 0;			//init
						pastWord.clear();
						break;
					}
					else if (hint == 2) {
						score += 3;			//hint2(알파벳힌트) 사용 -> 3점 증가
						correct += 1;
						hint = 0;			//init
						pastWord.clear();
						break;
					}
				}
			}
			//input : 단어
			else if (strInput.length() > 1) {
				if (strOriginal == strInput) {
					if (hint == 0) {
						score += 5;
						correct += 1;
						pastWord.clear();
						break;
					}
					else if (hint == 1) {
						score += 2;
						correct += 1;
						hint = 0;
						pastWord.clear();
						break;
					}
					else if (hint == 2) {
						score += 3;
						correct += 1;
						hint = 0;
						pastWord.clear();
						break;
					}
				}
				else {
					warning = 1;
				}
				if (strInput == "hint") {	//hint는 랜덤으로 받는다.
					hint = rand() % 2 + 1;
				}
			}

			if (hint == 0) {	//hint는 life를 깎지 않는다.
				life -= 1;
			}

			if (life < 0) {
				score -= 5;
				if (score < 0) {
					score = 0;
				}
				pastWord.clear();
				warning = 0;
				break;
			}
		}
	}
}



//메인 함수
int main(void) {

	Console::SetConsoleView();

	int selectMenu = 0;
	int selectCategory = -1;

	while (true) {
		selectMenu = DrawReadyGame();

		if (selectMenu == 0) {
			selectCategory = DrawCategory();
			if (-1 < selectCategory < 4) {	// 0: FRUIT, 1: ANIMAL, 2: COUNTRY, 3: OOP CONCEPT
				StartGame(selectCategory);
			}
		}
		else if (selectMenu == 1) {
			GameInfo();
		}
		else if (selectMenu == 2) {
			break;
		}
	}
	return 0;
}
