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

int life = 10;      // ��� ���� (�뷱�� ���� ���濹��)
int score = 0;      // �⺻ �־����� ���� (���� ����� ���� �߰��� �� ������ ���)

int main()
{





	return 0;
}