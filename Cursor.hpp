#ifndef CURSOR_HPP
#define CURSOR_HPP

#include "EditorSettings.hpp"
#include "TextBuffer.hpp"

class Cursor
{
public:
    bool update_position(int user_input, const EditorSettings &settings, const TextBuffer &buf);
    int get_row() const;
    int get_col() const;
    int get_row_offset() const;
    int get_col_offset() const;
private:
    bool update_row_position(int step, const EditorSettings &settings, const TextBuffer &buf);
    bool update_col_position(int step, const EditorSettings &settings, const TextBuffer &buf);
    // Note. These are 0-indexed, but the escape sequence expects 1-indexed numbers.
    int row_pos = 0;
    int col_pos = 0;
    int row_offset = 0;
    int col_offset = 0;
};

#endif