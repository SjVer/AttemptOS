#include "utils.h"
#include <stdbool.h>

uint32 stringlen(const char* str) {
	uint32 length = 0;
	while(str[length])
		length++;
	return length;
}

uint32 digit_count(int num) {
	uint32 count = 0;
	if(num == 0)
		return 1;
	while(num > 0){
		count++;
		num = num/10;
	}
	return count;
}

void itoa(int num, char *number) {
	int dgcount = digit_count(num);
	int index = dgcount - 1;
	char x;
	if(num == 0 && dgcount == 1){
		number[0] = '0';
		number[1] = '\0';
	}else{
		while(num != 0){
			x = num % 10;
			number[index] = x + '0';
			index--;
			num = num / 10;
		}
		number[dgcount] = '\0';
	}
}

int atoi(char* s) {
	int len = strlen(s);
	int i = len - 1;
	int num = 0, pos = 1;
	while(i >= 0){
		num += (s[i] - '0') * pos;
		pos *= 10;
		i--;
	}
	return num;
}

// =============

int strlen_int(char str[]) {
	int len;
	for (len = 0; str[len] != '\0'; len++);
	len++;
	return len;
}

// char * chararr_to_charptr(char *str) {
// 	char arr[sizeof(char*)];
// 	memcpy(arr, &str, sizeof(char *));
// 	return arr;
// }

void insert_char(char str[], char ch, int pos) {
	// shift
	for (int i = strlen_int(str); i >= pos; i--)
		str[i] = str[i-1];
	// insert at pos
	str[pos-1] = ch;
}

void overwrite_chararr(char src[], char dest[]) {
	// if (strlen_int(src) > strlen_int(dest))
	for (int i = 0; i < strlen_int(dest); i++) {
		dest[i] = src[i];
	}
}

bool strcmp_bool(char *a, char *b) {
	if (strcmp(a, b) == 0)
		return true;
	return false;
}
