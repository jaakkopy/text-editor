#ifndef POSITION_UPDATE_COMMAND_HPP
#define POSITION_UPDATE_COMMAND_HPP

#include <memory>

#include "Command.hpp"
#include "InputActionType.hpp"
#include "EditorState.hpp"

class PositionCommand : public Command
{
public:
    PositionCommand(std::shared_ptr<EditorState> state, Input action);
    AfterCommandInstruction execute();
private:
    std::shared_ptr<EditorState> state;
    Input action;
    AfterCommandInstruction update_position_left();
    AfterCommandInstruction update_position_right();
    AfterCommandInstruction update_position_up();
    AfterCommandInstruction update_position_down();
    void update_column_after_row_switch(AfterCommandInstruction &aci);
};


#endif