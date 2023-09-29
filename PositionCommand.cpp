#include "PositionCommand.hpp"
#include "Position.hpp"

PositionCommand::PositionCommand(std::shared_ptr<EditorState> state, Input action)
{
    this->state = state;
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
    int np = state->position->col_pos - 1;
    if (np >= 0)
    {
        state->position->col_pos = np;
        return PASS;
    }
    if (state->position->col_offset > 0)
    {
        state->position->col_offset -= 1;
        return DRAW_BUF;
    }
    return PASS;
}

AfterCommandInstruction PositionCommand::update_position_right()
{
    int np = state->position->col_pos + 1;
    if (np < state->settings->get_visible_columns())
    {
        state->position->col_pos = np;
        return PASS;
    }
    if (state->position->col_offset < (int)state->buffer->get_line(state->position->get_offset_adjusted_row()).length() - state->settings->get_visible_columns() - 1)
    {
        state->position->col_offset += 1;
        return DRAW_BUF;
    }
    return PASS;
}

AfterCommandInstruction PositionCommand::update_position_up()
{
    int np = state->position->row_pos - 1;
    if (np >= 0)
    {
        state->position->row_pos = np;
        return PASS;
    }
    if (state->position->row_offset > 0)
    {
        state->position->row_offset -= 1;
        return DRAW_BUF;
    }
    return PASS;
}

AfterCommandInstruction PositionCommand::update_position_down()
{
    int np = state->position->row_pos + 1;
    if (np < state->settings->get_visible_rows())
    {
        state->position->row_pos = np;
        return PASS;
    }
    if (state->position->row_offset < state->buffer->get_amount_rows() - state->settings->get_visible_rows() - 1)
    {
        state->position->row_offset += 1;
        return DRAW_BUF;
    }
    return PASS;
}