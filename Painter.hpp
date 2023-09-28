#ifndef PAINTER_HPP
#define PAINTER_HPP

#include <vector>
#include "EditorSettings.hpp"
#include "Position.hpp"
#include "TextBuffer.hpp"

class Painter
{
public:
    void begin_drawing();
    void end_drawing();
    void draw_cursor(int row, int col);
    void draw_text_buffer(const EditorSettings &settings, const TextBuffer &buf, const Position &cursor);
    void draw_line(const EditorSettings &settings, const TextBuffer &buf, const Position &cursor);
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