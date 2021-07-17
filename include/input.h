#ifndef INPUT_H
#define INPUT_H

#include "basic.h"

typedef struct Input_controller {
	Bool w;
	Bool a;
	Bool s;
	Bool d;
	Bool esc;
} input_controller;

input_controller keys;

void input_boot();

int input(Bool *gameover);

#endif /* INPUT_H */
