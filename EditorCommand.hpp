#ifndef EDITOR_COMMANDS_HPP
#define EDITOR_COMMANDS_HPP

#include <memory>
#include "Command.hpp"
#include "InputActionType.hpp"
#include "EditorState.hpp"

class EditorCommand : public Command
{
public:
    EditorCommand(std::shared_ptr<EditorState> state, Input action);
    AfterCommandInstruction execute();
private:
    Input action;
    std::shared_ptr<EditorState> state;
};

#endif