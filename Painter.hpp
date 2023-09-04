#ifndef PAINTER_HPP
#define PAINTER_HPP

#include <vector>
#include "EditorSettings.hpp"
#include "Cursor.hpp"
#include "TextBuffer.hpp"

class Painter
{
public:
    void begin_drawing();
    void end_drawing();
    void draw_cursor(int row, int col);
    void draw_text_buffer(const EditorSettings &settings, const TextBuffer &buf, const Cursor &cursor);
    void clear_screen();
    void hide_cursor();
    void show_cursor();
private:
    std::vector<char> buf;
    void add_to_buf(const char *text);
};

#endif