#ifndef TEXTBUFFER_HPP
#define TEXTBUFFER_HPP

#include <vector>
#include <string>

class TextBuffer
{
public:
    void read_file(const char *file_name);
    int get_amount_rows() const;
    const std::string &get_line(int row) const;
    std::vector<std::string>::const_iterator begin() const; 
    std::vector<std::string>::const_iterator end() const; 
    void write_byte(char c, int row, int col);
    void erase_byte(int row, int col);
    void write_file();
    void split_row_to_lines(int row, int col);
    void join_lines(int row1, int row2);
private:
    std::string file_name;
    std::vector<std::string> lines;
};

#endif