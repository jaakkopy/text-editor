#include "EditorCommand.hpp"

EditorCommand::EditorCommand(std::shared_ptr<TextBuffer> buf, Input action)
{
    this->buf = buf;
    this->action = action;
}

AfterCommandInstruction EditorCommand::execute()
{
    switch (action.action_type)
    {
        case SAVE:
            buf->write_file();
            return PASS;
        case QUIT:
            return STOP;
        default:
            return PASS;
    }
}
