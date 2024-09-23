#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 600
#define BLOCK_SIZE 30

int board[20][10] = { 0 };
int currentPiece[4][4];
int pieceX, pieceY;

void processInput()
{
	if (GetAsyncKeyState(VK_LEFT))
	{

	}
	if (GetAsyncKeyState(VK_RIGHT))
	{

	}
	if (GetAsyncKeyState('R'))
	{

	}
	if (GetAsyncKeyState('G'))
	{

	}
}

int life = 10;      // 목숨 갯수 (밸런스 보고 변경예정)
int score = 0;      // 기본 주어지는 점수 (남은 목숨에 따라 추가할 지 깎을지 고민)

int main()
{





	return 0;
}