#include<stdio.h>
#include<stdlib.h>
#include<linux/input.h>

char *c2k;

void init_c2k(void){
	c2k = new char[128];

	c2k['1'] = KEY_1		;
	c2k['2'] = KEY_2		;
	c2k['3'] = KEY_3		;
	c2k['4'] = KEY_4		;
	c2k['5'] = KEY_5		;
	c2k['6'] = KEY_6		;
	c2k['7'] = KEY_7		;
	c2k['8'] = KEY_8		;
	c2k['9'] = KEY_9		;
	c2k['0'] = KEY_0		;
	c2k['-'] = KEY_MINUS	;
	c2k['='] = KEY_EQUAL	;
	c2k['q'] = KEY_Q		;
	c2k['w'] = KEY_W		;
	c2k['e'] = KEY_E		;
	c2k['r'] = KEY_R		;
	c2k['t'] = KEY_T		;
	c2k['y'] = KEY_Y		;
	c2k['u'] = KEY_U		;
	c2k['i'] = KEY_I		;
	c2k['o'] = KEY_O		;
	c2k['p'] = KEY_P		;
	c2k['['] = KEY_LEFTBRACE	;
	c2k[']'] = KEY_RIGHTBRACE	;
	c2k['a'] = KEY_A		;
	c2k['s'] = KEY_S		;
	c2k['d'] = KEY_D		;
	c2k['f'] = KEY_F		;
	c2k['g'] = KEY_G		;
	c2k['h'] = KEY_H		;
	c2k['j'] = KEY_J		;
	c2k['k'] = KEY_K		;
	c2k['l'] = KEY_L		;
	c2k[';'] = KEY_SEMICOLON	;
	c2k['"'] = KEY_APOSTROPHE	;
	c2k['~'] = KEY_GRAVE	;
	c2k['\\'] = KEY_BACKSLASH	;
	c2k['z'] = KEY_Z		;
	c2k['x'] = KEY_X		;
	c2k['c'] = KEY_C		;
	c2k['v'] = KEY_V		;
	c2k['b'] = KEY_B		;
	c2k['n'] = KEY_N		;
	c2k['m'] = KEY_M		;
	c2k[','] = KEY_COMMA	;
	c2k['.'] = KEY_DOT		;
	c2k['/'] = KEY_SLASH	;


	c2k['B'] = KEY_BACKSPACE	;
	c2k['T'] = KEY_TAB		;
	c2k['R'] = KEY_ENTER	;
	c2k['C'] = KEY_LEFTCTRL	;
	c2k['S'] = KEY_LEFTSHIFT	;
	c2k['A'] = KEY_LEFTALT	;
	c2k['M'] = KEY_RIGHTALT	;
	c2k['P'] = KEY_SPACE	;
	c2k['W'] = KEY_LEFTMETA;
	c2k['D'] = KEY_DELETE;
	c2k['E'] = KEY_ESC		;

	c2k['!'] = KEY_F1		;
	c2k['@'] = KEY_F2		;
	c2k['#'] = KEY_F3		;
	c2k['$'] = KEY_F4		;
	c2k['%'] = KEY_F5		;
	c2k['^'] = KEY_F6		;
	c2k['&'] = KEY_F7		;
	c2k['*'] = KEY_F8		;
	c2k['('] = KEY_F9		;
	c2k[')'] = KEY_F10		;
	c2k['_'] = KEY_F11		;
	c2k['+'] = KEY_F12		;

	c2k['K'] = KEY_UP		;
	c2k['J'] = KEY_DOWN	;
	c2k['H'] = KEY_LEFT	;
	c2k['L'] = KEY_RIGHT;

	printf("c2k inited\n");
}

