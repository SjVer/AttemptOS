#include <stdio.h>
#include <stdbool.h>

int count = 0;

int main(void) {
    printf("kernel initialized.\n");
    welcome();

    char command[20] = "Hello there!";
    int time = 0;
    while (true)
    {
        if (time >= 100000000) {
            printf("$ ");
            // scanf("%s", command);
            exec(command);
            time = 0;
        }
        time++;
    }
} 

void welcome(void) {
    printf("\nWelcome to AttemptOS!\n");
}

void exec(char * command) {
    printf("You entered: %s (%d)\n", command, count);
    count++;
}