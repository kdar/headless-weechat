
int gui_window_get_width() { return 500; }
int gui_window_get_height() { return 500; }

void gui_window_objects_print_log(struct t_gui_window *window) {}
void gui_window_set_title(const char *title) {}

void gui_window_bare_display_toggle(const char *delay) {}
void gui_window_merge_all(struct t_gui_window *window) {}
void gui_window_move_cursor() {}
void gui_window_page_down(struct t_gui_window *window) {}
void gui_window_page_up(struct t_gui_window *window) {}
void gui_window_resize(struct t_gui_window_tree *tree, int percentage) {}
void gui_window_resize_delta(struct t_gui_window_tree *tree,
                             int delta_percentage) {}
void gui_window_scroll_beyond_end(struct t_gui_window *window) {}
void gui_window_swap(struct t_gui_window *window, int direction) {}
void gui_window_switch_up(struct t_gui_window *window) {}
void gui_window_switch_down(struct t_gui_window *window) {}
void gui_window_switch_left(struct t_gui_window *window) {}
void gui_window_switch_right(struct t_gui_window *window) {}
int gui_window_merge(struct t_gui_window *window) { return 1; }
void gui_window_term_display_infos() {}
void gui_window_set_bracketed_paste_mode(int enable) {}
void gui_window_switch_to_buffer(struct t_gui_window *window,
                                 struct t_gui_buffer *buffer,
                                 int set_last_read) {}
struct t_gui_window *gui_window_split_vertical(struct t_gui_window *window,
                                               int percentage) {}
struct t_gui_window *gui_window_split_horizontal(struct t_gui_window *window,
                                                 int percentage) {}
void gui_window_scroll_bottom(struct t_gui_window *window) {}
void gui_window_scroll_up(struct t_gui_window *window) {}
void gui_window_scroll_down(struct t_gui_window *window) {}
void gui_window_scroll_top(struct t_gui_window *window) {}
int gui_window_balance(struct t_gui_window_tree *tree) {}
void gui_window_switch(struct t_gui_window *window) {}
void gui_window_objects_free(struct t_gui_window *window, int free_separators) {}
int gui_window_objects_init(struct t_gui_window *window) {}
