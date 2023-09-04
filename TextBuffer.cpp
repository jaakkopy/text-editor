#include <fstream>
#include "TextBuffer.hpp"

void TextBuffer::read_file(const char *file_name)
{
    lines.clear();
    std::ifstream infile(file_name);
    std::string line;
    while (std::getline(infile, line))
    {
        lines.push_back(line);
    }
}

int TextBuffer::get_amount_rows() const
{
    return lines.size();
}

const std::string &TextBuffer::get_line(int row) const
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
