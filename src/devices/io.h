#ifndef IO_H
#define IO_H

#include <stddef.h>
#include <stdint.h>

#include "char.h"
#include "utils.h"
#include "keyboard.h"
#include "kernel.h"

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
static inline
void outw(uint16_t port, uint16_t data) {
	/* See [IA32-v2b] "OUT". */
	asm volatile("outw %w0, %w1" : : "a"(data), "Nd"(port));
}

// ==================================================================

uint32 vga_index;
static uint32 next_line_index = 1;
uint8 g_fore_color = WHITE, g_back_color = BLUE;
int digit_ascii_codes[10] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};

static inline
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

static inline 
void clear_vga_buffer(uint16 **buffer, uint8 fore_color, uint8 back_color) {
    uint32 i;
    for (i = 0; i < BUFSIZE; i++) {
    (*buffer)[i] = vga_entry(NULL, fore_color, back_color);
    }
    next_line_index = 1;
    vga_index = 0;
}

static inline 
void init_vga(uint8 fore_color, uint8 back_color) {
    vga_buffer = (uint16 *)VGA_ADDRESS;
    clear_vga_buffer(&vga_buffer, fore_color, back_color);
    g_fore_color = fore_color;
    g_back_color = back_color;
}

static inline 
void print_new_line() {
    if (next_line_index >= 55) {
    next_line_index = 0;
    clear_vga_buffer(&vga_buffer, g_fore_color, g_back_color);
    }
    vga_index = 80 * next_line_index;
    next_line_index++;
}

static inline 
void print_char(char ch) {
    vga_buffer[vga_index] = vga_entry(ch, g_fore_color, g_back_color);
    vga_index++;
}

static inline 
void print_string(char *str) {
    uint32 index = 0;
    while (str[index]) {
    print_char(str[index]);
    index++;
    }
}

static inline 
void print_int(int num) {
    char str_num[digit_count(num) + 1];
    itoa(num, str_num);
    print_string(str_num);
}

static inline 
uint8 inb(uint16 port) {
    uint8 ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "d"(port));
    return ret;
}

static inline 
void outb(uint16 port, uint8 data) {
    asm volatile("outb %0, %1" : "=a"(data) : "d"(port));
}

static inline 
char get_input_keycode() {
    char ch = 0;
    while ((ch = inb(KEYBOARD_PORT)) != 0) {
    if (ch > 0)
        return ch;
    }
    return ch;
}

static inline 
void wait_for_io(uint32 timer_count) {
    while (1) {
    asm volatile("nop");
    timer_count--;
    if (timer_count <= 0)
        break;
    }
}

static inline 
void sleep(uint32 timer_count) { wait_for_io(timer_count); }

#endif /* io.h */
