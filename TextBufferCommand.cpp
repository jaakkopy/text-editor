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
        insert_byte();
        return DRAW_LINE;
    case ERASE:
        erase_byte();
        return DRAW_LINE;
    case NEWLINE:
        split_with_newline();
        return DRAW_BUF;
    default:
        return PASS;
    }
}

void TextBufferCommand::insert_byte()
{
    state->buffer->write_byte((char)action.b, state->position->get_offset_adjusted_row(), state->position->get_offset_adjusted_col());
    Input task;
    task.action_type = POSITION_RIGHT;
    PositionCommand cmd = PositionCommand(state, task);
    cmd.execute();
}

void TextBufferCommand::split_with_newline()
{
    state->buffer->split_row_to_lines(state->position->get_offset_adjusted_row(), state->position->get_offset_adjusted_col());
    state->position->col_offset = 0;
    state->position->col_pos= 0;
    state->position->row_pos += 1;
}

void TextBufferCommand::erase_byte()
{
    Input task;
    task.action_type = POSITION_LEFT;
    PositionCommand cmd = PositionCommand(state, task);
    cmd.execute();
    state->buffer->erase_byte(state->position->get_offset_adjusted_row(), state->position->get_offset_adjusted_col());
}
