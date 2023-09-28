#ifndef COMMAND_HPP
#define COMMAND_HPP

class Command
{
public:
    virtual bool execute() = 0;
    virtual ~Command() {}
};

#endif