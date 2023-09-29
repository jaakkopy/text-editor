#include "CommandBuilder.hpp"
#include "EditorCommand.hpp"
#include "PositionCommand.hpp"
#include "TextBufferCommand.hpp"

Command *CommandBuilder::create_action_performer(std::shared_ptr<TextBuffer> buf, std::shared_ptr<Position> position, std::shared_ptr<EditorSettings> settings, Input action)
{
    switch (action.action_type)
    {
        case POSITION_UP:
        case POSITION_DOWN:
        case POSITION_LEFT:
        case POSITION_RIGHT:
            return new PositionCommand(position, buf, settings, action);
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