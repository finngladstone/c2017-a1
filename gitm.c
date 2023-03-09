// name: Finn Gladstone
// unikey: fgla0414
// SID: 510 448 570

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <regex.h>

#define BUFFER_SIZE 256
#define BOARD_SIZE 19
#define MAX_HISTORY 1084
#define NO_PARAM_ARGS 5

/* Helper commands */

int raise(int x, int power) {
    int reval = 1;  
    for (int i = 1; i <= power; i++)
        reval *= x;

    return reval;
}

int within_range(int a) {
    if (a >= 0 && a <= 18)
        return 1;

    return 0;
}

/* Functions for checking win condition*/

int check_next_position(char board[BOARD_SIZE][BOARD_SIZE], int x, int y, int xmod, int ymod) {

    if (!(within_range(x + xmod) && within_range(y + ymod)))
        return 0;

    char ch = board[y][x];

    if (board[y+ymod][x+xmod] != ch)
        return 0;
    else 
        return 1 + check_next_position(board, x+xmod, y+ymod, xmod, ymod);

}

int check_win_condition(char board[BOARD_SIZE][BOARD_SIZE], int x, int y) {
    int count = 0;
    char ch = board[y][x];
    int temp = 0;

    for (int i = x - 1; i < x + 2; i++) {
        for (int j = y - 1; j < y + 2; j++) {
            if ((i == x) && (j == y))
                continue;

            if (within_range(i) && within_range(j))
                ;
            else 
                continue;
            
            if (board[j][i] == ch) {
                temp = 1 + check_next_position(board, x, y, x - i, y - j) + check_next_position(board, x, y, (x - i)*-1, (y - j)*-1);
            }

            if (temp > count)
                count = temp;
        }
    }

    if (count >= 5)
        return 1;
    return 0;
}

/* Main */

int main()
{

    //Setup variables
    char history[MAX_HISTORY] = "";
    char player = 'B';
    char board[BOARD_SIZE][BOARD_SIZE];

    int history_pointer = 0;

    int mist_x = 9;
    int mist_y = 9;

    //Setup the game board
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = '.';
        }
    }

    // Setup regex for parsing place args later

    regex_t check_syntax;
    regex_t check_validity;

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

        else if (strcmp(buffer, "history") == 0) {
            printf("%s\n", history);
        }
        
        else if (strcmp(buffer, "view") == 0) {
            // Output centre of mist coord in 1-indexed
            printf("%c%i,", mist_x + 'A', 19 - mist_y); 

            // Display concat string of positions in mist
            for (int i = mist_y - 3; i <= mist_y + 3; i++) {
                for (int j = mist_x - 3; j <= mist_x + 3; j++) {
                    if (within_range(i) && within_range(j))
                        printf("%c", board[i][j]);
                    else 
                        printf("x");
                }
            }

            printf("\n");
        } 
        
        // Preprocessing for place()
        else if (strncmp(buffer, "place ", 6) == 0) { 

            // Will confirm command is within 'place [coord]' syntax and nothing else
            regcomp(&check_syntax, "^place ([a-z]|[A-Z]|[0-9])+$", REG_EXTENDED);
            
            if (regexec(&check_syntax, buffer, 0, NULL, 0) == 1) {
                printf("Invalid!\n");
                regfree(&check_syntax); // Will regfree asap in both outcomes
                continue;
            }

            regfree(&check_syntax); // See above about regfree

            // Will check that coordinate is valid!
            regcomp(&check_validity, "^place [A-S]([1-9]|1[0-9])$", REG_EXTENDED);
                
            if (regexec(&check_validity, buffer, 0, NULL, 0) == 0) {

                regfree(&check_validity);
                
                int x; 
                int y;
                char stone;
                int len;

                // Obtain x: we know that the x coord is always at index 6
                x = buffer[6] - 'A'; 
            
                // Check if we have a 1 or 2 digit y coord and account for such
                if (strlen(buffer) == 8) {
                    y = buffer[7] - '0'; 
                    len = 2;
                } else {
                    y = ((buffer[7] - '0') * 10) + (buffer[8] - '0');
                    len = 3;
                }

                // Set stone (dependent on current player)
                if (player == 'B')
                    stone = '#';
                else
                    stone = 'o';

                // Check coord != occupied
                if (board[19 - y][x] == '.') {
                    board[19 - y][x] = stone;
                    
                    //Update history
                    int i;
                    for (i = 0; i < len; i++)
                        history[history_pointer + i] = buffer[i+6];

                    history_pointer += i;

                    //Check win condition
                    if (check_win_condition(board, x, 19-y)) {
                        if (player == 'B')
                            printf("Black wins!\n");
                        else   
                            printf("White wins!\n");

                        break;
                    }

                    //Update mist - returns 0-indexed coords 
                    mist_x = (5 * raise(x+1, 2) + 3 * (x+1) + 4) % 19;
                    mist_y = 19 - (1 + (4 * raise(y, 2) + 2 * y - 4) % 19);


                    // Switch player
                    if (player == 'B')
                        player = 'W';
                    else
                        player = 'B';
                }
                else 
                    printf("Occupied coordinate\n");
            } 
            else { // Regex on validity fails
                printf("Invalid coordinate\n");
                regfree(&check_validity); // Already freed above if it succeeds
            }
        } 
        
        else { // Command is completely unrecognised 
            printf("Invalid!\n");
        }
    
    }
    // Endgame !
    
    printf("%s\n", history);
    printf("Thank you for playing!\n");
    return 0;
}
