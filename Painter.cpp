#include <unistd.h>
#include <cstring>
#include <string>
#include "Painter.hpp"

void Painter::begin_drawing()
{
    buf.clear();
}

void Painter::end_drawing()
{
    write(STDOUT_FILENO, buf.data(), buf.size());
}

void Painter::clear_screen()
{
    add_to_buf("\x1b[H");
    add_to_buf("\x1b[2J");
    add_to_buf("\x1b[H");
}

void Painter::draw_cursor(int row, int col)
{
    char b[32];
    snprintf(b, sizeof(b), "\x1b[%d;%dH", row + 1, col + 1);
    add_to_buf(b);
}

void Painter::add_to_buf(const char *text)
{
    buf.insert(buf.end(), text, text + strlen(text));
}

void Painter::hide_cursor()
{
    add_to_buf("\x1b[?25l");
}

void Painter::show_cursor()
{
    add_to_buf("\x1b[?25h");
}
