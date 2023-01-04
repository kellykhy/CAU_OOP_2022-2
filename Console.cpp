#include "console.h"

//�ܼ� ������ Ư�� ��ġ�� Ŀ���� �̵���Ű�� �Լ� �Դϴ�.
void Console::gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int Console::keyControl() {
	char temp = _getch();

	if (temp == 'w' || temp == 'W') {
		return UP;
	}
	else if (temp == 's' || temp == 'S') {
		return DOWN;
	}
	else if (temp == 'a' || temp == 'A') {
		return LEFT;
	}
	else if (temp == 'd' || temp == 'D') {
		return RIGHT;
	}
	else if (temp == ' ') {
		return SUBMIT;
	}
}

//�ܼ� ����
void Console::SetConsoleView() {
	system("mode con:cols=60 lines=20");
	system("title [HangManGame] by.Team10");
}