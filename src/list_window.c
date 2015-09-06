#include "list_window.h"

static WINDOW* parent_window;
static WINDOW* program_window;
static WINDOW* section_window;
static unsigned int width;
static unsigned int height;

void lw_initialize(WINDOW* parent)
{
    unsigned int parent_height, parent_width;
    getmaxyx(parent, parent_height, parent_width);

    width = (parent_width-2) / 2;
    height = parent_height - 5;

    section_window = newwin(height, width, 4, 1);
    box(section_window, 0, 0);
    mvwprintw(section_window, 0, 3, "[Sections][Programs]");
    wrefresh(section_window);


}

void lw_end()
{
    delwin(section_window);
}
