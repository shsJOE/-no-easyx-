#include "../include/game.h"

void InitBoard(char board[ROWS][COLS], int rows, int cols, char set)
{
    int i = 0;
    int j = 0;
    for (i = 0; i < ROWS; i ++)
    {
        for (j = 0; j < COLS; j ++)
        {
            board[i][j] = set; 
        }
    }
}

void DisplayBoard(char board[ROWS][COLS], int row, int col)
{
    int i = 0;
    int j = 0;
    printf("---------扫雷游戏---------\n");
    for (i = 0; i <= col; i++)
    {
        printf("%d ", i);
    }
    printf("\n");
    for (i = 1; i <= row; i++)
    {
        printf("%d ", i);
        for (j = 1; j <= col; j++)
        {
            printf("%c ", board[i][j]);
        }
        printf("\n");
        }
    printf("---------扫雷游戏---------\n");
}

void SetMine(char mine[ROWS][COLS], int row, int col)
{
    int count = EASY_COUNT;
    while(count)
    {
        int x = rand() % col + 1;
        int y = rand() % row + 1;
        if(mine[x][y] == '0')
        {
            mine[x][y] = '1';
            count--;
        }
    }
}

static int get_mine_count(char mine[ROWS][COLS], int x, int y)
{
    return mine[x - 1][y - 1] +
           mine[x - 1][y] +
           mine[x - 1][y + 1] +
           mine[x][y - 1] +
           mine[x][y + 1] +
           mine[x + 1][y - 1] +
           mine[x + 1][y] +
           mine[x + 1][y + 1] - 8 * '0';
}

void re_coor(char mine[ROWS][COLS], char show[ROWS][COLS], int a, int b, int *win)
{
    if (show[a][b] == '*' && a > 0 && a < COLS-1 && b > 0 && b < ROWS-1)
        ExpandBoard(mine, show, a, b, win);
}

void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
    int x = 0;
    int y = 0;
    int win = 0;
    int c = 0;
    int mark = 0;
    while (win < ROW * COL - EASY_COUNT)
    {
        printf("1.排雷\n2.标记\n3.退出\n");
        scanf("%d", &c);
        if (c == 1)
        {
            printf("请输入要排查的坐标:>");
            scanf("%d%d", &x, &y);
            if(x >= 1 && x <= col && y >= 1 && y <= row)
            {
                if(show[x][y]!='*'&&show[x][y]!='?')
                {
                    printf("排查过这里了，重新输入\n");
                }
                else if(mine[x][y]=='1')
                {
                    system("cls");
                    printf("寄，雷子炸了\n\n\n按理说你应该逝乐，可这只是游戏\n");
                    DisplayBoard(mine, row, col);
                    break;
                } 
                else
                {
                    ExpandBoard(mine, show, x, y, &win);
                    system("cls");
                    DisplayBoard(show, row, col);
                }
            }
            else
            {
                printf("坐标不合法，请重新输入:>\n");
            }
        }

        else if (c == 2)
        {
            if(mark<=EASY_COUNT)
            {
                printf("请输入要标记的坐标:>\n");
                scanf("%d%d", &x, &y);            
                if(x >= 1 && x <= col && y >= 1 && y <= row)
                {
                    if(show[x][y]=='*')
                    {
                        show[x][y] = '?';
                        system("cls");
                        printf("标记成功\n");
                        sleep(1);
                        system("cls");
                        DisplayBoard(show, row, col);
                        mark++;
                    }
                    else if(show[x][y]=='?')
                    {
                        show[x][y] = '*';
                        system("cls");
                        printf("已取消标记\n");
                        sleep(1);
                        system("cls");
                        DisplayBoard(show, row, col);
                        mark--;
                    }
                    else
                    {
                        printf("此处不可标记\n");
                    }
                }
                else
                {
                    printf("坐标不合法，请重新输入:>\n");
                }
            }
            else
            {
                printf("注意！！！标记数比雷数多了哦\n");
            }
        }

        else if (c == 3)
            break;

        else 
            printf("无此选项\n");
    }
    if (win == ROW * COL - EASY_COUNT)
    {
        system("cls");
        printf("赢了，排完了\n\n\n你就是扫雷小天才\n");
        printf("看看战果\n");
        printf("\n                 3                   \n");
        sleep(1);
        printf("\n                 2                   \n");
        sleep(1);
        printf("\n                 1                   \n");
        sleep(1);
        DisplayBoard(mine, row, col);
    }
}


void ExpandBoard(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y, int *win)
{
    int count = get_mine_count(mine, x, y);
    if (count == 0)
    {
        show[x][y] = ' ';
        (*win)++;
        re_coor(mine, show, x - 1, y - 1, win);
        re_coor(mine, show, x - 1, y, win);
        re_coor(mine, show, x - 1, y + 1, win);
        re_coor(mine, show, x, y - 1, win);
        re_coor(mine, show, x, y + 1, win);
        re_coor(mine, show, x + 1, y - 1, win);
        re_coor(mine, show, x + 1, y, win);
        re_coor(mine, show, x + 1, y + 1, win);
    }
    else
    {
        show[x][y] = count + '0';
        (*win)++;
    }
}