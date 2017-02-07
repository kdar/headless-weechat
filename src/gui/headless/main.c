#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>

#include "../core/wee-hook.h"
#include "../core/weechat.h"
#include "../gui-color.h"

void headless_main_init() { printf("INIT\n"); }

void headless_main_end(int clean_exit) { printf("END\n"); }

void gui_window_objects_print_log(struct t_gui_window *window) {}
int gui_window_get_width() { return 0; }
int gui_window_get_height() { return 0; }
void gui_window_set_title() { printf("gui_window_set_title\n"); }
void gui_bar_window_create_win() { printf("gui_bar_window_create_win\n"); }
void gui_bar_window_draw() { printf("gui_bar_window_draw\n"); }
void gui_bar_window_objects_free() { printf("gui_bar_window_objects_free\n"); }
void gui_bar_window_objects_init() { printf("gui_bar_window_objects_init\n"); }
void gui_bar_window_objects_print_log() {
  printf("gui_bar_window_objects_print_log\n");
}
void gui_chat_string_next_char() { printf("gui_chat_string_next_char\n"); }
int gui_color_assign(int *color, char const *color_name) {
  printf("gui_color_assign\n");
  return 0;
}
int gui_color_assign_by_diff(int *color, const char *color_name, int diff) {
  printf("gui_color_assign_by_diff\n");
  return 0;
}
void gui_color_buffer_assign() { printf("gui_color_buffer_assign\n"); }
void gui_color_buffer_display() { printf("gui_color_buffer_display\n"); }
void gui_color_buffer_open() { printf("gui_color_buffer_open\n"); }
void gui_color_display_terminal_colors() {
  printf("gui_color_display_terminal_colors\n");
}
void gui_color_dump() { printf("gui_color_dump\n"); }
void gui_color_free_vars() { printf("gui_color_free_vars\n"); }

// void gui_color_get_name() {printf("gui_color_get_name\n");}
const char *gui_color_get_name(int num_color) { return "white"; }

int gui_color_get_term_colors() {
  printf("gui_color_get_term_colors\n");
  return 0;
}
int gui_color_get_weechat_colors_number() {
  printf("gui_color_get_weechat_colors_number\n");
  return 0;
}
void gui_color_info_term_colors(char *buffer, int size) {
  printf("gui_color_info_term_colors\n");
}
void gui_color_init_weechat() { printf("gui_color_init_weechat\n"); }
void gui_color_palette_build_aliases() {
  printf("gui_color_palette_build_aliases\n");
}
void gui_color_palette_free(struct t_gui_color_palette *color_palette) {
  printf("gui_color_palette_free\n");
}

struct t_gui_color_palette *gui_color_palette_new(int number,
                                                  const char *value) {
  printf("gui_color_palette_new\n");
}

void gui_color_reset_pairs() { printf("gui_color_reset_pairs\n"); }
int gui_color_search(const char *color_name) { return -1; }
void gui_color_switch_colors() { printf("gui_color_switch_colors\n"); }
void gui_key_default_bindings() { printf("gui_key_default_bindings\n"); }
void gui_main_debug_libs() { printf("gui_main_debug_libs\n"); }
void gui_main_end() { printf("gui_main_end\n"); }
void gui_main_get_password() { printf("gui_main_get_password\n"); }
void gui_mouse_disable() { printf("gui_mouse_disable\n"); }
void gui_mouse_display_state() { printf("gui_mouse_display_state\n"); }
void gui_mouse_enable() { printf("gui_mouse_enable\n"); }
void gui_mouse_event_end() { printf("gui_mouse_event_end\n"); }
void gui_mouse_event_init() { printf("gui_mouse_event_init\n"); }
void gui_mouse_grab_init() { printf("gui_mouse_grab_init\n"); }
void gui_term_set_eat_newline_glitch() {
  printf("gui_term_set_eat_newline_glitch\n");
}
void gui_window_balance() { printf("gui_window_balance\n"); }
void gui_window_bare_display_toggle() {
  printf("gui_window_bare_display_toggle\n");
}
void gui_window_merge() { printf("gui_window_merge\n"); }
void gui_window_merge_all() { printf("gui_window_merge_all\n"); }
void gui_window_move_cursor() { printf("gui_window_move_cursor\n"); }
void gui_window_objects_free() { printf("gui_window_objects_free\n"); }
void gui_window_objects_init() { printf("gui_window_objects_init\n"); }
void gui_window_page_down() { printf("gui_window_page_down\n"); }
void gui_window_page_up() { printf("gui_window_page_up\n"); }
void gui_window_resize() { printf("gui_window_resize\n"); }
void gui_window_resize_delta() { printf("gui_window_resize_delta\n"); }
void gui_window_scroll_beyond_end() {
  printf("gui_window_scroll_beyond_end\n");
}
void gui_window_scroll_bottom() { printf("gui_window_scroll_bottom\n"); }
void gui_window_scroll_down() { printf("gui_window_scroll_down\n"); }
void gui_window_scroll_top() { printf("gui_window_scroll_top\n"); }
void gui_window_scroll_up() { printf("gui_window_scroll_up\n"); }
void gui_window_set_bracketed_paste_mode() {
  printf("gui_window_set_bracketed_paste_mode\n");
}
void gui_window_split_horizontal() { printf("gui_window_split_horizontal\n"); }
void gui_window_split_vertical() { printf("gui_window_split_vertical\n"); }
void gui_window_swap() { printf("gui_window_swap\n"); }
void gui_window_switch() { printf("gui_window_switch\n"); }
void gui_window_switch_down() { printf("gui_window_switch_down\n"); }
void gui_window_switch_left() { printf("gui_window_switch_left\n"); }
void gui_window_switch_right() { printf("gui_window_switch_right\n"); }
void gui_window_switch_to_buffer() { printf("gui_window_switch_to_buffer\n"); }
void gui_window_switch_up() { printf("gui_window_switch_up\n"); }
void gui_window_term_display_infos() {
  printf("gui_window_term_display_infos\n");
}

void headless_loop() {
  while (!weechat_quit) {
    /* execute timer hooks */
    hook_timer_exec();

    /* execute fd hooks */
    hook_fd_exec();

    /* run process (with fork) */
    hook_process_exec();

    /* handle signals received */
    if (weechat_quit_signal & (SIGHUP | SIGQUIT | SIGTERM) > 0) {
      weechat_quit_signal = 0;
      weechat_quit = 1;
    }
  }
}

int main(int argc, char *argv[]) {
  weechat_init(argc, argv, &headless_main_init);

  headless_loop();

  weechat_end(&headless_main_end);

  return EXIT_SUCCESS;
}