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
    infile.close();
    this->file_name = std::string(file_name);
}

int TextBuffer::get_amount_rows() const
{
    return lines.size();
}

const std::string &TextBuffer::get_line(int row) const
{
    return lines.at(row);
}

std::vector<std::string>::const_iterator TextBuffer::begin() const
{
    return lines.cbegin();
}

std::vector<std::string>::const_iterator TextBuffer::end() const
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

void TextBuffer::write_file()
{
    std::ofstream ofile(file_name);
    for (auto it = lines.cbegin(); it != lines.cend(); ++it)
    {
        if (it + 1 != lines.cend())
            ofile << *it << '\n';
        else
            ofile << *it;
    }
    ofile.close();
}

void TextBuffer::split_row_to_lines(int row, int col)
{
    lines.push_back(std::string());
    int end = (int)lines.size() - 1;
    if (end == 0)
        return;
    // Move the rows below one row down
    for (int r = end; r > row + 1; --r)
    {
        lines.at(r) = lines.at(r - 1);
    }
    // Move the right end of the split to the row below
    std::string line = lines.at(row);
    if (col >= (int)line.length() - 1)
    {
        lines.at(row + 1).clear();
    }
    else
    {
        auto left_part = line.substr(0, (size_t)col);
        auto right_part = lines.at(row).substr(col);
        lines.at(row + 1) = right_part;
        lines.at(row) = left_part;
    }
}