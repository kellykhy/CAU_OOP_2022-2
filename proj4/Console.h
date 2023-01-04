#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <Windows.h>
#include <vector>	// C++ vectror
#include <fstream>	// C++ ÆÄÀÏÀÔÃâ·Â

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4

class Console {
public:
	static void gotoxy(int x, int y);
	static int keyControl();
	static void SetConsoleView();
};
