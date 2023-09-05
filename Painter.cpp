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

void Painter::draw_text_buffer(const EditorSettings &settings, const TextBuffer &buf, const Cursor &cursor)
{
    clear_screen();
    auto it = buf.begin() + cursor.get_row_offset();
    auto end = buf.end();
    int visible_rows = settings.get_rows();
    while (it != end && visible_rows)
    {
        int line_length = (int)(*it).length();
        int offset_length = line_length - cursor.get_col_offset();
        // if the remainder of the line is visible with this column offset
        if (offset_length > 0)
        {
            add_to_buf((*it).substr(cursor.get_col_offset(), settings.get_cols()).c_str());
        }
        
        if (visible_rows > 1)
            add_to_buf("\r\n");
        ++it;
        --visible_rows;
    }
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
