#include <fstream>
#include "TextBuffer.hpp"

void TextBuffer::read_file(const char *file_name)
{
    lines.clear();
    amount_rows = 0;
    std::ifstream infile(file_name);
    std::string line;
    while (std::getline(infile, line))
    {
        lines.push_back(line);
        ++amount_rows;
    }
}

int TextBuffer::get_amount_rows() const
{
    return amount_rows;
}

const std::string &TextBuffer::get_line(int row)
{
    return lines.at(row);
}

std::_Deque_iterator<std::string, const std::string &, const std::string *> TextBuffer::begin() const
{
    return lines.cbegin();
}

std::_Deque_iterator<std::string, const std::string &, const std::string *> TextBuffer::end() const
{
    return lines.cend(); 
}
