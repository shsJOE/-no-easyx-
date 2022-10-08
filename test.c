#include "../lib/game.c"

void menu()
{
    printf("################################\n");
    printf("######      1.play        ######\n");
    printf("######      0.exit        ######\n");
    printf("################################\n");
}

void game()
{
    char mine[ROWS][COLS];
    char show[ROWS][COLS];
    InitBoard(mine, ROWS, COLS, '0');
    InitBoard(show, ROWS, COLS, '*');
    DisplayBoard(show, ROW, COL);
    SetMine(mine, ROW, COL);
    FindMine(mine, show, ROW, COL);
}

int main()
{
    int input = 0;
    srand((unsigned int)time(NULL));
    do
    {
        menu();
        printf("请输入:>");
        scanf("%d",&input);
        switch(input)
        {
            case 1:
                system("cls");
                printf("\n扫雷\n");
                sleep(1);
                system("cls");
                game();
                break;
            case 0:
                system("cls");
                printf("\n退出游戏\n");
                sleep(1);
                system("cls");
                break;
            default:
                system("cls");
                printf("\n选择错误,请重新选择\n");
                sleep(1);
                system("cls");
                break;
        }
    } while (input);
}