#ifndef TEXTBUFFER_HPP
#define TEXTBUFFER_HPP

#include <deque>
#include <string>

class TextBuffer
{
public:
    void read_file(const char *file_name);
    int get_amount_rows() const;
    const std::string &get_line(int row) const;
    std::_Deque_iterator<std::string, const std::string &, const std::string *> begin() const; 
    std::_Deque_iterator<std::string, const std::string &, const std::string *> end() const; 
    void write_byte(char c, int row, int col);
    void erase_byte(int row, int col);
    void write_file();
private:
    std::string file_name;
    std::deque<std::string> lines;
};

#endif