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

int main(int argc, char *argv[])
{
    std::shared_ptr<TextBuffer> buf = std::make_shared<TextBuffer>(TextBuffer());
    if (argc > 1)
    {
        buf->read_file(argv[1]);
    }
    else
    {
        fprintf(stderr, "Please provide a file to open or create\n");
        return 1;
    }
    InputReader input;
    CommandBuilder command_builder;
    Painter painter;
    std::shared_ptr<EditorSettings> settings = std::make_shared<EditorSettings>(EditorSettings());
    std::shared_ptr<Position> position = std::make_shared<Position>(Position());
    
    settings->enable_raw_mode();
    painter.begin_drawing();
    painter.clear_screen();
    painter.draw_cursor(0, 0);
    painter.end_drawing();
    settings->update_window_size();
    painter.begin_drawing();
    painter.draw_text_buffer(settings, buf, position);
    painter.draw_cursor(0, 0);
    painter.end_drawing();

    bool running = true;
    while (running)
    {
        Input action = input.read_input();
        Command *cmd = command_builder.create_action_performer(buf, position, settings, action);
        painter.begin_drawing();
        switch (cmd->execute())
        {
            case STOP:
                running = false;
                break;
            case DRAW_LINE:
                painter.draw_line(settings, buf, position);
                break;
            case DRAW_BUF:
                painter.draw_text_buffer(settings, buf, position);
                break;
            case PASS:
                break;
        }
        delete cmd;
        painter.draw_cursor(position->row_pos, position->col_pos);
        painter.end_drawing();
    }

    painter.begin_drawing();
    painter.clear_screen();
    painter.end_drawing();
    return 0;
}