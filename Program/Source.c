#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

#define kbhit _kbhit   // ���־�Ʃ���
#define getch _getch   // ���־�Ʃ���

#define LEFT    75 // ���� ȭ��ǥ Ű���� ��
#define RIGHT   77 // ������ ȭ��ǥ Ű 
#define UP      72 // ���� ȭ��ǥ Ű , ��� ȸ�� ��Ű��
#define DOWN    80 // �Ʒ��� ȭ��ǥ Ű, �� ���� �Ʒ��� �̵�
#define SPACE   32 // �����̽� ��, �Ʒ��� �����߸���
#define p       112 // �Ͻ� ���� 
#define P       80 // �Ͻ� ����
#define ESC     27 // ���� �߰��� ����ϱ� 

#define false 0
#define true 1

#define ACTIVE_BLOCK -2 // �����ǹ迭�� ����� ����� ���µ� 
#define CEILLING -1     // ����� �̵��� �� �ִ� ������ 0 �Ǵ� ���� ������ ǥ�� 
#define EMPTY 0         // ����� �̵��� �� ���� ������ ����� ǥ�� 
#define WALL 1
#define INACTIVE_BLOCK 2 // �̵��� �Ϸ�� ��ϰ� 

#define MAIN_X 16       //������ ����ũ�� 
#define MAIN_Y 24       //������ ����ũ�� 
#define MAIN_X_ADJ 18    //������ ��ġ���� 
#define MAIN_Y_ADJ 4    //������ ��ġ���� 

#define STATUS_X_ADJ MAIN_X_ADJ+MAIN_X+1 // ���� ���� ǥ��

int STATUS_Y_GOAL; //GOAL ����ǥ����ġY ��ǥ ���� 
int STATUS_Y_LEVEL; //LEVEL ����ǥ����ġY ��ǥ ����
int STATUS_Y_SCORE; //SCORE ����ǥ����ġY ��ǥ ����

int blocks[7][4][4][4] = {
{{0,0,0,0,
  0,1,1,0,
  0,1,1,0,
  0,0,0,0},
 {0,0,0,0,
  0,1,1,0,
  0,1,1,0,
  0,0,0,0},
 {0,0,0,0,
  0,1,1,0,
  0,1,1,0,
  0,0,0,0},
 {0,0,0,0,
  0,1,1,0,
  0,1,1,0,
  0,0,0,0}},
{{0,0,0,0,
  0,0,0,0,
  1,1,1,1,
  0,0,0,0},
 {0,1,0,0,
  0,1,0,0,
  0,1,0,0,
  0,1,0,0},
 {0,0,0,0,
  0,0,0,0,
  1,1,1,1,
  0,0,0,0},
 {0,1,0,0,
  0,1,0,0,
  0,1,0,0,
  0,1,0,0}},
{{0,0,0,0,
  1,1,0,0,
  0,1,1,0,
  0,0,0,0},
 {0,0,0,0,
  0,0,1,0,
  0,1,1,0,
  0,1,0,0},
 {0,0,0,0,
  1,1,0,0,
  0,1,1,0,
  0,0,0,0},
 {0,0,0,0,
  0,0,1,0,
  0,1,1,0,
  0,1,0,0}},
{{0,0,0,0,
  0,1,1,0,
  1,1,0,0,
  0,0,0,0},
 {0,0,0,0,
  1,0,0,0,
  1,1,0,0,
  0,1,0,0},
 {0,0,0,0,
  0,1,1,0,
  1,1,0,0,
  0,0,0,0},
 {0,0,0,0,
  1,0,0,0,
  1,1,0,0,
  0,1,0,0}},
{{0,0,0,0,
  0,0,1,0,
  1,1,1,0,
  0,0,0,0},
 {0,0,0,0,
  1,1,0,0,
  0,1,0,0,
  0,1,0,0},
 {0,0,0,0,
  0,0,0,0,
  1,1,1,0,
  1,0,0,0},
 {0,0,0,0,
  0,1,0,0,
  0,1,0,0,
  0,1,1,0}},
{{0,0,0,0,
  1,0,0,0,
  1,1,1,0,
  0,0,0,0},
 {0,0,0,0,
  0,1,0,0,
  0,1,0,0,
  1,1,0,0},
 {0,0,0,0,
  0,0,0,0,
  1,1,1,0,
  0,0,1,0},
 {0,0,0,0,
  0,1,1,0,
  0,1,0,0,
  0,1,0,0}},
{{0,0,0,0,
  0,1,0,0,
  1,1,1,0,
  0,0,0,0},
 {0,0,0,0,
  0,1,0,0,
  0,1,1,0,
  0,1,0,0},
 {0,0,0,0,
  0,0,0,0,
  1,1,1,0,
  0,1,0,0},
 {0,0,0,0,
  0,1,0,0,
  1,1,0,0,
  0,1,0,0}}
};

int b_type;     //��� ���� 
int b_rotation; //��� ȸ���� 
int b_type_next;//���� ��ϰ� 

int main_org[MAIN_Y][MAIN_X]; //�������� ������ �����ϴ� �迭 ����Ϳ� ǥ���Ŀ� main_cpy�� ����� 
int main_cpy[MAIN_Y][MAIN_X]; //�� maincpy�� �������� ����Ϳ� ǥ�õǱ� ���� ������ ������ ���� 
//main�� ��ü�� ��� ����Ϳ� ǥ������ �ʰ�(�̷��� �ϸ� ����Ͱ� �����Ÿ�) 
//main_cpy�� �迭�� ���ؼ� ���� �޶��� ���� ����Ϳ� ��ħ 

int bx, by; //�̵����� ����� �����ǻ��� x,y��ǥ�� ���� 

int key;    //Ű����� �Է¹��� Ű���� ���� 

int speed;  //��������ӵ� 
int level;  //���� level 
int level_goal; //���������� �Ѿ�� ���� ��ǥ���� 
int cnt;    //���� �������� ������ �� ���� ���� 
int score;  //���� ���� 
int last_score = 0; //�������������� 
int best_score = 0; //�ְ�������� 

int new_block_on = 0;   //���ο� ���� �ʿ����� �˸��� flag 
int crush_on = 0;       //���� �̵����� ����� �浹�������� �˷��ִ� flag 
int level_up_on = 0;    //���������� ����(���� ������ǥ�� �Ϸ�Ǿ�����) �˸��� flag 
int space_key_on = 0;   //hard drop�������� �˷��ִ� flag 

void title(); //���ӽ���ȭ�� 
void reset(); //������ �ʱ�ȭ 
void reset_main();  //���� ������(main_org[][]�� �ʱ�ȭ)
void reset_main_cpy(); //copy ������(main_cpy[][]�� �ʱ�ȭ)
void draw_map();    //���� ��ü �������̽��� ǥ�� 
void draw_main();   //�������� �׸� 
void new_block();   //���ο� ����� �ϳ� ���� 
void check_key();   //Ű����� Ű�� �Է¹��� 
void drop_block();  //����� �Ʒ��� ����Ʈ�� 
int check_crush(int bx, int by, int rotation); //bx, by��ġ�� rotationȸ������ ���� ��� �浹 �Ǵ� 
void move_block(int dir); //dir�������� ����� ������ 
void check_line();  //���� ����á������ �Ǵ��ϰ� ���� 
void check_level_up(); //������ǥ�� �޼��Ǿ������� �Ǵ��ϰ� levelup��Ŵ 
void check_game_over(); //���ӿ������� �Ǵ��ϰ� ���ӿ����� ���� 
void pause();       //������ �Ͻ�������Ŵ 

void setColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void resetColor()
{
    setColor(7);
}

void gotoxy(int x, int y) { //gotoxy�Լ� 
    COORD pos = { 2 * x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE; //Ŀ���� ����� �Լ��� ���Ǵ� ������ 
void setcursortype(CURSOR_TYPE c) { //Ŀ���� ����� �Լ� 
    CONSOLE_CURSOR_INFO CurInfo;

    switch (c) {
    case NOCURSOR:
        CurInfo.dwSize = 1;
        CurInfo.bVisible = FALSE;
        break;
    case SOLIDCURSOR:
        CurInfo.dwSize = 100;
        CurInfo.bVisible = TRUE;
        break;
    case NORMALCURSOR:
        CurInfo.dwSize = 20;
        CurInfo.bVisible = TRUE;
        break;
    }
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

int main() {
    int i;

    srand((unsigned)time(NULL));
    setcursortype(NOCURSOR); //Ŀ�� ���� 
    title();
    reset();

    while (1) {
        for (i = 0; i < 5; i++) { //����� ��ĭ�������µ��� 5�� Ű�Է¹��� �� ���� 
            check_key(); //Ű�Է�Ȯ�� 
            draw_main(); //ȭ���� �׸� 
            Sleep(speed); //���Ӽӵ����� 
            if (crush_on && check_crush(bx, by + 1, b_rotation) == false) Sleep(100);
            //����� �浹���ΰ�� �߰��� �̵��� ȸ���� �ð��� ���� 
            if (space_key_on == 1) { //�����̽��ٸ� �������(hard drop) �߰��� �̵��� ȸ���Ҽ� ���� break; 
                space_key_on = 0;
                break;
            }
        }
        drop_block();       // ����� ��ĭ ���� 
        check_level_up();   // �������� üũ 
        check_game_over();  //���ӿ����� üũ 
        if (new_block_on == 1) new_block(); // �� �� flag�� �ִ� ��� ���ο� �� ���� 
    }
}

void title() {
    int x = 14;  //Ÿ��Ʋȭ���� ǥ�õǴ� x��ǥ 
    int y = 7;  //Ÿ��Ʋȭ���� ǥ�õǴ� y��ǥ 
    int cnt;    //Ÿ��Ʋ �������� ���� ����  


    gotoxy(x, y + 0); printf("�ޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡ�"); Sleep(100);
    gotoxy(x, y + 1); printf("�ޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡ�"); Sleep(100);
    gotoxy(x, y + 2); printf("�ޡޡ�����ޡ����ޡ�����ޡ���ޡޡ�ޡ����ޡ�"); Sleep(100);
    gotoxy(x, y + 3); printf("�ޡޡޡޡ�ޡޡޡ�ޡޡޡޡޡޡ�ޡޡޡ�ޡޡ�ޡ�ޡ�ޡޡޡޡ�"); Sleep(100);
    gotoxy(x, y + 4); printf("�ޡޡޡޡ�ޡޡޡ����ޡޡޡ�ޡޡޡ���ޡޡ�ޡ����ޡ�"); Sleep(100);
    gotoxy(x, y + 5); printf("�ޡޡޡޡ�ޡޡޡ�ޡޡޡޡޡޡ�ޡޡޡ�ޡޡ�ޡ�ޡޡޡޡ�ޡ�"); Sleep(100);
    gotoxy(x, y + 6); printf("�ޡޡޡޡ�ޡޡޡ����ޡޡޡ�ޡޡޡ�ޡޡ�ޡ�ޡ����ޡ�"); Sleep(100);
    gotoxy(x, y + 7); printf("�ޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡ�"); Sleep(100);
    gotoxy(x, y + 8); printf("�ޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡ�"); Sleep(100);
    
    
    

    for (cnt = 0;; cnt++) { // cnt�� 1�� ������Ű�鼭 ��� �ݺ�
        if (kbhit()) break; // Ű�Է��� ������ ���ѷ��� ���� 
        if (cnt % 200 == 0)
        {
            setColor(6);
            gotoxy(x + 10 , y + 11); printf("Press Any Key to Start");
        }       //cnt�� 200���� ������ �������� ���� ǥ�� 
        if ((cnt % 200 - 100) == 0) { gotoxy(x + 10 , y + 11); printf("                                   "); } //�� ī��Ʈ���� 100ī��Ʈ �������� ���� ���� 
        
        Sleep(10); // 0.01�� ����  
    }

    while (kbhit()) getch(); // ���ۿ� ����� Ű ���� ����
}

void reset() {
    FILE* file = fopen("score.dat", "rt");  // ������ ���� ���� 
    if (file == 0) { best_score = 0; }      // ������ ���� �������� �ְ� ������ 0���� �ʱ�ȭ
    else {
        fscanf(file, "%d", &best_score); // �ְ� ������ ���� 
        fclose(file);
    }

    level = 1;
    score = 0;
    level_goal = 1000;
    key = 0;
    crush_on = 0;
    cnt = 0;
    speed = 100;

    system("cls");  // ��ü ȭ�� ���� 
    reset_main();   // main_org�� �ʱ�ȭ 
    draw_map();     // ����ȭ���� �׸�
    draw_main();    // �������� �׸� 

    b_type_next = rand() % 7;   // �������� ���� ��� ������ �����ϰ� ���� 
    new_block();                //���ο� ����� �ϳ� ����  

}

void reset_main() { //�������� �ʱ�ȭ  
    int i, j;

    for (i = 0; i < MAIN_Y; i++) { // �������� 0���� �ʱ�ȭ  
        for (j = 0; j < MAIN_X; j++) {
            main_org[i][j] = 0;
            main_cpy[i][j] = 100;
        }
    }
    for (j = 1; j < MAIN_X; j++) {      // y���� 3�� ��ġ�� õ���� 
        main_org[3][j] = CEILLING;
    }
    for (i = 1; i < MAIN_Y - 1; i++) {  // �¿� ��
        main_org[i][0] = WALL;
        main_org[i][MAIN_X - 1] = WALL;
    }
    for (j = 0; j < MAIN_X; j++) {      //�ٴ� ��
        main_org[MAIN_Y - 1][j] = WALL;
    }
}

void reset_main_cpy() { // main_cpy�� �ʱ�ȭ 
    int i, j;

    for (i = 0; i < MAIN_Y; i++) {          // �����ǿ� ���ӿ� ������ �ʴ� ���ڸ� ���� 
        for (j = 0; j < MAIN_X; j++) {      // main_org�� ���� ���ڰ� ���� �ϱ� ���� 
            main_cpy[i][j] = 100;
        }
    }
}

void draw_map() {       //���� ���� ǥ�ø� ��Ÿ���� �Լ�  
    int y = 3;              // level, goal, score�� �����߿� ���� �ٲ�� �� ���� �� y���� ���� �����ص� 
    // �׷��� Ȥ�� ���� ���� ǥ�� ��ġ�� �ٲ� �� �Լ����� �ȹٲ㵵 �ǰ�.. 
    gotoxy(STATUS_X_ADJ, STATUS_Y_LEVEL = y); printf(" LEVEL : %5d", level);
    gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL = y + 1); printf(" GOAL  : %5d", 10 - cnt);
    setColor(7);
    gotoxy(STATUS_X_ADJ, y + 2); printf("��   N E X T  �� ");
    gotoxy(STATUS_X_ADJ, y + 3); printf("��            �� ");
    gotoxy(STATUS_X_ADJ, y + 4); printf("��            �� ");
    gotoxy(STATUS_X_ADJ, y + 5); printf("��            �� ");
    gotoxy(STATUS_X_ADJ, y + 6); printf("��            �� ");
    gotoxy(STATUS_X_ADJ, y + 7); printf("�ߡߡߡߡߡߡߡ� ");
    setColor(10);
    gotoxy(STATUS_X_ADJ, y + 9); printf(" YOUR SCORE :");
    gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE = y + 10); printf("        %6d", score);
    setColor(8);
    gotoxy(STATUS_X_ADJ, y + 11); printf(" LAST SCORE :");
    gotoxy(STATUS_X_ADJ, y + 12); printf("        %6d", last_score);
    setColor(14);
    gotoxy(STATUS_X_ADJ, y + 13); printf(" BEST SCORE :");
    gotoxy(STATUS_X_ADJ, y + 14); printf("        %6d", best_score);
    setColor(5);
    gotoxy(STATUS_X_ADJ, y + 16); printf("  ��   : Shift");
    gotoxy(STATUS_X_ADJ, y + 17); printf("��  �� : Left / Right");
    gotoxy(STATUS_X_ADJ, y + 18); printf("  ��   : Soft Drop");
    gotoxy(STATUS_X_ADJ, y + 20); printf(" SPACE : Hard Drop");
    gotoxy(STATUS_X_ADJ, y + 22); printf("   P   : Pause");
    gotoxy(STATUS_X_ADJ, y + 24); printf("  ESC  : Quit");
}

void draw_main() {
    int i, j;

    for (j = 1; j < MAIN_X - 1; j++) { //õ���� ��� ���ο���� �������� �������� ���� �׷��� 
        if (main_org[3][j] == EMPTY) main_org[3][j] = CEILLING;
    }
    for (i = 0; i < MAIN_Y; i++) {
        for (j = 0; j < MAIN_X; j++) {
            if (main_cpy[i][j] != main_org[i][j]) { //cpy�� ���ؼ� ���� �޶��� �κи� ���� �׷���.
                //�̰� ������ ��������ü�� ��� �׷��� �������� ��¦�Ÿ�
                gotoxy(MAIN_X_ADJ + j, MAIN_Y_ADJ + i);
                switch (main_org[i][j]) {
                case EMPTY: //��ĭ��� 
                    printf("  ");
                    break;
                case CEILLING: // õ���� 
                    printf(". ");
                    break;
                case WALL: // �����
                    setColor(1);
                    printf("��");
                    break;
                case INACTIVE_BLOCK: //���� �� ���
                    setColor(15);
                    printf("��");
                    break;
                case ACTIVE_BLOCK: //�����̰� �ִ� �� ���  
                    setColor(2);
                    printf("��");
                    break;
                }
            }
        }
    }
    for (i = 0; i < MAIN_Y; i++) { //�������� �׸� �� main_cpy�� ����  
        for (j = 0; j < MAIN_X; j++) {
            main_cpy[i][j] = main_org[i][j];
        }
    }
}

void new_block() { // ���ο� ��� ����  
    int i, j;

    bx = (MAIN_X / 2) - 1; //��� ���� ��ġx��ǥ(�������� ���) 
    by = 0;  //��� ������ġ y��ǥ(���� ��) 
    b_type = b_type_next; //���������� ������ 
    b_type_next = rand() % 7; //���� ���� ���� 
    b_rotation = 0;  //ȸ���� 0������ ������ 

    new_block_on = 0; //new_block flag�� ��  

    for (i = 0; i < 4; i++)
    { //������ bx, by��ġ�� ������  
        for (j = 0; j < 4; j++) {
            if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = ACTIVE_BLOCK;
        }
    }
    for (i = 1; i < 3; i++)
    { //���ӻ���ǥ�ÿ� ������ ���ú��� �׸� 
        for (j = 0; j < 4; j++)
        {
            if (blocks[b_type_next][0][i][j] == 1)
            {
                setColor(10);
                gotoxy(STATUS_X_ADJ + 2 + j, i + 6);
                printf("��");
            }
            else
            {
                gotoxy(STATUS_X_ADJ + 2 + j, i + 6);
                printf("  ");
            }
        }
    }
}

void check_key() {
    key = 0; //Ű�� �ʱ�ȭ  

    if (kbhit()) { // ���� Ű�Է��� �ִ� ��쿡  
        key = getch(); //Ű���� �޴´�
        if (key == 224) { // ����Ű�� �� 
            do { key = getch(); } while (key == 224);// ���ð��� ���� 
            switch (key) {
            case LEFT: //����Ű ��������  
                if (check_crush(bx - 1, by, b_rotation) == true) move_block(LEFT);
                break;                            //�������� �� �� �ִ��� üũ �� �����ϸ� �̵�
            case RIGHT: //������ ����Ű ��������- ���� �����ϰ� ó���� 
                if (check_crush(bx + 1, by, b_rotation) == true) move_block(RIGHT);
                break;
            case DOWN: //�Ʒ��� ����Ű ��������-���� �����ϰ� ó���� 
                if (check_crush(bx, by + 1, b_rotation) == true) move_block(DOWN);
                break;
            case UP: //���� ����Ű �������� 
                if (check_crush(bx, by, (b_rotation + 1) % 4) == true) move_block(UP);
                //ȸ���� �� �ִ��� üũ �� �����ϸ� ȸ��
                else if (crush_on == 1 && check_crush(bx, by - 1, (b_rotation + 1) % 4) == true) move_block(100);
            }                    //�ٴڿ� ���� ��� �������� ��ĭ����� ȸ���� �����ϸ� �׷��� ��(Ư������)
        }
        else { //����Ű�� �ƴѰ�� 
            switch (key) {
            case SPACE: //�����̽�Ű �������� 
                space_key_on = 1; //�����̽�Ű flag�� ��� 
                while (crush_on == 0) { //�ٴڿ� ���������� �̵���Ŵ 
                    drop_block();
                    score += level; // hard drop ���ʽ�
                    gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE); printf("        %6d", score); //���� ǥ��  
                }
                break;
            case P: //P(�빮��) �������� 
            case p: //p(�ҹ���) �������� 
                pause(); //�Ͻ����� 
                break;
            case ESC: //ESC�������� 
                system("cls"); //ȭ���� ����� 
                exit(0); //�������� 
            }
        }
    }
    while (kbhit()) getch(); //Ű���۸� ��� 
}

void drop_block() {
    int i, j;

    if (crush_on && check_crush(bx, by + 1, b_rotation) == true) crush_on = 0; //���� ��������� crush flag �� 
    if (crush_on && check_crush(bx, by + 1, b_rotation) == false) { //���� ��������ʰ� crush flag�� ���������� 
        for (i = 0; i < MAIN_Y; i++) { //���� �������� ���� ���� 
            for (j = 0; j < MAIN_X; j++) {
                if (main_org[i][j] == ACTIVE_BLOCK) main_org[i][j] = INACTIVE_BLOCK;
            }
        }
        crush_on = 0; //flag�� �� 
        check_line(); //����üũ�� �� 
        new_block_on = 1; //���ο� ������ flag�� ��    
        return; //�Լ� ���� 
    }
    if (check_crush(bx, by + 1, b_rotation) == true) move_block(DOWN); //���� ��������� ������ ��ĭ �̵� 
    if (check_crush(bx, by + 1, b_rotation) == false) crush_on++; //������ �̵��� �ȵǸ�  crush flag�� ��
}

int check_crush(int bx, int by, int b_rotation) { //������ ��ǥ�� ȸ�������� �浹�� �ִ��� �˻� 
    int i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) { //������ ��ġ�� �����ǰ� ������� ���ؼ� ��ġ�� false�� ���� 
            if (blocks[b_type][b_rotation][i][j] == 1 && main_org[by + i][bx + j] > 0) return false;
        }
    }
    return true; //�ϳ��� �Ȱ�ġ�� true���� 
};

void move_block(int dir) { //����� �̵���Ŵ 
    int i, j;

    switch (dir) {
    case LEFT: //���ʹ��� 
        for (i = 0; i < 4; i++) { //������ǥ�� ���� ���� 
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
            }
        }
        for (i = 0; i < 4; i++) { //�������� ��ĭ���� active block�� ���� 
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j - 1] = ACTIVE_BLOCK;
            }
        }
        bx--; //��ǥ�� �̵� 
        break;

    case RIGHT:    //������ ����. ���ʹ����̶� ���� ������ ���� 
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
            }
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j + 1] = ACTIVE_BLOCK;
            }
        }
        bx++;
        break;

    case DOWN:    //�Ʒ��� ����. ���ʹ����̶� ���� ������ ����
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
            }
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i + 1][bx + j] = ACTIVE_BLOCK;
            }
        }
        by++;
        break;

    case UP: //Ű���� ���� �������� ȸ����Ŵ. 
        for (i = 0; i < 4; i++) { //������ǥ�� ���� ����  
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
            }
        }
        b_rotation = (b_rotation + 1) % 4; //ȸ������ 1������Ŵ(3���� 4�� �Ǵ� ���� 0���� �ǵ���) 
        for (i = 0; i < 4; i++) { //ȸ���� ����� ���� 
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = ACTIVE_BLOCK;
            }
        }
        break;

    case 100: //����� �ٴ�, Ȥ�� �ٸ� ��ϰ� ���� ���¿��� ��ĭ���� �÷� ȸ���� ������ ��� 
        //�̸� ���۽�Ű�� Ư������ 
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
            }
        }
        b_rotation = (b_rotation + 1) % 4;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i - 1][bx + j] = ACTIVE_BLOCK;
            }
        }
        by--;
        break;
    }
}

void check_line() {
    int i, j, k, l;

    int    block_amount; //������ ��ϰ����� �����ϴ� ���� 
    int combo = 0; //�޺����� �����ϴ� ���� ������ �ʱ�ȭ 

    for (i = MAIN_Y - 2; i > 3;) { //i=MAIN_Y-2 : ���ʺ��� ��ĭ����,  i>3 : õ��(3)�Ʒ����� �˻� 
        block_amount = 0; //��ϰ��� ���� ���� �ʱ�ȭ 
        for (j = 1; j < MAIN_X - 1; j++) { //���� �������� ��ϰ��縦 �� 
            if (main_org[i][j] > 0) block_amount++;
        }
        if (block_amount == MAIN_X - 2) { //����� ���� �� ��� 
            if (level_up_on == 0) { //���������°� �ƴ� ��쿡(�������� �Ǹ� �ڵ� �ٻ����� ����) 
                score += 100 * level; //�����߰� 
                cnt++; //���� �� ���� ī��Ʈ ���� 
                combo++; //�޺��� ����  
            }
            for (k = i; k > 1; k--) { //������ ��ĭ�� ��� ����(������ õ���� �ƴ� ��쿡��) 
                for (l = 1; l < MAIN_X - 1; l++) {
                    if (main_org[k - 1][l] != CEILLING) main_org[k][l] = main_org[k - 1][l];
                    if (main_org[k - 1][l] == CEILLING) main_org[k][l] = EMPTY;
                    //������ õ���� ��쿡�� õ���� ��ĭ ������ �ȵǴϱ� ��ĭ�� ���� 
                }
            }
        }
        else i--;
    }
    if (combo) { //�� ������ �ִ� ��� ������ ���� ��ǥ�� ���� ǥ����  
        if (combo > 1) { //2�޺��̻��� ��� ��� ���ʽ��� �޼����� �����ǿ� ����ٰ� ���� 
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 1, MAIN_Y_ADJ + by - 2); printf("%d COMBO!", combo);
            Sleep(500);
            score += (combo * level * 100);
            reset_main_cpy(); //�ؽ�Ʈ�� ����� ���� main_cpy�� �ʱ�ȭ.
            //(main_cpy�� main_org�� ���� �ٸ��Ƿ� ������ draw()ȣ��� ������ ��ü�� ���� �׸��� ��) 
        }
        gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL); printf(" GOAL  : %5d", (cnt <= 10) ? 10 - cnt : 0);
        gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE); printf("        %6d", score);
    }
}

void check_level_up() {
    int i, j;

    if (cnt >= 10) { //�������� 10�پ� ���־���. 10���̻� ���� ��� 
        draw_main();
        level_up_on = 1; //������ flag�� ��� 
        level += 1; //������ 1 �ø� 
        cnt = 0; //���� �ټ� �ʱ�ȭ   

        for (i = 0; i < 4; i++) {
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 3, MAIN_Y_ADJ + 5);
            printf("             ");
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 3, MAIN_Y_ADJ + 7);
            printf("             ");
            Sleep(200);

            setColor(12);
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 3, MAIN_Y_ADJ + 5);
            printf("��LEVEL UP!��");
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 3, MAIN_Y_ADJ + 7);
            printf("��SPEED UP!��");
            Sleep(200);
        }
        reset_main_cpy(); //�ؽ�Ʈ�� ����� ���� main_cpy�� �ʱ�ȭ.
        //(main_cpy�� main_org�� ���� �ٸ��Ƿ� ������ draw()ȣ��� ������ ��ü�� ���� �׸��� ��) 

        for (i = MAIN_Y - 2; i > MAIN_Y - 2 - (level - 1); i--) { //�������������� �� ����-1�� ����ŭ �Ʒ��� ���� ������ 
            for (j = 1; j < MAIN_X - 1; j++) {
                main_org[i][j] = INACTIVE_BLOCK; // ���� ������� ��� ä��� 
                gotoxy(MAIN_X_ADJ + j, MAIN_Y_ADJ + i); 
                printf("  ");
                Sleep(20);
            }
        }
        Sleep(100); //�������� �����ֱ� ���� delay 
        check_line(); //������� ��� ä��� �����
        //.check_line()�Լ� ���ο��� level up flag�� �����ִ� ��� ������ ����.         
        switch (level) { //�������� �ӵ��� ��������. 
        case 2:
            speed = 50;
            break;
        case 3:
            speed = 25;
            break;
        case 4:
            speed = 10;
            break;
        case 5:
            speed = 5;
            break;
        case 6:
            speed = 4;
            break;
        case 7:
            speed = 3;
            break;
        case 8:
            speed = 2;
            break;
        case 9:
            speed = 1;
            break;
        case 10:
            speed = 0;
            break;
        }
        level_up_on = 0; //������ flag����

        gotoxy(STATUS_X_ADJ, STATUS_Y_LEVEL); printf(" LEVEL : %5d", level); //����ǥ�� 
        gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL); printf(" GOAL  : %5d", 10 - cnt); // ������ǥ ǥ�� 

    }
}

void check_game_over() {
    int i;

    int x = 22;
    int y = 11;

    for (i = 1; i < MAIN_X - 2; i++) {
        if (main_org[3][i] > 0) { //õ��(������ ����° ��)�� inactive�� �����Ǹ� ���� ���� 
            setColor(12);
            gotoxy(x, y + 0); printf("�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�"); //���ӿ��� �޼��� 
            gotoxy(x, y + 1); printf("��                              ��");
            gotoxy(x, y + 2); printf("��    ��-------------------��     ��");
            gotoxy(x, y + 3); printf("��    ��  G A M E  O V E R ��     ��");
            gotoxy(x, y + 4); printf("��    ��-------------------��     ��");
            gotoxy(x, y + 5); printf("��   YOUR SCORE: %6d         ��", score);
            gotoxy(x, y + 6); printf("��                              ��");
            gotoxy(x, y + 7); printf("��   Press any key to restart   ��");
            gotoxy(x, y + 8); printf("��                              ��");
            gotoxy(x, y + 9); printf("�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�");
            last_score = score; //���������� �ű� 

            if (score > best_score) { //�ְ��� ���Ž� 
                FILE* file = fopen("score.dat", "wt"); //score.dat�� ���� ����                

                gotoxy(x, y + 6); printf("��  �١١� BEST SCORE! �١١�   ��  ");

                if (file == 0)
                { //���� �����޼���
                    setColor(4);
                    gotoxy(0, 0);
                    printf("FILE ERROR: SYSTEM CANNOT WRITE BEST SCORE ON \"SCORE.DAT\"");
                }
                else {
                    fprintf(file, "%d", score);
                    fclose(file);
                }
            }
            Sleep(1000);
            while (kbhit()) getch();
            key = getch();
            reset();
        }
    }
}

void pause() { //���� �Ͻ����� �Լ� 
    int i, j;

    int x = 22;
    int y = 11;

    for (i = 1; i < MAIN_X - 2; i++) { //���� �Ͻ����� �޼��� 
        setColor(11);
        gotoxy(x, y + 0); printf("�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�");
        gotoxy(x, y + 1); printf("��                              ��");
        gotoxy(x, y + 2); printf("��    ��-------------------��     ��");
        gotoxy(x, y + 3); printf("��    ��     P A U S E     ��     ��");
        gotoxy(x, y + 4); printf("��    ��-------------------��     ��");
        gotoxy(x, y + 5); printf("��    Press any key to resume   ��");
        gotoxy(x, y + 6); printf("��                              ��");
        gotoxy(x, y + 7); printf("�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�");
    }
    getch(); //Ű�Է½ñ��� ��� 

    system("cls"); //ȭ�� ����� ���� �׸� 
    reset_main_cpy();
    draw_main();
    draw_map();

    for (i = 1; i < 3; i++) { // ������� �׸� 
        for (j = 0; j < 4; j++) {
            if (blocks[b_type_next][0][i][j] == 1) {
                gotoxy(MAIN_X + MAIN_X_ADJ + 3 + j, i + 6);
                printf("��");
            }
            else {
                gotoxy(MAIN_X + MAIN_X_ADJ + 3 + j, i + 6);
                printf("  ");
            }
        }
    }
}