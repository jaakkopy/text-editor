#include <cstdlib>
#include <unistd.h>
#include <termios.h>
#include <cstdio>
#include <ctype.h>
#include <errno.h>
#include "EditorSettings.hpp"
#include "Painter.hpp"
#include "Input.hpp"
#include "Cursor.hpp"
#include "macros.hpp"
#include "key_definitions.hpp"
#include "TextBuffer.hpp"

void init_editor(EditorSettings &settings, Painter &painter);

int main(int argc, char *argv[])
{
    Input input;
    Painter painter;
    EditorSettings settings;
    Cursor cursor;
    TextBuffer buf;
    if (argc > 1)
    {
        buf.read_file(argv[1]);
    }
    else
    {
        fprintf(stderr, "No file given\n");
        return 1;
    }
    init_editor(settings, painter);
    settings.update_window_size();
    painter.begin_drawing();
    painter.draw_text_buffer(settings, buf, cursor);
    painter.draw_cursor(0, 0);
    painter.end_drawing();

    bool running = true;
    bool should_redraw = false;
    bool write_char = false;
    bool erase_char = false;

    while (running)
    {
        int c = input.read_input();
        painter.begin_drawing();
        switch (c)
        {
        case CTRL_KEY('q'):
            running = false;
            break;
        case CTRL_KEY('s'):
            buf.write_file();
            break;
        case CURSOR_UP:
        case CURSOR_DOWN:
        case CURSOR_LEFT:
        case CURSOR_RIGHT:
            should_redraw = cursor.update_position(c, settings, buf);
            break;
        case BACKSPACE:
            erase_char = true;
            break;
        default:
            write_char = true;
        }
        if (should_redraw)
        {
            painter.draw_text_buffer(settings, buf, cursor);
            should_redraw = false;
        }
        if (erase_char)
        {
            cursor.update_position(CURSOR_LEFT, settings, buf);
            buf.erase_byte(cursor.get_offset_adjusted_row(), cursor.get_offset_adjusted_col());
            painter.draw_line(settings, buf, cursor);
            erase_char = false;
        }
        if (write_char)
        {
            buf.write_byte((char)c, cursor.get_offset_adjusted_row(), cursor.get_offset_adjusted_col());
            cursor.update_position(CURSOR_RIGHT, settings, buf);
            painter.draw_line(settings, buf, cursor);
            write_char = false;
        }
        painter.draw_cursor(cursor.get_row(), cursor.get_col());
        painter.end_drawing();
    }

    painter.begin_drawing();
    painter.clear_screen();
    painter.end_drawing();
    return 0;
}

void init_editor(EditorSettings &settings, Painter &painter)
{
    settings.enable_raw_mode();
    painter.begin_drawing();
    painter.clear_screen();
    painter.draw_cursor(0, 0);
    painter.end_drawing();
}