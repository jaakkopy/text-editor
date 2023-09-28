#ifndef ACTION_BUILDER_HPP
#define ACTION_BUILDER_HPP

#include "InputReader.hpp"
#include "Command.hpp"

class CommandBuilder
{
    Command create_action_performer(Input action);
};

#endif