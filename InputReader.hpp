#ifndef INPUT_HPP
#define INPUT_HPP

#define BACKSPACE 127

#include "InputActionType.hpp"


struct Input
{
    InputActionType action_type;
    char b;
};

class InputReader
{
public:
    Input read_input();
private:
    int read_byte();
    int check_escape_sequence();
};

#endif