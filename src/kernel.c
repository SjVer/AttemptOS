#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main(void) {
    printf("kernel initialized.\n");
    welcome();

    char *command;

    int time = 0;
    while (true) { // main command loop 

        printf("$ ");
        // scanf("%s", command);
        command = "test test";
        exec(command);
        break;
    }

    // infinite loop for testing purposes
    while (true) {
        if ( time > 200000000 ) {
            printf("...\n");
            time = 0;
        }
        time++;
    }
} 

void welcome(void) {
    printf("\nWelcome to AttemptOS!\n");
}

void exec(char *command) {
    printf("You entered: %s\n", command);
}