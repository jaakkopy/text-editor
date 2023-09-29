#include "TextBufferCommand.hpp"

TextBufferCommand::TextBufferCommand(std::shared_ptr<TextBuffer> buf, std::shared_ptr<Position> pos, Input action)
{
    this->buf = buf;
    this->pos = pos;
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
    buf->write_byte((char)action.b, pos->get_offset_adjusted_row(), pos->get_offset_adjusted_col());
    // TODO: update position
}

void TextBufferCommand::split_with_newline()
{
    buf->split_row_to_lines(pos->get_offset_adjusted_row(), pos->get_offset_adjusted_col());
    // TODO: update position
}

void TextBufferCommand::erase_byte()
{
    //pos->col_pos -= 1;
    buf->erase_byte(pos->get_offset_adjusted_row(), pos->get_offset_adjusted_col());
    // TODO: update position
}
