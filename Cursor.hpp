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
    int get_offset_adjusted_row() const;
    int get_offset_adjusted_col() const;
private:
    bool update_row_position(int step, const EditorSettings &settings, const TextBuffer &buf);
    bool update_col_position(int step, const EditorSettings &settings, const TextBuffer &buf);
    int row_pos = 0;
    int col_pos = 0;
    int row_offset = 0;
    int col_offset = 0;
};

#endif