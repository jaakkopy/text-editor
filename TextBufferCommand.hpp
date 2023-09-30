#ifndef TEXT_BUFFER_COMMAND_HPP
#define TEXT_BUFFER_COMMAND_HPP

#include <memory>
#include "Command.hpp"
#include "InputActionType.hpp"
#include "EditorState.hpp"

class TextBufferCommand : public Command
{
public:
    TextBufferCommand(std::shared_ptr<EditorState> state, Input action);
    AfterCommandInstruction execute();
private:
    std::shared_ptr<EditorState> state;
    Input action;
    AfterCommandInstruction insert_byte();
    AfterCommandInstruction split_with_newline();
    AfterCommandInstruction erase_byte();
};

#endif