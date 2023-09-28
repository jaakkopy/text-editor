#include <errno.h>
#include <cstdlib>
#include <unistd.h>
#include "InputReader.hpp"
#include "macros.hpp"

Input InputReader::read_input()
{
    Input inp;
    inp.b = read_byte();
    if (inp.b == '\x1b')
        inp.b = check_escape_sequence();
    switch (inp.b)
    {
        case 'A': 
            inp.action_type = CURSOR_UP;
            break;
        case 'B': 
            inp.action_type = CURSOR_DOWN;
            break;
        case 'C': 
            inp.action_type = CURSOR_RIGHT;
            break;
        case 'D': 
            inp.action_type = CURSOR_LEFT;
            break;
        case BACKSPACE:
            inp.action_type = ERASE;
            break;
        default:
            inp.action_type = WRITE;
    }
    return inp;
}

int InputReader::read_byte()
{
    int n;
    int c;
    while ( (n = read(STDIN_FILENO, &c, 1)) != 1 )
    {
        if (errno != EAGAIN)
        {
            CHECK(n, -1, "read");
        }
        c = 0;
    }
    return c;
}

int InputReader::check_escape_sequence()
{
    char esc_seq[3];
    if (read(STDIN_FILENO, &esc_seq[0], 1) == -1)
    {
        return '\x1b';
    }
    if (read(STDIN_FILENO, &esc_seq[1], 1) == -1)
    {
        return '\x1b';
    }
    if (esc_seq[0] == '[')
    {
        return esc_seq[1];
    }
    return '\x1b';
}
