// #include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "char.h"
#include "kernel.h"
#include "utils.h"
#include "io.h"

// =====================================================================================

void input_loop() {
	char ch = 0;
	char keycode = 0;
	do {

		keycode = get_input_keycode();

		if (keycode == KEY_ENTER) {
			print_new_line();
		} else {
			ch = get_ascii_char(keycode);
			print_char(ch);
		}
		sleep(1);

	} while (true);
}

int main(void) {
	init_vga(WHITE, BLUE);
	print_string("Welcome to AttemptOS!");
	print_new_line();
	print_string("Type here...");
	print_new_line();
	input_loop();

	return 0;
}
