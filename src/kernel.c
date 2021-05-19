#include <stdio.h>

int main(void) {
    printf("kernel initialized.\n");
    welcome();
}

void welcome(void) {
    printf("\nWelcome to AttemptOS!\n");
}