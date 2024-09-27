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
    return rand() % 4; // 0부터 3까지의 랜덤 블록 ID 반환
}

char blockModel[7][4][4][4] =
{
	{ // T모양 블럭
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
	{    // 번개 블럭
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
	{   // 번개 블럭 반대
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
	{   // 1자형 블럭
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
	{   // L자형 블럭
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
	{   // L자형 블럭 반대
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
	{   // 네모 블럭
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

int gameBoard[BOARD_HEIGHT][BOARD_WIDTH] = {  // 세로 15+1(아래벽)칸, 가로 10+2(양쪽 벽)칸  
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
            SetCurrentCursorPos(x * 2, y); // 콘솔에서는 x 좌표를 2배로 늘려야 합니다.
            if (gameBoard[y][x] == 0)
                printf("  "); // 빈 공간 출력
            else
                printf("■"); // 블록이 있는 부분 출력
        }
    }
}





void ShowBlock(char block[4][4])
{
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            SetCurrentCursorPos((pos_x + x) * 2, pos_y + y); // 블록 위치 설정
            if (block[y][x] == 1)
            {
                printf("■");
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
            SetCurrentCursorPos((pos_x + x) * 2, pos_y + y); // 블록 위치 설정
            if (block[y][x] == 1)
            {
                printf("  "); // 블록을 지움
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
				gameBoard[pos_y + y][(pos_x / 2) + x] = 1;  // 블록을 게임판에 복사
			}
		}
	}
}

void ShiftDown()
{
	if (CanMove(pos_x, pos_y + 1, blockModel[block_id])) { // 1칸 아래로 이동할 수 있는지 확인
		DeleteBlock(blockModel[block_id]);
		pos_y += 1; // 1칸 아래로 이동
		PrintGameBoard(); // 게임판을 먼저 그린다
		SetCurrentCursorPos(pos_x, pos_y);
		ShowBlock(blockModel[block_id]);
	}
	else {
		FixBlockToBoard(blockModel[block_id]); // 블록을 게임판에 고정
		block_id = GetRandomBlockId(); // 새로운 블록 ID를 랜덤으로 가져온다
		pos_x = 8; // 새로운 블록의 시작 X 위치 (중앙)
		pos_y = 0; // 새로운 블록의 시작 Y 위치 (위쪽에서 시작)

		// 새로운 블록이 게임 보드에 겹치지 않는지 확인
		if (!CanMove(pos_x, pos_y, blockModel[block_id])) {
			printf("Game Over\n");
			exit(0);
		}

		PrintGameBoard(); // 게임판을 먼저 그린다
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
				// 블록의 위치가 게임 보드 밖인지 확인
				if (new_x / 2 + x < 0 || new_x / 2 + x >= BOARD_WIDTH || new_y + y >= BOARD_HEIGHT) {
					return false; // 벽 또는 보드 경계를 넘으면 이동 불가
				}
				// 블록이 이미 고정된 다른 블록과 겹치는지 확인
				if (gameBoard[new_y + y][new_x / 2 + x] == 1) {
					return false; // 다른 블록과 겹치면 이동 불가
				}
			}
		}
	}
	return true; // 모두 유효하면 이동 가능
}

void RotateBlock()
{
    int temp = block_id / 4;    //블럭 종류 저장
    int tempid = block_id + 1;  //다음으로 보여줄 블록 아이디
    if (temp + 1 == tempid / 4) { //다른 종류의 블록의 경우 인덱스 초기화 
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
            case LEFT:	// 왼쪽 방향키
                ShiftLeft();
                break;
            case RIGHT:	// 오른쪽 방향키
                ShiftRight();
                break;
            case UP:	// 위쪽 방향키
                RotateBlock();
                break;
            case DOWN: // 아래 방향키
                ShiftDown(); // 아래로 두 칸씩 이동
                break;
            }
        }
        Sleep(speed);
    }
    ShiftDown();
}
int main()
{
    RemoveCursor();  // 커서 제거
    srand((unsigned int)time(NULL)); // 랜덤 시드 초기화

    // 게임 보드 초기화
    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            if (x == 0 || x == BOARD_WIDTH - 1 || y == BOARD_HEIGHT - 1)
                gameBoard[y][x] = 1;  // 경계는 블록으로 막음
            else
                gameBoard[y][x] = 0;  // 나머지는 빈 공간
        }
    }

    // 첫 블록 생성
    block_id = GetRandomBlockId();
    SetCurrentCursorPos(pos_x, pos_y);
    ShowBlock(blockModel[block_id]);

    while (TRUE)
    {
        ProcessKeyInput();  // 사용자 입력 처리
    }

    getchar();
    return 0;
}



