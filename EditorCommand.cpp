#include "EditorCommand.hpp"

EditorCommand::EditorCommand(std::shared_ptr<TextBuffer> buf, Input action)
{
    this->buf = buf;
    this->action = action;
}

bool EditorCommand::execute()
{
    switch (action.action_type)
    {
        case SAVE:
            buf->write_file();
            return true;
        case QUIT:
            return false;
        default:
            return true;
    }
}
