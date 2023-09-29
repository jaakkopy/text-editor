#ifndef EDITOR_STATE_HPP
#define EDITOR_STATE_HPP

#include <memory>

#include "TextBuffer.hpp"
#include "Position.hpp"
#include "EditorSettings.hpp"

struct EditorState
{
    EditorState(std::shared_ptr<Position> position, std::shared_ptr<TextBuffer> buf, std::shared_ptr<EditorSettings> settings)
    {
        this->position = position;
        this->buffer = buf;
        this->settings = settings;
    }
    std::shared_ptr<TextBuffer> buffer;
    std::shared_ptr<Position> position;
    std::shared_ptr<EditorSettings> settings;
};

#endif