#ifndef COMMAND_HPP
#define COMMAND_HPP

enum AfterCommandInstruction
{
    PASS,
    DRAW_LINE,
    DRAW_BUF,
    STOP
};

class Command
{
public:
    virtual AfterCommandInstruction execute() = 0;
    virtual ~Command() {}
};

#endif