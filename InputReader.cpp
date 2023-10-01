#include <errno.h>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include "InputReader.hpp"

#define CTRL_KEY(key) (key & 0b00011111)

Input InputReader::read_input()
{
    Input inp;
    inp.b = read_byte();
    if (inp.b == '\x1b')
        inp.b = check_escape_sequence();
    switch (inp.b)
    {
        case 'A': 
            inp.action_type = POSITION_UP;
            break;
        case 'B': 
            inp.action_type = POSITION_DOWN;
            break;
        case 'C': 
            inp.action_type = POSITION_RIGHT;
            break;
        case 'D': 
            inp.action_type = POSITION_LEFT;
            break;
        case BACKSPACE:
            inp.action_type = ERASE;
            break;
        case '\r':
            inp.action_type = NEWLINE;
            break;
        case '\t':
            inp.action_type = TAB;
            break;
        case CTRL_KEY('q'):
            inp.action_type = QUIT;
            break;
        case CTRL_KEY('s'):
            inp.action_type = SAVE;
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
            if (n == -1)
            {
                perror("read"); 
                exit(1);
            }
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
