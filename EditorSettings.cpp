#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

#include "EditorSettings.hpp"
#include "macros.hpp"

struct termios EditorSettings::original_terminal_settings;

void EditorSettings::enable_raw_mode()
{
    CHECK(tcgetattr(STDERR_FILENO, &original_terminal_settings), -1, "tcgetattr");
    atexit(disable_raw_mode);
    struct termios new_settings = original_terminal_settings;
    new_settings.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    new_settings.c_oflag &= ~(OPOST);
    new_settings.c_cflag |= (CS8);
    new_settings.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
    new_settings.c_cc[VMIN] = 0;
    new_settings.c_cc[VTIME] = 1;
    CHECK(tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_settings), -1, "tcsetattr");
}

void EditorSettings::disable_raw_mode()
{
    CHECK(tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_terminal_settings), -1, "tcsetattr");
}

void EditorSettings::update_window_size()
{
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_row == 0)
        return;
    rows = ws.ws_row;
    cols = ws.ws_col;
}

int EditorSettings::get_rows() const
{
    return rows;
}

int EditorSettings::get_cols() const
{
    return cols;
}
