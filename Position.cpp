#include "Position.hpp"

PositionUpdateCommand::PositionUpdateCommand(std::shared_ptr<Position> position, std::shared_ptr<TextBuffer> buf, std::shared_ptr<EditorSettings> settings, Input action)
{
    this->pos = position;
    this->buf = buf;
    this->settings = settings;
    this->action = action;
}

AfterCommandInstruction PositionUpdateCommand::execute()
{
    switch (action.action_type)
    {
        case POSITION_UP:
            return update_position_up();
        case POSITION_DOWN:
            return update_position_down();
        case POSITION_LEFT:
            return update_position_left();
        case POSITION_RIGHT:
            return update_position_right();
        default:
            return PASS;
    }
}

AfterCommandInstruction PositionUpdateCommand::update_position_left()
{
    // TODO
    return PASS;
}

AfterCommandInstruction PositionUpdateCommand::update_position_right()
{
    // TODO
    return PASS;
}

AfterCommandInstruction PositionUpdateCommand::update_position_up()
{
    // TODO
    return PASS;
}

AfterCommandInstruction PositionUpdateCommand::update_position_down()
{
    // TODO
    return PASS;
}
