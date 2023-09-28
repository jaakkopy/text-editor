#ifndef ACTION_BUILDER_HPP
#define ACTION_BUILDER_HPP

#include "InputReader.hpp"
#include "Command.hpp"
#include "TextBuffer.hpp"
#include "Position.hpp"
#include <memory>

class CommandBuilder
{
public:
    Command *create_action_performer(std::shared_ptr<TextBuffer> buf, std::shared_ptr<Position> position, std::shared_ptr<EditorSettings> settings, Input action);
};

#endif