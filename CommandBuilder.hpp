#ifndef ACTION_BUILDER_HPP
#define ACTION_BUILDER_HPP

#include <memory>

#include "InputReader.hpp"
#include "Command.hpp"
#include "EditorState.hpp"

class CommandBuilder
{
public:
    Command *create_action_performer(std::shared_ptr<EditorState> state, Input action);
};

#endif