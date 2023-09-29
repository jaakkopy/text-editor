#ifndef EDITOR_STATE_HPP
#define EDITOR_STATE_HPP

#include <memory>

#include "TextBuffer.hpp"
#include "Position.hpp"
#include "EditorSettings.hpp"

struct EditorState
{
    EditorState()
    {
        this->position = std::make_shared<Position>();
        this->buffer = std::make_shared<TextBuffer>();
        this->settings = std::make_shared<EditorSettings>();
    }
    std::shared_ptr<TextBuffer> buffer;
    std::shared_ptr<Position> position;
    std::shared_ptr<EditorSettings> settings;
};

#endif