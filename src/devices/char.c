#include "char.h"
#include <stdbool.h>

char get_ascii_char(uint8 key_code) {
	switch(key_code){
		case KEY_A : return 'A';
		case KEY_B : return 'B';
		case KEY_C : return 'C';
		case KEY_D : return 'D';
		case KEY_E : return 'E';
		case KEY_F : return 'F';
		case KEY_G : return 'G';
		case KEY_H : return 'H';
		case KEY_I : return 'I';
		case KEY_J : return 'J';
		case KEY_K : return 'K';
		case KEY_L : return 'L';
		case KEY_M : return 'M';
		case KEY_N : return 'N';
		case KEY_O : return 'O';
		case KEY_P : return 'P';
		case KEY_Q : return 'Q';
		case KEY_R : return 'R';
		case KEY_S : return 'S';
		case KEY_T : return 'T';
		case KEY_U : return 'U';
		case KEY_V : return 'V';
		case KEY_W : return 'W';
		case KEY_X : return 'X';
		case KEY_Y : return 'Y';
		case KEY_Z : return 'Z';
		case KEY_1 : return '1';
		case KEY_2 : return '2';
		case KEY_3 : return '3';
		case KEY_4 : return '4';
		case KEY_5 : return '5';
		case KEY_6 : return '6';
		case KEY_7 : return '7';
		case KEY_8 : return '8';
		case KEY_9 : return '9';
		case KEY_0 : return '0';
		case KEY_MINUS : return '-';
		case KEY_EQUAL : return '=';
		case KEY_SQUARE_OPEN_BRACKET : return '[';
		case KEY_SQUARE_CLOSE_BRACKET : return ']';
		case KEY_SEMICOLON : return ';';
		case KEY_BACKSLASH : return '\\';
		case KEY_COMMA : return ',';
		case KEY_DOT : return '.';
		case KEY_FORESLHASH : return '/';
		case KEY_SPACE : return ' ';
		default : return 0;
	}
}

uint8 get_keycode(char ch) {
	switch(ch){
		case 'A' : return KEY_A;
		case 'B' : return KEY_B;
		case 'C' : return KEY_C;
		case 'D' : return KEY_D;
		case 'E' : return KEY_E;
		case 'F' : return KEY_F;
		case 'G' : return KEY_G;
		case 'H' : return KEY_H;
		case 'I' : return KEY_I;
		case 'J' : return KEY_J;
		case 'K' : return KEY_K;
		case 'L' : return KEY_L;
		case 'M' : return KEY_M;
		case 'N' : return KEY_N;
		case 'O' : return KEY_O;
		case 'P' : return KEY_P;
		case 'Q' : return KEY_Q;
		case 'R' : return KEY_R;
		case 'S' : return KEY_S;
		case 'T' : return KEY_T;
		case 'U' : return KEY_U;
		case 'V' : return KEY_V;
		case 'W' : return KEY_W;
		case 'X' : return KEY_X;
		case 'Y' : return KEY_Y;
		case 'Z' : return KEY_Z;
		case '1' : return KEY_1;
		case '2' : return KEY_2;
		case '3' : return KEY_3;
		case '4' : return KEY_4;
		case '5' : return KEY_5;
		case '6' : return KEY_6;
		case '7' : return KEY_7;
		case '8' : return KEY_8;
		case '9' : return KEY_9;
		case '0' : return KEY_0;
		case '-' : return KEY_MINUS;
		// case "=" : return KEY_EQUAL;
		case '[' : return KEY_SQUARE_OPEN_BRACKET;
		case ']' : return KEY_SQUARE_CLOSE_BRACKET;
		case ';' : return KEY_SEMICOLON;
		case '\\' : return KEY_BACKSLASH;
		case ',' : return KEY_COMMA;
		case '.' : return KEY_DOT;
		case '/' : return KEY_FORESLHASH;
		case ' ' : return KEY_SPACE;
		default : return 0;
	}
}

bool is_normal_char(uint8 key_code) {
	switch(key_code){
		case KEY_A : return true; // 'A';
		case KEY_B : return true; // 'B';
		case KEY_C : return true; // 'C';
		case KEY_D : return true; // 'D';
		case KEY_E : return true; // 'E';
		case KEY_F : return true; // 'F';
		case KEY_G : return true; // 'G';
		case KEY_H : return true; // 'H';
		case KEY_I : return true; // 'I';
		case KEY_J : return true; // 'J';
		case KEY_K : return true; // 'K';
		case KEY_L : return true; // 'L';
		case KEY_M : return true; // 'M';
		case KEY_N : return true; // 'N';
		case KEY_O : return true; // 'O';
		case KEY_P : return true; // 'P';
		case KEY_Q : return true; // 'Q';
		case KEY_R : return true; // 'R';
		case KEY_S : return true; // 'S';
		case KEY_T : return true; // 'T';
		case KEY_U : return true; // 'U';
		case KEY_V : return true; // 'V';
		case KEY_W : return true; // 'W';
		case KEY_X : return true; // 'X';
		case KEY_Y : return true; // 'Y';
		case KEY_Z : return true; // 'Z';
		case KEY_1 : return true; // '1';
		case KEY_2 : return true; // '2';
		case KEY_3 : return true; // '3';
		case KEY_4 : return true; // '4';
		case KEY_5 : return true; // '5';
		case KEY_6 : return true; // '6';
		case KEY_7 : return true; // '7';
		case KEY_8 : return true; // '8';
		case KEY_9 : return true; // '9';
		case KEY_0 : return true; // '0';
		case KEY_MINUS : return true; // '-';
		case KEY_EQUAL : return true; // '=';
		case KEY_SQUARE_OPEN_BRACKET : return true; // '[';
		case KEY_SQUARE_CLOSE_BRACKET : return true; // ']';
		case KEY_SEMICOLON : return true; // ';';
		case KEY_BACKSLASH : return true; // '\\';
		case KEY_COMMA : return true; // ',';
		case KEY_DOT : return true; // '.';
		case KEY_FORESLHASH : return true; // '/';
		case KEY_SPACE : return true; // ' ';
		default: return false;
	}
}

char char_tolower(char ch) {
	char c = ch;
	if(c>='A' && c<='Z') //or if(c > 64 && c < 91)
		c += 32;
	return c;
}

char char_toupper(char ch) {
	char c = ch;
	if( c >= 'a' && c <= 'z' )
		c = c - 32;
	return c;
}

char * string_tolower(char str[]) {
	for(int i = 0; i < strlen_int(str); i++)
		str[i] = char_tolower(str[i]);
	return str;
}

char * string_toupper(char str[]) {
	for(int i = 0; i < strlen_int(str); i++)
		str[i] = char_toupper(str[i]);
	return str;
}