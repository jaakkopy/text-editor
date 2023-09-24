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

void TextBuffer::write_byte(char c, int row, int col)
{
    while (row >= (int)lines.size())
    {
        lines.push_back(std::string());
    }
    std::string &r = lines.at(row);
    if (col >= (int)r.length())
    {
        r.push_back(c);
    }
    else
    {
        r.insert(r.begin() + col, c);
    }
}

void TextBuffer::erase_byte(int row, int col)
{
    if (row >= (int)lines.size())
        return;
    std::string &r = lines.at(row);
    if (col >= (int)r.length())
        return;
    r.erase(r.begin() + col);
}