#include <cstdlib>
#include <unistd.h>
#include <termios.h>
#include <cstdio>
#include <ctype.h>
#include <errno.h>
#include <memory>

#include "EditorSettings.hpp"
#include "Painter.hpp"
#include "InputReader.hpp"
#include "Position.hpp"
#include "TextBuffer.hpp"
#include "CommandBuilder.hpp"
#include "EditorState.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Please provide a file to open or create\n");
        return 1;
    }
    std::shared_ptr<struct EditorState> state = std::make_shared<EditorState>();
    state->buffer->read_file(argv[1]);
    InputReader input;
    CommandBuilder command_builder;
    Painter painter;
    
    state->settings->enable_raw_mode();
    painter.begin_drawing();
    painter.clear_screen();
    painter.draw_cursor(state->position);
    painter.end_drawing();
    state->settings->update_window_size();
    painter.begin_drawing();
    painter.draw_text_buffer(state);
    painter.draw_cursor(state->position);
    painter.end_drawing();

    bool running = true;
    while (running)
    {
        Input action = input.read_input();
        Command *cmd = command_builder.create_action_performer(state, action);
        painter.begin_drawing();
        switch (cmd->execute())
        {
            case STOP:
                running = false;
                break;
            case DRAW_LINE:
                painter.draw_line(state);
                break;
            case DRAW_BUF:
                painter.draw_text_buffer(state);
                break;
            case PASS:
                break;
        }
        delete cmd;
        painter.draw_cursor(state->position);
        painter.end_drawing();
    }

    painter.begin_drawing();
    painter.clear_screen();
    painter.end_drawing();
    return 0;
}