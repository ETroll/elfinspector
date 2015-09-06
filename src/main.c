#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>

#include "elf.h"
#include "list_window.h"

void inputloop();
int wprintf(WINDOW* win, int attr, int y, int x, const char* format, ...);

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

    if(argc < 2)
    {
        endwin();
        printf("Usage: elfinspector <path-to-elf>\n");
        return -1;
    }

    raw();
    keypad(stdscr, TRUE);
    noecho();

    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLUE);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);

    getmaxyx(stdscr,row,col);


    WINDOW* main_window = newwin(row, col, 0, 0);

    box(main_window, 0, 0);

    mvwprintw(main_window, 0, 5, "%s", argv[1]);
    //wborder(local_win, '|', '|', '-', '-', '+', '+', '+', '+');
    refresh();
    //wrefresh(main_window);


    Elf_t* elf = elf_open(argv[1]);

    char size_string[200];
    sprintf(size_string, "Size: bytes %ldKB", elf->size/1024);
    mvwprintw(main_window, 0, col-strlen(size_string)-3, "%s", size_string);

    wprintf(main_window, COLOR_PAIR(3) | A_BOLD, 1, 2, "Programs:");
    mvwprintw(main_window, 1, 12, "%d", elf->header->e_phnum);

    wprintf(main_window, COLOR_PAIR(3) | A_BOLD, 2, 2, "Sections:");
    mvwprintw(main_window, 2, 12, "%d", elf->header->e_shnum);

    wprintf(main_window, COLOR_PAIR(3) | A_BOLD, 1, 20, "Arch:");
    mvwprintw(main_window, 1, 27, "%s", elf->machine_description);

    wprintf(main_window, COLOR_PAIR(3) | A_BOLD, 2, 20, "Types:");
    mvwprintw(main_window, 2, 27, "%s", elf->type_description);

    wrefresh(main_window);

    lw_initialize(main_window);


    inputloop();

    lw_end();
    delwin(main_window);
    endwin();
    elf_close(elf);

    return 0;
}

void inputloop()
{
    int ch;
    while(1)
    {
        ch = getch();
        if(ch == 27 || ch == 'q') // ESC
        {
            break;
        }
        else
        {
            usleep(50000);
        }
        //refresh();
    }
}

int wprintf(WINDOW* win, int attr, int y, int x, const char* format, ...)
{
    char dest[4096];
    wattron(win, attr);
    va_list argptr;
    va_start(argptr, format);
    vsprintf(dest, format, argptr);

    int ret = mvwprintw(win, y, x, dest);

    va_end(argptr);
    wattroff(win, attr);
    return ret;
}
