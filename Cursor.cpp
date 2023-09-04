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
    if (new_pos + row_offset == -1)
        return false;
    bool outside_file_buffer = new_pos + row_offset >= buf.get_amount_rows();
    // no content to move the cursor over
    if (outside_file_buffer)
    {
        return false;
    }
    int visible_rows = settings.get_rows();
    // if the new position is within the terminal window's view
    if (new_pos < visible_rows && new_pos >= 0)
    {
        row_pos = new_pos;
    }
    // else if the position goes out of bounds for terminal window's visiblity, but the position is within the file buffer
    else if (!outside_file_buffer)
    {
        // scroll down
        if (new_pos == visible_rows)
        {
            row_offset = row_offset + 1;
        }
        // scroll up
        else
        {
            row_offset = row_offset - 1;
            row_offset = row_offset < 0 ? 0 : row_offset;
        }
        return true;
    }
    return false;
}

bool Cursor::update_col_position(int step, const EditorSettings &settings, const TextBuffer &buf)
{
    int new_pos = col_pos + step; 
    if (new_pos + col_offset == -1)
        return false;
    bool outside_file_buffer = (buf.get_amount_rows() == 0) || (new_pos + col_offset >= (int)buf.get_line(row_pos + row_offset).length());
    // no content to move the cursor over
    if (outside_file_buffer)
    {
        return false;
    }
    int visible_cols = settings.get_cols();
    // if the new position is within the terminal window's view
    if (new_pos < visible_cols && new_pos >= 0)
    {
        col_pos = new_pos;
    }
    // if the new column position goes out of the view of the terminal window, but the line has more content to show
    else if (!outside_file_buffer)
    {
        // scroll right 
        if (new_pos == visible_cols)
        {
            col_offset = col_offset + 1;
        }
        // scroll left 
        else
        {
            col_offset = col_offset - 1;
            col_offset = col_offset < 0 ? 0 : col_offset;
        }
        return true;
    }
    return false;
}