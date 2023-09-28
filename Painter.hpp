#ifndef PAINTER_HPP
#define PAINTER_HPP

#include <vector>
#include <memory>
#include "EditorSettings.hpp"
#include "Position.hpp"
#include "TextBuffer.hpp"

class Painter
{
public:
    void begin_drawing();
    void end_drawing();
    void draw_cursor(int row, int col);
    void draw_text_buffer(const std::shared_ptr<EditorSettings> settings, const std::shared_ptr<TextBuffer> buf, const std::shared_ptr<Position> position);
    void draw_line(const std::shared_ptr<EditorSettings> settings, const std::shared_ptr<TextBuffer> buf, const std::shared_ptr<Position> position);
    void clear_screen();
    void hide_cursor();
    void show_cursor();
    void draw_char(int c);
private:
    std::vector<char> buf;
    void add_to_buf(const char *text);
    void add_to_buf(char c);
};

#endif