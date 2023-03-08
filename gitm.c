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
#define MAX_HISTORY 1084
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


void history(char * h) {
    printf("%s\n", h);
}

void view() {}

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
    regex_t check_syntax;
    regex_t check_validity;

    //https://regex101.com/r/rO0yE6/1
    regcomp(&check_syntax, "^place ([a-z]|[A-Z]|[0-9])+$", REG_EXTENDED);
    regcomp(&check_validity, "^place [A-S]([1-9]|1[0-9])$", REG_EXTENDED);

    int c;
    char buffer[BUFFER_SIZE];

    while(fgets(buffer, BUFFER_SIZE, stdin)) {
        
        //remove newline
        buffer[strcspn(buffer, "\n")] = 0; 
        
        if (strcmp(buffer, "who") == 0) {
            printf("%c\n", player);

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
        
        // Preprocessing for place()
        else if (strncmp(buffer, "place ", 6) == 0) { 
            
            if (regexec(&check_syntax, buffer, 0, NULL, 0) == 1) {
                printf("Invalid!\n");
                continue;
            }
                
            if (regexec(&check_validity, buffer, 0, NULL, 0) == 0) {
                
                int x; 
                int y;

                x = buffer[6] - 'A';

                if (strlen(buffer) == 8) 
                    y = buffer[7] - '0'; 
                else 
                    y = ((buffer[7] - '0') * 10) + (buffer[8] - '0') - 1;

                // Flip input as x, y in 2d array addressed as arr[y][x]
                // x/y coords preserved for history - remember to output as char/1-indexed int

                

            } 
            else 
                printf("Invalid coordinate\n");
    
        } 
        
        else {
            printf("Invalid!\n");
        }
    
    }

    puts(history);
    puts("Thank you for playing!");
    return 0;
}
