#ifndef IO_H
#define IO_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "char.h"
#include "kernel.h"
#include "keyboard.h"
#include "utils.h"

// ==================================================================

/* Reads and returns a byte from PORT. */
// static inline
// uint8_t inb(uint16_t port) {
// 	/* See [IA32-v2a] "IN". */
// 	uint8_t data;
// 	asm volatile("inb %w1, %b0" : "=a"(data) : "Nd"(port));
// 	return data;
// }

// /* Writes byte DATA to PORT. */
// static inline
// void outb(uint16_t port, uint8_t data) {
// 	 See [IA32-v2b] "OUT".
// 	asm volatile("outb %b0, %w1" : : "a"(data), "Nd"(port));
// }

// /* Writes the 16-bit DATA to PORT. */
static inline void outw(uint16_t port, uint16_t data) {
	/* See [IA32-v2b] "OUT". */
	asm volatile("outw %w0, %w1" : : "a"(data), "Nd"(port));
}

// ==================================================================

uint8 g_fore_color = WHITE, g_back_color = BLUE;

// vga stuff
uint32 vga_index;
uint16 cursor_pos = 0, cursor_next_line_index = 1;
static uint32 next_line_index = 1;

// key stuff
int digit_ascii_codes[10] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};
uint8_t shift; // shift flags. left shift is bit 0, right shift is bit 1.
uint8_t ctrl; // control flags just like shift flags.
uint8_t keypresses[256];

#define INPUT_SLEEP 1
#define TAB_WIDTH 4

uint16 vga_entry(unsigned char ch, uint8 fore_color, uint8 back_color) {
	uint16 ax = 0;
	uint8 ah = 0, al = 0;

	ah = back_color;
	ah <<= 4;
	ah |= fore_color;
	ax = ah;
	ax <<= 8;
	al = ch;
	ax |= al;

	return ax;
}

void clear_vga_buffer(uint16 **buffer, uint8 fore_color, uint8 back_color) {
	uint32 i;
	for (i = 0; i < BUFSIZE; i++) {
		(*buffer)[i] = vga_entry(NULL, fore_color, back_color);
	}
	next_line_index = 1;
	vga_index = 0;
}

void clear_screen() {
	clear_vga_buffer(&vga_buffer, g_fore_color, g_back_color);
	cursor_pos = 0;
	cursor_next_line_index = 1;
}

void init_vga(uint8 fore_color, uint8 back_color) {
	vga_buffer = (uint16 *)VGA_ADDRESS;
	clear_vga_buffer(&vga_buffer, fore_color, back_color);
	g_fore_color = fore_color;
	g_back_color = back_color;
}

uint8 inb(uint16 port) {
	uint8 data;
	asm volatile("inb %1, %0" : "=a"(data) : "Nd"(port));
	return data;
}

void outb(uint16 port, uint8 data) { asm volatile("outb %0, %1" : : "a"(data), "Nd"(port)); }

void move_cursor(uint16 pos) {
	outb(0x3D4, 14);
	outb(0x3D5, ((pos >> 8) & 0x00FF));
	outb(0x3D4, 15);
	outb(0x3D5, pos & 0x00FF);
}

void move_cursor_back() {
	vga_index--;
	move_cursor(--cursor_pos);
}

void move_cursor_next_line() {
	cursor_pos = 80 * cursor_next_line_index;
	cursor_next_line_index++;
	move_cursor(cursor_pos);
}

void gotoxy(uint16 x, uint16 y) {
	vga_index = 80 * y;
	vga_index += x;
	if (y > 0) {
		cursor_pos = 80 * cursor_next_line_index * y;
		cursor_next_line_index++;
		move_cursor(cursor_pos);
	}
}

char get_input_keycode() {
	char ch = 0;
	while ((ch = inb(KEYBOARD_PORT)) != 0) {
		if (ch > 0)
			return ch;
	}
	return ch;
}

/*
char handle_input_keycode(uint8_t byte) {
	char ch;

	if(byte & 0x80) {
		print_string("KEY RELEASE");
		// Key release
		uint8_t pressedbyte = byte & 0x7F;
		// Check if we're releasing a shift key.
		if(pressedbyte == 0x2A) {
			// left
			shift = shift & 0x02;
		}
		else if(pressedbyte == 0x36) {
			// right
			shift = shift & 0x01;
		}
		else if(pressedbyte == 0x1D) {
			ctrl = 0;
		}

		keypresses[pressedbyte] = 0;
		return;
	}

	if(keypresses[byte] < 10 && keypresses[byte] > 0) {
		// Key is already pressed. Ignore it.
		keypresses[byte]++; // Increment anyway, so we can roll over and repeat.
		return;
	}
	keypresses[byte]++;

	if(byte == 0x2A) {
		shift = shift | 0x01;
		return;
	}
	else if(byte == 0x36) {
		shift = shift | 0x02;
		return;
	}
	else if(byte == 0x1D) {
		ctrl = 1;
		return;
	}

	if (shift) {
		ch = byte;
	}
	else
		ch = char_tolower(byte);
	return ch;
}
*/

void wait_for_io(uint32 timer_count) {
	while (1) {
		asm volatile("nop");
		timer_count--;
		if (timer_count <= 0)
			break;
	}
}

void sleep(uint32 timer_count) { wait_for_io(timer_count * 0x02FFFFFF); }

void print_newline() {
	if (next_line_index >= 55) {
		next_line_index = 0;
		clear_vga_buffer(&vga_buffer, g_fore_color, g_back_color);
	}
	vga_index = 80 * next_line_index;
	next_line_index++;
	move_cursor_next_line();
}

void print_char(char ch) {
	vga_buffer[vga_index] = vga_entry(ch, g_fore_color, g_back_color);
	vga_index++;
	move_cursor(++cursor_pos);
}

void print_string(char *str) {
	uint32 index = 0;
	while (str[index]) {
		if (str[index] == '\n') {
			print_newline();
			index++;
		} else if (str[index] == '\t') {
			for (int x; x < TAB_WIDTH; x++)
				print_char(' ');
			index++;
		} else {
			print_char(str[index]);
			index++;
		}
	}
}

void print_tab() {
	for (int i = 0; i < TAB_WIDTH; i++)
		print_char(' ');
}

void print_int(int num) {
	char str_num[digit_count(num) + 1];
	itoa(num, str_num);
	print_string(str_num);
}

void print_uint8(uint8 ch) {
	print_char(ch);
}

void backspace() {
	move_cursor_back();
	vga_buffer[vga_index] = vga_entry(0, g_fore_color, g_back_color);
}

int read_int() {
	char ch = 0;
	char keycode = 0;
	char data[32];
	int index = 0;
	do {
		keycode = get_input_keycode();
		if (keycode == KEY_ENTER) {
			data[index] = '\0';
			print_newline();
			break;
		} else {
			ch = get_ascii_char(keycode);
			print_char(ch);
			data[index] = ch;
			index++;
		}
		sleep(INPUT_SLEEP);
	} while (ch > 0);

	return atoi(data);
}

char get_char(bool do_sleep) {
	char keycode = 0;
	if (do_sleep)
		sleep(INPUT_SLEEP);
	keycode = get_input_keycode();
	if (do_sleep)
		sleep(INPUT_SLEEP);
	return get_ascii_char(keycode);
}

#endif /* io.h */
