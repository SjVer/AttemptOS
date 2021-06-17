// #include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "keyboard.h"
#include "char.h"
#include "kernel.h"
#include "utils.h"
#include "io.h"
#include "device.h"

#define FG_COLOR GREEN
#define BG_COLOR BLACK

const char promp_msg[] = "> ";

void prompt(char out_buf[]) {
	print_string(promp_msg);

	char buffer[CMDBUFSIZE] = "";
	char ch = 0;
	char keycode = 0;
	bool shift = false;
	bool ctrl = false;

	// loop: get input, check if char or else and do shit with it
	do {

		keycode = get_input_keycode();

		if (keycode != KEY_ENTER && is_normal_char(keycode)) {

			ch = get_ascii_char(keycode);
			ch = char_tolower(ch);

			// handle key releases n stuff
			// if((uint8_t)keycode & 0x80) {
			// 	print_string("KEY RELEASE");
			// 	// Key release
			// 	uint8_t pressedbyte = (uint8_t)keycode & 0x7F;
			// 	// Check if we're releasing a shift key.
			// 	if (pressedbyte == KEY_SHIFT_L || pressedbyte == KEY_SHIFT_R) {
			// 		shift = false;
			// 	}
			// 	else if (pressedbyte == KEY_CONTROL)
			// 		ctrl = false;
			// }

			if (shift) {
				ch = char_toupper(ch);
				shift = false;
			}



			print_char(ch);
			// append to buffer
			insert_char(buffer, ch, strlen_int(buffer));
		
		} else {
			// switch((uint8)keycode) {
			// 	case KEY_BACKSPACE: if (strlen_int(buffer) > 1) { buffer[strlen_int(buffer)-2] = '\0'; backspace(); }
			// 	case KEY_TAB: print_tab();
			// 	default: {} 
			// }
			uint8 key = (uint8)keycode;

			if (key == KEY_SHIFT_L || key == KEY_SHIFT_R)
				shift = true;

			else if (key == KEY_CONTROL)
				ctrl = true;

			else if (key == KEY_BACKSPACE) {
				if (strlen_int(buffer) > 1) {
					buffer[strlen_int(buffer) - 2] = '\0';
					backspace();
				}
			}
			else if (key == KEY_TAB) {
				print_tab();
				for (int i = 0; i < TAB_WIDTH; i++)
					insert_char(buffer, ' ', strlen_int(buffer));
			}
		}

		sleep(INPUT_SLEEP);

	} while (keycode != KEY_ENTER);

	overwrite_chararr(buffer, out_buf);
	return;
}

void eval_command(char cmd[]) {

	cmd = string_toupper(cmd);

	if (strcmp_bool(cmd, ""))
		return;

	if (strcmp_bool(cmd, "CLEAR"))
		clear_screen();

	else if (strcmp_bool(cmd, "TEST"))
		print_string("test confirmed!\n");

	else if (strcmp_bool(cmd, "REBOOT"))
		reboot();

	else if (strcmp_bool(cmd, "SHUTDOWN"))
		shutdown();

	else if (strcmp_bool(cmd, "HELP")) {
		print_string("Available commands:\n\
			 - CLEAR      - clear the screen\n\
			 - TEST       - prints test message\n\
			 - HELP       - show this message\n\
			 - REBOOT     - reboot device\n\
			 - SHUTDOWN   - shutdown device\n");
	}
	else {
		print_string(cmd);
		print_string(": command not found.\nType \"HELP\" to list all available commands.\n");
	}
}

int main(void) {
	init_vga(FG_COLOR, BG_COLOR);
	print_string("Welcome to AttemptOS!");
	print_newline();
	print_string("Type here...");
	print_newline();
	
	bool keep_alive = true;

	do {

		char user_input[CMDBUFSIZE];
		prompt(user_input);
		print_newline();
		eval_command(user_input);

	} while (keep_alive);

	return 0;
}
