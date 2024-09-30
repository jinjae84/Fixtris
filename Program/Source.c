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
#define BLOCK_EMPTY 0
#define BLOCK_FILLED 1

int speed = 20;
int block_id = 0;
int pos_x = 10, pos_y = 5;
int rotation_state = 0;

// Buffers for double buffering
char buffer[BOARD_HEIGHT][BOARD_WIDTH];
int gameBoard[BOARD_HEIGHT][BOARD_WIDTH]; // Declare gameBoard
char blockModel[7][4][4] = {
    {
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 1},
        {0, 0, 0, 0}
    },
    {
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 1, 0, 0},
        {0, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 1, 1, 1},
        {0, 0, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 1, 1, 1},
        {0, 0, 0, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 1, 1, 0},
        {0, 0, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }
};

int GetRandomBlockId() {
    return rand() % 7;
}

void SetCurrentCursorPos(int x, int y) {
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void RemoveCursor(void) {
    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curInfo.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void InitializeBuffer() {
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            buffer[y][x] = ' '; // Initialize buffer with spaces
        }
    }
}

void PrintGameBoard() {
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            buffer[y][x] = (gameBoard[y][x] == BLOCK_EMPTY) ? ' ' : '■';
        }
    }
}

void ShowBlock(char block[4][4]) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (block[y][x] == 1) {
                buffer[pos_y + y][pos_x + x] = '■'; // Place block on buffer
            }
        }
    }
}

void DeleteBlock(char block[4][4]) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (block[y][x] == 1) {
                buffer[pos_y + y][pos_x + x] = ' '; // Clear block from buffer
            }
        }
    }
}

void DrawBuffer() {
    SetCurrentCursorPos(0, 0); // Set cursor to top-left
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            printf("%c", buffer[y][x]); // Draw from buffer to console
        }
        printf("\n"); // Move to the next line
    }
}

void FixBlockToBoard(char block[4][4]) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (block[y][x] == 1) {
                gameBoard[pos_y + y][pos_x + x] = BLOCK_FILLED;
            }
        }
    }
}

bool CanMove(int x, int y, char block[4][4]) {
    for (int block_y = 0; block_y < 4; block_y++) {
        for (int block_x = 0; block_x < 4; block_x++) {
            if (block[block_y][block_x] == 1) {
                int new_x = x + block_x;
                int new_y = y + block_y;

                // Check bounds
                if (new_x < 0 || new_x >= BOARD_WIDTH || new_y < 0 || new_y >= BOARD_HEIGHT) {
                    return false;
                }

                // Check for collision
                if (gameBoard[new_y][new_x] == BLOCK_FILLED) {
                    return false;
                }
            }
        }
    }
    return true;
}

void ShiftDown() {
    if (CanMove(pos_x, pos_y + 1, blockModel[block_id])) {
        DeleteBlock(blockModel[block_id]);
        pos_y += 1;
        ShowBlock(blockModel[block_id]);
        DrawBuffer(); // Update the console with the buffer
    }
    else {
        FixBlockToBoard(blockModel[block_id]);
        block_id = GetRandomBlockId();
        pos_x = 8; // 초기 x좌표
        pos_y = 0; // 초기 y좌표

        if (!CanMove(pos_x, pos_y, blockModel[block_id])) { // 0회전 상태 확인
            printf("Game Over\n");
            exit(0);
        }

        DrawBuffer(); // Update the console with the buffer
        ShowBlock(blockModel[block_id]);
    }
}

void ShiftLeft() {
    if (CanMove(pos_x - 1, pos_y, blockModel[block_id])) {
        DeleteBlock(blockModel[block_id]);
        pos_x -= 1; // x 좌표 감소
        ShowBlock(blockModel[block_id]);
        DrawBuffer();
    }
}

void ShiftRight() {
    if (CanMove(pos_x + 1, pos_y, blockModel[block_id])) {
        DeleteBlock(blockModel[block_id]);
        pos_x += 1; // x 좌표 증가
        ShowBlock(blockModel[block_id]);
        DrawBuffer();
    }
}

void RotateBlock() {
    int nextRotation = (rotation_state + 1) % 4; // 회전 상태 업데이트
    if (CanMove(pos_x, pos_y, blockModel[block_id][nextRotation])) {
        DeleteBlock(blockModel[block_id]);
        rotation_state = nextRotation; // 회전 상태 변경
        ShowBlock(blockModel[block_id][rotation_state]);
        DrawBuffer();
    }
}

void ProcessKeyInput() {
    int key;
    for (int i = 0; i < 20; i++) {
        if (_kbhit() != 0) {
            key = _getch();
            switch (key) {
            case LEFT:
                ShiftLeft();
                break;
            case RIGHT:
                ShiftRight();
                break;
            case UP:
                RotateBlock();
                break;
            case DOWN:
                ShiftDown();
                break;
            }
        }
        Sleep(speed);
    }
    ShiftDown();
}

int main() {
    RemoveCursor();
    srand((unsigned int)time(NULL));
    InitializeBuffer(); // Initialize buffer

    // Initialize game board
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (x == 0 || x == BOARD_WIDTH - 1 || y == BOARD_HEIGHT - 1)
                gameBoard[y][x] = BLOCK_FILLED; // Set borders
            else
                gameBoard[y][x] = BLOCK_EMPTY; // Initialize empty spaces
        }
    }

    block_id = GetRandomBlockId();
    SetCurrentCursorPos(pos_x, pos_y);
    ShowBlock(blockModel[block_id]);

    while (true) {
        PrintGameBoard(); // Prepare the game board for the buffer
        DrawBuffer(); // Draw the buffer to the console
        ProcessKeyInput();
    }

    return 0;
}
