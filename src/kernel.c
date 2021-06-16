// #include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "char.h"
#include "kernel.h"
#include "utils.h"
#include "io.h"

const char promp_msg[] = "> ";

void prompt(char* *command) {
	print_string(promp_msg);

	char *buffer;
	char ch = 0;
	char keycode = 0;
	do {

		keycode = get_input_keycode();

		if (keycode == KEY_ENTER) {
			print_new_line();
			strcpy(*command, buffer);
			return;
		} else {
			ch = get_ascii_char(keycode);
			print_char(ch);
			strncat(buffer, &ch, 1);
		}
		sleep(INPUT_SLEEP);

	} while (true);
}

int main(void) {
	init_vga(WHITE, BLUE);
	print_string("Welcome to AttemptOS!");
	print_new_line();
	print_string("Type here...");
	print_new_line();
	
	bool keep_alive = true;

	do {

		char *user_input;
		prompt(&user_input);
		print_string(user_input);

	} while (keep_alive)

	return 0;
}
