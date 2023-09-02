#include "Cursor.hpp"
#include "key_definitions.hpp"

bool Cursor::update_position(int user_input, const EditorSettings &settings, const TextBuffer &buf)
{
    switch (user_input)
    {
        case CURSOR_UP:    return update_row_position(-1, settings, buf);
        case CURSOR_DOWN:  return update_row_position(1, settings, buf);
        case CURSOR_LEFT:  return update_col_position(-1, settings, buf);
        case CURSOR_RIGHT: return update_col_position(1, settings, buf);
    }
    return false;
}

int Cursor::get_row() const
{
    return row_pos;
}

int Cursor::get_col() const
{
    return col_pos;
}

int Cursor::get_row_offset() const
{
    return row_offset;
}

int Cursor::get_col_offset() const
{
    return col_offset;
}

bool Cursor::update_row_position(int step, const EditorSettings &settings, const TextBuffer &buf)
{
    int new_pos = row_pos + step;
    int visible_rows = settings.get_rows();
    if (new_pos < visible_rows && new_pos >= 0)
    {
        row_pos = new_pos;
    }
    return false;
}

bool Cursor::update_col_position(int step, const EditorSettings &settings, const TextBuffer &buf)
{
    int new_pos = col_pos + step; 
    int visible_cols = settings.get_cols();
    if (new_pos < visible_cols && new_pos >= 0)
    {
        col_pos = new_pos;
    }
    return false;
}