// name: Finn Gladstone
// unikey: fgla0414
// SID: 510 448 570

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <regex.h>

#define BUFFER_SIZE 128
#define BOARD_SIZE 19
#define MAX_HISTORY 1200
#define NO_PARAM_ARGS 5

/* Helper commands */

void update_history(char * input) {}

int check_win_condition(char * board) {
//     int reval;
//     printf("%c wins!\n", "finn");

//     return reval;
}

void update_mist(int x, int y) {}


/* Player commands */

void who(char ch) {
    printf("%c\n", ch);
}

void history(char * h) {
    printf("%s\n", h);
}

void view() {}

void place(char * input) {}

/* Main */

int main()
{
    //Setup variables
    char history[MAX_HISTORY];
    char player = 'B';
    char board[BOARD_SIZE][BOARD_SIZE];

    //Setup the game board
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = '.';
        }
    }

    // Setup regex
    regex_t re;
    int value; 
    //https://regex101.com/r/rO0yE6/1
    value = regcomp(&re, "^place [A-S]([1-9]|1[0-9]|20)$", 0);

    if (value != 0)
        printf("Fucked\n");




    int c;
    char buffer[BUFFER_SIZE];

    while(fgets(buffer, BUFFER_SIZE, stdin)) {
        
        //remove newline
        buffer[strcspn(buffer, "\n")] = 0; 
        
        if (strcmp(buffer, "who") == 0) {
            who(player);

        } else if (strcmp(buffer, "term") == 0) {
            exit(1);  
        } 
        
        else if (strcmp(buffer, "resign") == 0) {
            if (player == 'B')
                printf("White wins!\n");
            else
                printf("Black wins!\n");

            break;
        } 
        
        else if (strcmp(buffer, "view") == 0) {
            view();
        } 
        
        else if (strncmp(buffer, "place ", 6) == 0) {
            
            int x = regexec(&re, "place A14", 0, NULL, 0);

            printf("%d\n", x);

            // if (check_win_condition)
            //     break;
        } 
        
        else {
            printf("Invalid!\n");
        }
    
    }

    puts(history);
    puts("Thank you for playing!");
    return 0;
}