#include "Position.hpp"

/*
int Position::get_row() const
{
    return row_pos;
}

int Position::get_col() const
{
    return col_pos;
}

int Position::get_row_offset() const
{
    return row_offset;
}

int Position::get_col_offset() const
{
    return col_offset;
}

int Position::get_offset_adjusted_row() const
{
    return row_pos + row_offset;
}

int Position::get_offset_adjusted_col() const
{
    return col_pos + col_offset;
}

void Position::set_row_pos(int row, const EditorSettings &settings, const TextBuffer &buf)
{
    int curr_row = get_offset_adjusted_row();
    int step = (row - curr_row > 0) - (row - curr_row < 0);
    while (curr_row != row)
    {
        update_row_position(step, settings, buf);
        curr_row += step;
    }
}

void Position::set_col_pos(int col, const EditorSettings &settings, const TextBuffer &buf)
{
    int curr_col = get_offset_adjusted_col();
    int step = (col - curr_col > 0) - (col - curr_col < 0);
    while (curr_col != col)
    {
        update_col_position(step, settings, buf);
        curr_col += step;
    }
}

bool Position::update_row_position(int step, const EditorSettings &settings, const TextBuffer &buf)
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
    int visible_rows = settings.get_visible_rows();
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

bool Position::update_col_position(int step, const EditorSettings &settings, const TextBuffer &buf)
{
    int new_pos = col_pos + step; 
    if (new_pos + col_offset == -1)
        return false;
    bool outside_file_buffer = (buf.get_amount_rows() == 0) || (new_pos + col_offset >= (int)buf.get_line(row_pos + row_offset).length());
    // no content to move the cursor over
    if (outside_file_buffer)
    {
        if (abs(new_pos - col_pos) == 1)
            col_pos = new_pos;
        return false;
    }
    int visible_cols = settings.get_visible_columns();
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
*/

PositionUpdateCommand::PositionUpdateCommand(std::shared_ptr<Position> position, Input action)
{
    this->position = position;
    this->action = action;
}

AfterCommandInstruction PositionUpdateCommand::execute()
{
    switch (action.action_type)
    {
        case POSITION_UP:
            return update_position_up();
        case POSITION_DOWN:
            return update_position_down();
        case POSITION_LEFT:
            return update_position_left();
        case POSITION_RIGHT:
            return update_position_right();
        default:
            return PASS;
    }
}

AfterCommandInstruction PositionUpdateCommand::update_position_left()
{
}

AfterCommandInstruction PositionUpdateCommand::update_position_right()
{
}

AfterCommandInstruction PositionUpdateCommand::update_position_up()
{
}

AfterCommandInstruction PositionUpdateCommand::update_position_down()
{
}
