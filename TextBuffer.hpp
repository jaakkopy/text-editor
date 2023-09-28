#ifndef TEXTBUFFER_HPP
#define TEXTBUFFER_HPP

#include <vector>
#include <string>
#include <memory>
#include "Command.hpp"
#include "InputActionType.hpp"
#include "Position.hpp"

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
private:
    std::string file_name;
    std::vector<std::string> lines;
};

class TextBufferCommand : public Command
{
public:
    TextBufferCommand(std::shared_ptr<TextBuffer> buf, std::shared_ptr<Position> pos, Input action);
    AfterCommandInstruction execute();
private:
    std::shared_ptr<TextBuffer> buf;
    std::shared_ptr<Position> pos;
    Input action;
    void insert_byte();
    void split_with_newline();
    void erase_byte();
};

#endif