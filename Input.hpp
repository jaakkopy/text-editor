#ifndef INPUT_HPP
#define INPUT_HPP

class Input
{
public:
    int read_byte();
    int read_input();
private:
    int check_escape_sequence();
};

#endif