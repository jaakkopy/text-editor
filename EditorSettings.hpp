#ifndef EDITOR_SETTINGS
#define EDITOR_SETTINGS

#include <termios.h>

class EditorSettings
{
public:
    static void enable_raw_mode();
    static void disable_raw_mode();
    void update_window_size();
    int get_visible_columns() const;
    int get_visible_rows() const;
private:
    static struct termios original_terminal_settings;
    int rows;
    int cols;
};

#endif