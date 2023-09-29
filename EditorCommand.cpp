#include "EditorCommand.hpp"

EditorCommand::EditorCommand(std::shared_ptr<EditorState> state, Input action)
{
    this->state = state;
    this->action = action;
}

AfterCommandInstruction EditorCommand::execute()
{
    switch (action.action_type)
    {
        case SAVE:
            state->buffer->write_file();
            return PASS;
        case QUIT:
            return STOP;
        default:
            return PASS;
    }
}
