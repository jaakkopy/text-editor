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

void Painter::draw_cursor(const std::shared_ptr<Position> position)
{
    char b[32];
    snprintf(b, sizeof(b), "\x1b[%d;%dH", position->row_pos + 1, position->col_pos + 1);
    add_to_buf(b);
}

void Painter::draw_text_buffer(const std::shared_ptr<EditorState> state)
{
    clear_screen();
    auto it = state->buffer->begin() + state->position->row_offset;
    auto end = state->buffer->end();
    int visible_rows = state->settings->get_visible_rows();
    while (it != end && visible_rows)
    {
        int line_length = (int)(*it).length();
        int offset_length = line_length - state->position->col_offset;
        // if the remainder of the line is visible with this column offset
        if (offset_length > 0)
        {
            add_to_buf((*it).substr(state->position->col_offset, state->settings->get_visible_columns()).c_str());
        }

        if (visible_rows > 1)
            add_to_buf("\r\n");
        ++it;
        --visible_rows;
    }
}

void Painter::draw_line(const std::shared_ptr<EditorState> state)
{
    draw_cursor(state->position);
    add_to_buf("\x1b[K");
    auto line = state->buffer->get_line(state->position->get_offset_adjusted_row());
    int line_length = (int)line.length();
    int offset_length = line_length - state->position->col_offset;
    if (offset_length > 0)
    {
        add_to_buf(line.substr(state->position->col_offset, state->settings->get_visible_columns()).c_str());
    }
    draw_cursor(state->position);
}

void Painter::draw_char(int c)
{
    add_to_buf(c);
}

void Painter::add_to_buf(const char *text)
{
    buf.insert(buf.end(), text, text + strlen(text));
}

void Painter::add_to_buf(char c)
{
    buf.push_back(c);
}

void Painter::hide_cursor()
{
    add_to_buf("\x1b[?25l");
}

void Painter::show_cursor()
{
    add_to_buf("\x1b[?25h");
}