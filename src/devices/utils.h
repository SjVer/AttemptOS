#ifndef UTILS_H
#define UTILS_H

#include "types.h"
#include <stdbool.h>

extern uint32 strlen(const char*);
extern uint32 digit_count(int);
extern void itoa(int, char *);
extern int atoi(char*);

extern int strlen_int(char str[]);
// extern char * chararr_to_charptr(char *str);
extern void insert_char(char str[], char ch, int pos);
extern void overwrite_chararr(char src[], char dest[]);
extern bool strcmp_bool(char *a, char *b);

#endif

