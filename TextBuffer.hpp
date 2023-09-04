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
private:
    std::deque<std::string> lines;
};

#endif