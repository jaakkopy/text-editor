#ifndef CURSOR_HPP
#define CURSOR_HPP

#include <memory>

#include "EditorSettings.hpp"
#include "Command.hpp"
#include "InputActionType.hpp"
#include "TextBuffer.hpp"

struct Position
{
    int row_pos = 0;
    int col_pos = 0;
    int row_offset = 0;
    int col_offset = 0;
    int get_offset_adjusted_row() const {return row_pos + row_offset;}
    int get_offset_adjusted_col() const {return col_pos + col_offset;}
};

class PositionUpdateCommand : public Command
{
public:
    PositionUpdateCommand(std::shared_ptr<Position> position, std::shared_ptr<TextBuffer> buf, std::shared_ptr<EditorSettings> settings, Input action);
    AfterCommandInstruction execute();
private:
    std::shared_ptr<Position> pos;
    std::shared_ptr<TextBuffer> buf;
    std::shared_ptr<EditorSettings> settings;
    Input action;
    AfterCommandInstruction update_position_left();
    AfterCommandInstruction update_position_right();
    AfterCommandInstruction update_position_up();
    AfterCommandInstruction update_position_down();
};

#endif