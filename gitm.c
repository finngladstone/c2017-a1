// name: Finn Gladstone
// unikey: fgla0414
// SID: 510 448 570

/*
    Will interpret EOF as term + exit with code 1
*/

#include <stdio.h>
#include <string.h>

#define BUFFER 100
#define ARG0_BUFFER 8 // max command length = 7, + null byte
#define NUMBER_OF_NOPARAMS 4
#define BUFFER_SIZE 100



void who() {
    printf("Hello world\n");
}

void term() {}

void resign() {}

void view() {}

void place(int c, int r) {}

void history(int c, int r) {}

// https://stackoverflow.com/questions/252748/how-can-i-use-an-array-of-function-pointers
void (*no_param_ptr[NUMBER_OF_NOPARAMS])() = {who, term, resign, view};


/* 
    history --> hashmap? location : char array
    process line of input + recognise commands 
    incorrect command?
*/

void stdout_the_board() 
{
    ;
}

int main() // main will only read stdin and pass to other fns
{

    char no_param_calls[NUMBER_OF_NOPARAMS][ARG0_BUFFER];

    strcpy(no_param_calls[0], "who\0");
    strcpy(no_param_calls[1], "term\0");
    strcpy(no_param_calls[2], "resign\0");
    strcpy(no_param_calls[3], "view\0");

    /* Program logic loop */

    int c;
    char buffer[BUFFER_SIZE];

    while (fgets(buffer, BUFFER_SIZE, stdin)) 
    {
        buffer[strcspn(buffer, "\n")] = 0;

        for (int i = 0; i < NUMBER_OF_NOPARAMS; i++)
        {
            if (strcmp(buffer, no_param_calls[i]) == 0) 
            {
                (*no_param_ptr[i])();
                break;
            }      
        }

        ;
    }
    
    // term();

    return 0;
} 