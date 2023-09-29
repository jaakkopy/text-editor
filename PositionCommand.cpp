#include "PositionCommand.hpp"
#include "Position.hpp"

PositionCommand::PositionCommand(std::shared_ptr<Position> position, std::shared_ptr<TextBuffer> buf, std::shared_ptr<EditorSettings> settings, Input action)
{
    this->pos = position;
    this->buf = buf;
    this->settings = settings;
    this->action = action;
}

AfterCommandInstruction PositionCommand::execute()
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

AfterCommandInstruction PositionCommand::update_position_left()
{
    int np = pos->col_pos - 1;
    if (np >= 0)
    {
        pos->col_pos = np;
        return PASS;
    }
    if (pos->col_offset > 0)
    {
        pos->col_offset -= 1;
        return DRAW_BUF;
    }
    return PASS;
}

AfterCommandInstruction PositionCommand::update_position_right()
{
    int np = pos->col_pos + 1;
    if (np < settings->get_visible_columns())
    {
        pos->col_pos = np;
        return PASS;
    }
    if (pos->col_offset < (int)buf->get_line(pos->get_offset_adjusted_row()).length() - settings->get_visible_columns() - 1)
    {
        pos->col_offset += 1;
        return DRAW_BUF;
    }
    return PASS;
}

AfterCommandInstruction PositionCommand::update_position_up()
{
    int np = pos->row_pos - 1;
    if (np >= 0)
    {
        pos->row_pos = np;
        return PASS;
    }
    if (pos->row_offset > 0)
    {
        pos->row_offset -= 1;
        return DRAW_BUF;
    }
    return PASS;
}

AfterCommandInstruction PositionCommand::update_position_down()
{
    int np = pos->row_pos + 1;
    if (np < settings->get_visible_rows())
    {
        pos->row_pos = np;
        return PASS;
    }
    if (pos->row_offset < buf->get_amount_rows() - settings->get_visible_rows() - 1)
    {
        pos->row_offset += 1;
        return DRAW_BUF;
    }
    return PASS;
}