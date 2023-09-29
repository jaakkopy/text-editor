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
    void insert_byte();
    void split_with_newline();
    void erase_byte();
};

#endif