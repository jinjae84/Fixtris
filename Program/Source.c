#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <stdbool.h>
#include <stdlib.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define BOARD_WIDTH 20
#define BOARD_HEIGHT 30

int speed = 20;
int block_id = 0;
int pos_x = 10, pos_y = 5;

int GetRandomBlockId()
{
    return rand() % 4; // 0���� 3������ ���� ��� ID ��ȯ
}

char blockModel[7][4][4][4] =
{
	{ // T��� ��
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{0,1,1,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{0,1,0,0}
		}
	},
	{    // ���� ��
		{
			{0,0,0,0},
			{0,1,1,0},
			{1,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{1,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,1,0,0}
		}
	},
	{   // ���� �� �ݴ�
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{1,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{1,0,0,0}
		}
	},
	{   // 1���� ��
		{
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,1},
			{0,0,0,0}
		},
		{
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,1},
			{0,0,0,0}
		}
	},
	{   // L���� ��
		{
			{0,0,0,0},
			{1,0,0,0},
			{1,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0},
			{1,0,0,0},
			{1,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,1,0},
			{0,0,1,0},
			{0,0,0,0}
		},
		{
			{0,1,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{0,0,0,0}
		}
	},
	{   // L���� �� �ݴ�
		{
			{0,0,0,0},
			{0,0,1,0},
			{1,1,1,0},
			{0,0,0,0}
		},
		{
			{1,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,1,0},
			{1,0,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		}
	},
	{   // �׸� ��
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		}
	}
};

int gameBoard[BOARD_HEIGHT][BOARD_WIDTH] = {  // ���� 15+1(�Ʒ���)ĭ, ���� 10+2(���� ��)ĭ  
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1}
};

void SetCurrentCursorPos(int x, int y)
{
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void RemoveCursor(void)
{
    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curInfo.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}
// COORD GetCurrentCursorPos(void)
// {
//     COORD curPoint;
//     CONSOLE_SCREEN_BUFFER_INFO curInfo;
// 
//     GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
//     curPoint.X = curInfo.dwCursorPosition.X;
//     curPoint.Y = curInfo.dwCursorPosition.Y;
// 
//     return curPoint;
// }

void ClearScreen()
{
    system("cls");
}

void PrintGameBoard()
{
    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            SetCurrentCursorPos(x * 2, y); // �ֿܼ����� x ��ǥ�� 2��� �÷��� �մϴ�.
            if (gameBoard[y][x] == 0)
                printf("  "); // �� ���� ���
            else
                printf("��"); // ����� �ִ� �κ� ���
        }
    }
}





void ShowBlock(char block[4][4])
{
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            SetCurrentCursorPos((pos_x + x) * 2, pos_y + y); // ��� ��ġ ����
            if (block[y][x] == 1)
            {
                printf("��");
            }
        }
    }
}
void DeleteBlock(char block[4][4])
{
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            SetCurrentCursorPos((pos_x + x) * 2, pos_y + y); // ��� ��ġ ����
            if (block[y][x] == 1)
            {
                printf("  "); // ����� ����
            }
        }
    }
}

void FixBlockToBoard(char block[4][4])
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (block[y][x] == 1)
			{
				gameBoard[pos_y + y][(pos_x / 2) + x] = 1;  // ����� �����ǿ� ����
			}
		}
	}
}

void ShiftDown()
{
	if (CanMove(pos_x, pos_y + 1, blockModel[block_id])) { // 1ĭ �Ʒ��� �̵��� �� �ִ��� Ȯ��
		DeleteBlock(blockModel[block_id]);
		pos_y += 1; // 1ĭ �Ʒ��� �̵�
		PrintGameBoard(); // �������� ���� �׸���
		SetCurrentCursorPos(pos_x, pos_y);
		ShowBlock(blockModel[block_id]);
	}
	else {
		FixBlockToBoard(blockModel[block_id]); // ����� �����ǿ� ����
		block_id = GetRandomBlockId(); // ���ο� ��� ID�� �������� �����´�
		pos_x = 8; // ���ο� ����� ���� X ��ġ (�߾�)
		pos_y = 0; // ���ο� ����� ���� Y ��ġ (���ʿ��� ����)

		// ���ο� ����� ���� ���忡 ��ġ�� �ʴ��� Ȯ��
		if (!CanMove(pos_x, pos_y, blockModel[block_id])) {
			printf("Game Over\n");
			exit(0);
		}

		PrintGameBoard(); // �������� ���� �׸���
		SetCurrentCursorPos(pos_x, pos_y);
		ShowBlock(blockModel[block_id]);
	}
}
void ShiftLeft()
{
    if (CanMove(pos_x - 2, pos_y, blockModel[block_id])) {
        DeleteBlock(blockModel[block_id]);
        pos_x -= 2;
        PrintGameBoard();
        SetCurrentCursorPos(pos_x, pos_y);
        ShowBlock(blockModel[block_id]);
    }
}
void ShiftRight()
{
    if (CanMove(pos_x + 2, pos_y, blockModel[block_id]))
    {
        DeleteBlock(blockModel[block_id]);
        pos_x += 2;
        PrintGameBoard();
        SetCurrentCursorPos(pos_x, pos_y);
        ShowBlock(blockModel[block_id]);
    }
}



int CanMove(int new_x, int new_y, char block[4][4])
{
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (block[y][x] == 1) {
				// ����� ��ġ�� ���� ���� ������ Ȯ��
				if (new_x / 2 + x < 0 || new_x / 2 + x >= BOARD_WIDTH || new_y + y >= BOARD_HEIGHT) {
					return false; // �� �Ǵ� ���� ��踦 ������ �̵� �Ұ�
				}
				// ����� �̹� ������ �ٸ� ��ϰ� ��ġ���� Ȯ��
				if (gameBoard[new_y + y][new_x / 2 + x] == 1) {
					return false; // �ٸ� ��ϰ� ��ġ�� �̵� �Ұ�
				}
			}
		}
	}
	return true; // ��� ��ȿ�ϸ� �̵� ����
}

void RotateBlock()
{
    int temp = block_id / 4;    //�� ���� ����
    int tempid = block_id + 1;  //�������� ������ ��� ���̵�
    if (temp + 1 == tempid / 4) { //�ٸ� ������ ����� ��� �ε��� �ʱ�ȭ 
        tempid -= 4;
    }
    DeleteBlock(blockModel[block_id]);
    block_id = tempid;
    ShowBlock(blockModel[block_id]);
}
void ProcessKeyInput()
{
    int key;
    for (int i = 0; i < 20; i++)
    {
        if (_kbhit() != 0)
        {
            key = _getch();
            switch (key)
            {
            case LEFT:	// ���� ����Ű
                ShiftLeft();
                break;
            case RIGHT:	// ������ ����Ű
                ShiftRight();
                break;
            case UP:	// ���� ����Ű
                RotateBlock();
                break;
            case DOWN: // �Ʒ� ����Ű
                ShiftDown(); // �Ʒ��� �� ĭ�� �̵�
                break;
            }
        }
        Sleep(speed);
    }
    ShiftDown();
}
int main()
{
    RemoveCursor();  // Ŀ�� ����
    srand((unsigned int)time(NULL)); // ���� �õ� �ʱ�ȭ

    // ���� ���� �ʱ�ȭ
    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            if (x == 0 || x == BOARD_WIDTH - 1 || y == BOARD_HEIGHT - 1)
                gameBoard[y][x] = 1;  // ���� ������� ����
            else
                gameBoard[y][x] = 0;  // �������� �� ����
        }
    }

    // ù ��� ����
    block_id = GetRandomBlockId();
    SetCurrentCursorPos(pos_x, pos_y);
    ShowBlock(blockModel[block_id]);

    while (TRUE)
    {
        ProcessKeyInput();  // ����� �Է� ó��
    }

    getchar();
    return 0;
}



