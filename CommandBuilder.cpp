#include "CommandBuilder.hpp"
#include "EditorCommand.hpp"

Command *CommandBuilder::create_action_performer(std::shared_ptr<TextBuffer> buf, std::shared_ptr<Position> position, Input action)
{
    switch (action.action_type)
    {
        case POSITION_UP:
        case POSITION_DOWN:
        case POSITION_LEFT:
        case POSITION_RIGHT:
            return new PositionUpdateCommand(position, action);
        case WRITE:
        case ERASE:
        case NEWLINE:
            return new TextBufferCommand(buf, position, action);
        case QUIT:
        case SAVE:
            return new EditorCommand(buf, action);
    }
    return nullptr;
}