#ifndef POSITION_UPDATE_COMMAND_HPP
#define POSITION_UPDATE_COMMAND_HPP

#include <memory>

#include "EditorSettings.hpp"
#include "Command.hpp"
#include "InputActionType.hpp"
#include "TextBuffer.hpp"
#include "Position.hpp"

class PositionCommand : public Command
{
public:
    PositionCommand(std::shared_ptr<Position> position, std::shared_ptr<TextBuffer> buf, std::shared_ptr<EditorSettings> settings, Input action);
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