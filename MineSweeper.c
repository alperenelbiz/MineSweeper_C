
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#define table_length 8
#define mine 3
#define win 1
#define lose -1
#define CONTINUE 0

char tab[table_length + 2][table_length + 2];
int main_table[table_length + 2][table_length + 2];
int num_mine, y = 0;
int f_count = 0;

void create_alt_table();
void initialize_table();
void print_alt_table();
void print_table();
void place_mine();
int verify_result();
void explorer(int line, int column);
int scanner(int line, int column);

int main(void)
{
    int line, column, stats, again;
    char action;

    printf("Welcome to Minesweeper:\n");
    create_alt_table();
    initialize_table();

    do
    {
        print_table();
        printf("\n");
        printf("\nPlease enter your action like tihs(s,1,2);");
        scanf("%c,%d,%d", &action, &line, &column);
        printf("\n");

        if (action == 's')
        {

            stats = scanner(line, column);
        }

        else if (action == 'f')
        {
            if (num_mine > f_count)
            {
                f_count++;
                tab[line][column] = 'F';
                stats = verify_result();
            }
        }

        else if (action == 'e')
        {
            if (f_count > 0)
            {
                f_count--;
            }

            tab[line][column] = '#';
            stats = scanner(line, column);
        }

        if (stats == lose)
        {
            printf("You lost.\n");
            print_alt_table();
            printf("Do you want to play again? [1-Yes] [2-No]\n");
            scanf("%d", &again);

            switch (again)
            {
            case 2:
                printf("Goodbye\n");
                return 0;
                break;

            case 1:
                f_count = 0;
                stats = CONTINUE;
                create_alt_table();
                initialize_table();
                break;

            default:
                printf("Invalid Value!!\n");
                break;
            }
        }

        if (stats == win)
        {
            printf("You won.\n");
            print_alt_table();

            printf("Do you want to play again? [1-Yes] [2-No]\n");
            scanf("%d", &again);

            switch (again)
            {
            case 0:
                printf("Goodbye\n");
                return 0;
                break;

            case 1:
                f_count = 0;
                stats = CONTINUE;
                create_alt_table();
                initialize_table();
                break;

            default:
                printf("Invalid Value!!");
                break;
            }
        }
    } while (1);
    return 0;
}

void create_alt_table()
{
    int i, j, num_mine;

    for (i = 0; i <= table_length + 1; i++)
    {
        for (j = 0; j <= table_length + 1; j++)
        {
            main_table[i][j] = 0;
        }
    }

    for (i = 0; i <= table_length; i++)
    {
        main_table[i][0] = 1;
        main_table[i][table_length + 1] = 1;
    }

    for (j = 0; j <= table_length; j++)
    {
        main_table[0][j] = 1;
        main_table[table_length + 1][j] = 1;
    }

    num_mine = mine;
    place_mine();
}

void initialize_table()
{
    int i, j;

    for (i = 0; i <= table_length + 1; i++)
    {
        for (j = 0; j <= table_length + 1; j++)
        {
            tab[i][j] = '#';
        }
    }

    for (i = 0; i <= table_length; i++)
    {
        tab[i][0] = '*';
        tab[i][table_length + 1] = '*';
    }

    for (j = 0; j <= table_length; j++)
    {
        tab[0][j] = '*';
        tab[table_length + 1][j] = '*';
    }
}

void print_table()
{
    int i, j;

    printf("\n");
    for (i = 1; i <= table_length; i++)
    {
        printf("%3d", i);
    }
    printf("\n");

    for (i = 1; i <= table_length; i++)
    {
        printf("---");
    }
    printf("\n");

    for (i = 1; i <= table_length; i++)
    {
        for (j = 1; j <= table_length; j++)
        {
            printf("%3c", tab[i][j]);
        }
        printf(" |%d", i);
        printf("\n");
    }

    for (i = 1; i <= table_length; i++)
    {
        printf("___");
    }
}

void print_alt_table()
{
    int i, j;

    printf("\n");
    for (i = 1; i <= table_length; i++)
    {
        printf("%3d", i);
    }
    printf("\n");

    for (i = 1; i <= table_length; i++)
    {
        printf("---");
    }
    printf("\n");

    for (i = 1; i <= table_length; i++)
    {
        for (j = 1; j <= table_length; j++)
        {
            printf("%3d", main_table[i][j]);
        }
        printf(" |%d", i);
        printf("\n");
    }

    for (i = 1; i <= table_length; i++)
    {
        printf("___");
    }
    printf("\n");
}

void place_mine()
{
    srand(time(NULL));
    int i, j, k, p, line, column;
    num_mine = mine;

    for (i = 1; i <= num_mine; i++)
    {
        line = 1 + rand() % table_length;
        column = 1 + rand() % table_length;

        if (main_table[line][column] == -1)
        {
            i--;
        }

        main_table[line][column] = -1;

        for (k = -1; k <= 1; k++)
        {
            for (p = -1; p <= 1; p++)
            {
                if (main_table[line][column] == -1)
                {
                    if (main_table[line + k][column + p] != -1)
                    {
                        main_table[line + k][column + p]++;
                    }
                }
            }
        }
    }
}

int verify_result()
{
    int i, j, y = 0, statut;

    for (i = 1; i <= table_length; i++)
    {
        for (j = 1; j <= table_length; j++)
        {
            if (tab[i][j] == 'D')
            {
                if (main_table[i][j] == -1)
                {
                    y++;
                }
            }
        }
    }

    if (y == mine)
    {
        statut = win;
    }

    else
        statut = CONTINUE;

    return statut;
}

void explorer(int line, int column)
{
    int i, j;

    tab[line][column] = '0' + main_table[line][column];

    for (i = -1; i <= 1; i++)
    {
        for (j = -1; j <= 1; j++)
        {
            if (main_table[line + i][column + j] > 0 && tab[line + i][column + j] == '#')
            {
                tab[line + i][column + j] = '0' + main_table[line + i][column + j];
            }

            else if (main_table[line + i][column + j] == 0 && tab[line + i][column + j] == '#')
            {
                explorer(line + i, column + j);
            }
        }
    }
}

int scanner(int line, int column)
{
    int x = 0;
    if (main_table[line][column] == -1)
    {
        x = lose;
    }

    else if (main_table[line][column] > 0)
    {
        tab[line][column] = ('0' + main_table[line][column]);
        x = CONTINUE;
    }

    else
    {
        explorer(line, column);
    }

    return x;
}