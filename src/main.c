#include <stdio.h>
#include <string.h>
#include <ncurses.h>

void inputloop();

int main(int argc, char** argv)
{
    int row, col;

    initscr();
    if(has_colors() == FALSE)
	{
        endwin();
        printf("Your terminal does not support color\n");
        return -1;
	}

    raw();
    keypad(stdscr, TRUE);
    noecho();

    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLUE);
    init_pair(2, COLOR_RED, COLOR_BLACK);

    getmaxyx(stdscr,row,col);

    inputloop();

    endwin();

    return 0;
}

void inputloop()
{
    int ch;
}
