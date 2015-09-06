#ifndef _LIST_WINDOW_H
#define _LIST_WINDOW_H

#include <ncurses.h>

void lw_initialize(WINDOW* parent);
void lw_end();

void lw_add_program();

#endif
