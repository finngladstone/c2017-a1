// name: Finn Gladstone
// unikey: fgla0414
// SID: 510 448 570

#include <stdio.h>
#include <string.h>

#define BUFFER 100
#define ARG0_BUFFER 8 // max command length = 7, + null byte

void who();

void term();

void resign();

void view();

void place(int c, int r);

void history(int c, int r);




/* 
    history --> hashmap? location : char array
    process line of input + recognise commands 
    incorrect command?
*/


void route_commands(char * command)
{  
    
    // clean commands
    char first_arg[ARG0_BUFFER];

    int i = 0;
    while (*command != ' ') {
        
        if (i == ARG0_BUFFER) {
            printf("Error: Invalid command\n");
            return;
        }

        command++;

    }

}

int main() // main will only read stdin and pass to other fns
{
    // char str1[] = "hello";
    // // char str2[] = "hello";
    // char str2[8];
    // str2[0] = 'h';
    // str2[1] = 'e';
    // str2[2] = 'l';
    // str2[3] = 'l';
    // str2[4] = 'o';
    // str2[5] = '\0';

    // int result = strcmp(str1, str2);
    // printf("result = %d\n", result);
    // printf("length = %ld\n", strlen(str2));

    return 0;
} 