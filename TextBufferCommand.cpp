#include "TextBufferCommand.hpp"
#include "PositionCommand.hpp"

TextBufferCommand::TextBufferCommand(std::shared_ptr<EditorState> state, Input action)
{
    this->state = state;
    this->action = action;
}

AfterCommandInstruction TextBufferCommand::execute()
{
    switch (action.action_type)
    {
    case WRITE:
        return insert_byte();
    case ERASE:
        return erase_byte();
    case NEWLINE:
        return split_with_newline();
    default:
        return PASS;
    }
}

AfterCommandInstruction TextBufferCommand::insert_byte()
{
    // TODO: special characters like tab
    state->buffer->write_byte((char)action.b, state->position->get_offset_adjusted_row(), state->position->get_offset_adjusted_col());
    Input task;
    task.action_type = POSITION_RIGHT;
    PositionCommand cmd = PositionCommand(state, task);
    cmd.execute();
    return DRAW_LINE;
}

AfterCommandInstruction TextBufferCommand::split_with_newline()
{
    state->buffer->split_row_to_lines(state->position->get_offset_adjusted_row(), state->position->get_offset_adjusted_col());
    state->position->col_offset = 0;
    state->position->col_pos= 0;
    state->position->row_pos += 1;
    return DRAW_BUF;
}

AfterCommandInstruction TextBufferCommand::erase_byte()
{
    if (state->position->col_pos > 0)
    {
        Input task;
        task.action_type = POSITION_LEFT;
        PositionCommand cmd = PositionCommand(state, task);
        cmd.execute();
        state->buffer->erase_byte(state->position->get_offset_adjusted_row(), state->position->get_offset_adjusted_col());
    }
    else if (state->position->get_offset_adjusted_row() > 0)
    {
        // Append the current row to the one above and delete the current row.
        int row = state->position->get_offset_adjusted_row();
        int original_len = (int)state->buffer->get_line(row-1).length();
        state->buffer->join_lines(row - 1, row);
        // Update position
        state->position->row_pos -= 1;
        if (state->position->row_pos < 0)
        {
            state->position->row_pos = 0;
            state->position->row_offset -= 1;
        }
        int cp = original_len - 1;
        int vc = state->settings->get_visible_columns();
        if (cp >= vc)
        {
            int inc = cp - vc + 1;
            state->position->col_pos = cp - inc;
            state->position->col_offset += inc;
        }
        else
        {
            state->position->col_pos = cp;
        }
        return DRAW_BUF;
    }
    return DRAW_LINE;
}
