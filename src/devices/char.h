#ifndef CHAR_H
#define CHAR_H

#include "types.h"
#include "keyboard.h"
#include <stdbool.h>

extern char get_ascii_char(uint8);
extern uint8 get_keycode(char);
extern bool is_normal_char(uint8);
extern char char_tolower(char);
extern char * string_toupper(char[]);
extern char * string_tolower(char[]);

#endif


