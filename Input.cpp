#include <errno.h>
#include <cstdlib>
#include <unistd.h>
#include "Input.hpp"
#include "macros.hpp"
#include "Cursor.hpp"
#include "key_definitions.hpp"

int Input::read_byte()
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

int Input::read_input()
{
    char c = read_byte();
    if (c == '\x1b')
    {
        return check_escape_sequence();
    }
    return c;
}

int Input::check_escape_sequence()
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
        switch (esc_seq[1])
        {
            case 'A': return CURSOR_UP;
            case 'B': return CURSOR_DOWN;
            case 'C': return CURSOR_RIGHT;
            case 'D': return CURSOR_LEFT;
        }
    }
    return '\x1b';
}
