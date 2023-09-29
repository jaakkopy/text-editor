#ifndef CURSOR_HPP
#define CURSOR_HPP

struct Position
{
    int row_pos = 0;
    int col_pos = 0;
    int row_offset = 0;
    int col_offset = 0;
    int get_offset_adjusted_row() const {return row_pos + row_offset;}
    int get_offset_adjusted_col() const {return col_pos + col_offset;}
};

#endif