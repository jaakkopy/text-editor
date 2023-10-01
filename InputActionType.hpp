#ifndef INPUT_ACTION_TYPE_HPP
#define INPUT_ACTION_TYPE_HPP

enum InputActionType
{
    WRITE = 1000,
    ERASE,
    NEWLINE,
    TAB,
    POSITION_UP,
    POSITION_DOWN,
    POSITION_LEFT,
    POSITION_RIGHT,
    QUIT,
    SAVE
};

struct Input
{
    InputActionType action_type;
    char b;
};

#endif