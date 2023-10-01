#include "CommandBuilder.hpp"
#include "EditorCommand.hpp"
#include "PositionCommand.hpp"
#include "TextBufferCommand.hpp"

Command *CommandBuilder::create_action_performer(std::shared_ptr<EditorState> state, Input action)
{
    switch (action.action_type)
    {
        case POSITION_UP:
        case POSITION_DOWN:
        case POSITION_LEFT:
        case POSITION_RIGHT:
            return new PositionCommand(state, action);
        case WRITE:
        case ERASE:
        case NEWLINE:
        case TAB:
            return new TextBufferCommand(state, action);
        case QUIT:
        case SAVE:
            return new EditorCommand(state, action);
    }
    return nullptr;
}