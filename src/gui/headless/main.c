#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../core/wee-command.h"
#include "../core/wee-hook.h"
#include "../core/wee-log.h"
#include "../core/wee-string.h"
#include "../core/wee-utf8.h"
#include "../core/wee-util.h"
#include "../core/wee-version.h"
#include "../core/weechat.h"
#include "../gui-bar-item.h"
#include "../gui-bar.h"
#include "../gui-buffer.h"
#include "../gui-chat.h"
#include "../gui-cursor.h"
#include "../gui-filter.h"
#include "../gui-history.h"
#include "../gui-hotlist.h"
#include "../gui-input.h"
#include "../gui-layout.h"
#include "../gui-line.h"
#include "../gui-main.h"
#include "../gui-nicklist.h"
#include "../gui-window.h"

void gui_main_init() {
  struct t_gui_buffer *ptr_buffer;
  char title[256];

  /* create core buffer */
  ptr_buffer =
      gui_buffer_new(NULL, GUI_BUFFER_MAIN, NULL, NULL, NULL, NULL, NULL, NULL);
  if (ptr_buffer) {
    gui_init_ok = 1;

    ptr_buffer->num_displayed = 1;

    /* set short name */
    if (!ptr_buffer->short_name)
      ptr_buffer->short_name = strdup(GUI_BUFFER_MAIN);

    /* set title for core buffer */
    snprintf(title, sizeof(title), "WeeChat %s %s - %s", version_get_version(),
             WEECHAT_COPYRIGHT_DATE, WEECHAT_WEBSITE);
    gui_buffer_set_title(ptr_buffer, title);

    if (gui_window_new(NULL, ptr_buffer, 0, 0, 80, 25, 100, 100)) {
      gui_current_window = gui_windows;
    }
  }
}

void gui_main_end(int clean_exit) {}

void gui_main_debug_libs() {}
void gui_main_get_password(const char **prompt, char *password, int size) {}

void gui_main_refreshs()
{
    struct t_gui_buffer *ptr_buffer;

    /* compute max length for prefix/buffer if needed */
    for (ptr_buffer = gui_buffers; ptr_buffer;
         ptr_buffer = ptr_buffer->next_buffer)
    {
        /* compute buffer/prefix max length for own_lines */
        if (ptr_buffer->own_lines)
        {
            if (ptr_buffer->own_lines->buffer_max_length_refresh)
            {
                gui_line_compute_buffer_max_length (ptr_buffer,
                                                    ptr_buffer->own_lines);
            }
            if (ptr_buffer->own_lines->prefix_max_length_refresh)
                gui_line_compute_prefix_max_length (ptr_buffer->own_lines);
        }

        /* compute buffer/prefix max length for mixed_lines */
        if (ptr_buffer->mixed_lines)
        {
            if (ptr_buffer->mixed_lines->buffer_max_length_refresh)
            {
                gui_line_compute_buffer_max_length (ptr_buffer,
                                                    ptr_buffer->mixed_lines);
            }
            if (ptr_buffer->mixed_lines->prefix_max_length_refresh)
                gui_line_compute_prefix_max_length (ptr_buffer->mixed_lines);
        }
    }
}

void gui_main_loop() {
  while (!weechat_quit) {
    /* execute timer hooks */
    hook_timer_exec();

    gui_main_refreshs();

    /* execute fd hooks */
    hook_fd_exec();

    /* run process (with fork) */
    hook_process_exec();

    /* handle signals received */
    if ((weechat_quit_signal & (SIGHUP | SIGQUIT | SIGTERM)) > 0) {
      weechat_quit_signal = 0;
      weechat_quit = 1;
    }
  }
}

int main(int argc, char *argv[]) {
  weechat_init(argc, argv, &gui_main_init);
  gui_main_loop();
  weechat_end(&gui_main_end);

  return EXIT_SUCCESS;
}