// name: Finn Gladstone
// unikey: fgla0414
// SID: 510 448 570

/*
    Will interpret EOF as term + exit with code 1
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFFER 100
#define ARG0_BUFFER 8 // max command length = 7, + null byte
#define NUMBER_OF_NOPARAMS 5
#define BUFFER_SIZE 100
#define BOARD_SIZE 19
#define HISTORY_SIZE 100

char board[BOARD_SIZE][BOARD_SIZE];
int x_mist;
int y_mist;

int x_stone;
int y_stone;

char player;
char historystr[HISTORY_SIZE];

int check_coord(int a)
{
    if (a >= 1 && a <= 19)
        return 1;

    printf("Invalid coordinate\n");
    return 0;
}

int check_same_tile() 
{

}

void check_win_condition()
{

}

void switch_player() 
{
    if (player == 'B')
        player = 'W';
    else
        player = 'B';
}

void who() 
{
    printf("%c\n", player);
}

void history() 
{
    printf("%s\n", historystr);
}

void term() 
{
    exit(1);
}

void resign() 
{   
    if (player == 'B')
        printf("White wins!\n");
    else   
        printf("Black wins!\n");

    history();
    exit(0);
}

void view() 
{
    ;
}

void place(char * input) 
{
    int x;
    int y;

    if (!isalpha(input[6]) || !isupper(input[6]))
    {
        printf("Invalid coordinate\n");
        return;
    }

    if (input[8] == ' ' || input[9] == ' ') // command = [place][coord][whitespace]
    {
        printf("Invalid!\n");
        return;
    }


    x = input[6] - 'A';

    if (!check_coord(x + 1)) // we read in A as 0, therefore offset for check!
        return;

    if (strlen(input) == 8) 
        y = input[7] - '0'; 
    else 
        y = ((input[7] - '0') * 10) + (input[8] - '0');

    if (!check_coord(y))
        return;

    if (board[x][y-1] == '.')
        ;
    else 
    {
        ;
    }
        

    

    // add to history string
        
    // switch_player();
    
} // need to clean input



// https://stackoverflow.com/questions/252748/how-can-i-use-an-array-of-function-pointers
void (*no_param_ptr[NUMBER_OF_NOPARAMS])() = {who, term, resign, view, history};

void stdout_the_board() {}

void update_mist() {}

int main()
{

    /* Setup board + function calls*/

    player = 'B';

    for (int i = 0; i < 19; i++) 
    {
        for (int j = 0; j < 19; j++) 
        {
            board[i][j] = '.';
        }
    }

    char no_param_calls[NUMBER_OF_NOPARAMS][ARG0_BUFFER];

    strcpy(no_param_calls[0], "who\0");
    strcpy(no_param_calls[1], "term\0");
    strcpy(no_param_calls[2], "resign\0");
    strcpy(no_param_calls[3], "view\0");
    strcpy(no_param_calls[4], "history\0");

    /* Program logic loop */

    int c;
    int success;
    char buffer[BUFFER_SIZE];

    while (fgets(buffer, BUFFER_SIZE, stdin)) 
    {
        buffer[strcspn(buffer, "\n")] = 0;
        success = 0;


        for (int i = 0; i < NUMBER_OF_NOPARAMS; i++)
        {
            if (strcmp(buffer, no_param_calls[i]) == 0) 
            {
                (*no_param_ptr[i])();
                success = 1;
                break;
            }      
        } 

        if (success == 0)
        {   
            if (strncmp(buffer, "place ", 6) == 0)
            {
                if (strlen(buffer) == 9 || strlen(buffer) == 8)
                    place(buffer);
                else 
                    printf("Invalid coordinate\n");
            }
            else
                printf("Invalid!\n");
        }

    }
    
    // term();

    return 0;
} 