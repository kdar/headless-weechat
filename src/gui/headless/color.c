#include <stdio.h>
#include <stdlib.h>

#include "../core/wee-config.h"
#include "../gui-color.h"
#include "../gui-chat.h"

#define COLOR_BLACK 0
#define COLOR_RED 1
#define COLOR_GREEN 2
#define COLOR_YELLOW 3
#define COLOR_BLUE 4
#define COLOR_MAGENTA 5
#define COLOR_CYAN 6
#define COLOR_WHITE 7
#define GUI_CURSES_NUM_WEECHAT_COLORS 17
#define NCURSES_ATTR_SHIFT 8
typedef unsigned chtype;
#define NCURSES_CAST(type, value) (type)(value)
#define NCURSES_BITS(mask, shift)                                              \
  (NCURSES_CAST(chtype, (mask)) << ((shift) + NCURSES_ATTR_SHIFT))
#define A_BOLD NCURSES_BITS(1U, 13)
#define A_UNDERLINE NCURSES_BITS(1U, 9)
#define A_REVERSE NCURSES_BITS(1U, 10)
#define A_ITALIC NCURSES_BITS(1U, 23)

struct t_gui_color gui_weechat_colors_bold[GUI_CURSES_NUM_WEECHAT_COLORS + 1] =
    {{-1, -1, 0, "default"},
     {COLOR_BLACK, COLOR_BLACK, 0, "black"},
     {COLOR_BLACK, COLOR_BLACK + 8, A_BOLD, "darkgray"},
     {COLOR_RED, COLOR_RED, 0, "red"},
     {COLOR_RED, COLOR_RED + 8, A_BOLD, "lightred"},
     {COLOR_GREEN, COLOR_GREEN, 0, "green"},
     {COLOR_GREEN, COLOR_GREEN + 8, A_BOLD, "lightgreen"},
     {COLOR_YELLOW, COLOR_YELLOW, 0, "brown"},
     {COLOR_YELLOW, COLOR_YELLOW + 8, A_BOLD, "yellow"},
     {COLOR_BLUE, COLOR_BLUE, 0, "blue"},
     {COLOR_BLUE, COLOR_BLUE + 8, A_BOLD, "lightblue"},
     {COLOR_MAGENTA, COLOR_MAGENTA, 0, "magenta"},
     {COLOR_MAGENTA, COLOR_MAGENTA + 8, A_BOLD, "lightmagenta"},
     {COLOR_CYAN, COLOR_CYAN, 0, "cyan"},
     {COLOR_CYAN, COLOR_CYAN + 8, A_BOLD, "lightcyan"},
     {COLOR_WHITE, COLOR_WHITE, 0, "gray"},
     {COLOR_WHITE, COLOR_WHITE + 8, A_BOLD, "white"},
     {0, 0, 0, NULL}};

struct t_gui_color
    gui_weechat_colors_no_bold[GUI_CURSES_NUM_WEECHAT_COLORS + 1] = {
        {-1, -1, 0, "default"},
        {COLOR_BLACK, COLOR_BLACK, 0, "black"},
        {COLOR_BLACK + 8, COLOR_BLACK + 8, 0, "darkgray"},
        {COLOR_RED, COLOR_RED, 0, "red"},
        {COLOR_RED + 8, COLOR_RED + 8, 0, "lightred"},
        {COLOR_GREEN, COLOR_GREEN, 0, "green"},
        {COLOR_GREEN + 8, COLOR_GREEN + 8, 0, "lightgreen"},
        {COLOR_YELLOW, COLOR_YELLOW, 0, "brown"},
        {COLOR_YELLOW + 8, COLOR_YELLOW + 8, 0, "yellow"},
        {COLOR_BLUE, COLOR_BLUE, 0, "blue"},
        {COLOR_BLUE + 8, COLOR_BLUE + 8, 0, "lightblue"},
        {COLOR_MAGENTA, COLOR_MAGENTA, 0, "magenta"},
        {COLOR_MAGENTA + 8, COLOR_MAGENTA + 8, 0, "lightmagenta"},
        {COLOR_CYAN, COLOR_CYAN, 0, "cyan"},
        {COLOR_CYAN + 8, COLOR_CYAN + 8, 0, "lightcyan"},
        {COLOR_WHITE, COLOR_WHITE, 0, "gray"},
        {COLOR_WHITE + 8, COLOR_WHITE + 8, 0, "white"},
        {0, 0, 0, NULL}};

struct t_gui_color *gui_weechat_colors = gui_weechat_colors_bold;
int gui_color_term_colors = 0;

int gui_color_get_extended_attrs(int color) {
  int attributes;

  attributes = 0;

  if (color & GUI_COLOR_EXTENDED_BOLD_FLAG)
    attributes |= A_BOLD;
  if (color & GUI_COLOR_EXTENDED_REVERSE_FLAG)
    attributes |= A_REVERSE;
  if (color & GUI_COLOR_EXTENDED_ITALIC_FLAG)
    attributes |= A_ITALIC;
  if (color & GUI_COLOR_EXTENDED_UNDERLINE_FLAG)
    attributes |= A_UNDERLINE;

  return attributes;
}

void gui_color_build(int number, int foreground, int background) {
  if (foreground < 0)
    foreground = 0;
  if (background < 0)
    background = 0;

  /* allocate color */
  if (!gui_color[number]) {
    gui_color[number] = malloc(sizeof(*gui_color[number]));
    if (!gui_color[number])
      return;
    gui_color[number]->string = malloc(4);
  }

  /* set foreground and attributes */
  if (foreground & GUI_COLOR_EXTENDED_FLAG) {
    gui_color[number]->foreground = foreground & GUI_COLOR_EXTENDED_MASK;
    gui_color[number]->attributes = 0;
  } else {
    gui_color[number]->foreground =
        gui_weechat_colors[foreground & GUI_COLOR_EXTENDED_MASK].foreground;
    gui_color[number]->attributes =
        gui_weechat_colors[foreground & GUI_COLOR_EXTENDED_MASK].attributes;
  }
  gui_color[number]->attributes |= gui_color_get_extended_attrs(foreground);

  /* set background */
  if (background & GUI_COLOR_EXTENDED_FLAG)
    gui_color[number]->background = background & GUI_COLOR_EXTENDED_MASK;
  else
    gui_color[number]->background =
        gui_weechat_colors[background & GUI_COLOR_EXTENDED_MASK].background;

  /* set string */
  if (gui_color[number]->string) {
    snprintf(gui_color[number]->string, 4, "%c%02d", GUI_COLOR_COLOR_CHAR,
             number);
  }
}

int gui_color_assign(int *color, char const *color_name) {

  *color = 0;
  return 1;
}

int gui_color_assign_by_diff(int *color, const char *color_name, int diff) {

  *color = 0;
  return 1;
}

const char *gui_color_get_name(int num_color) { return "white"; }

int gui_color_get_term_colors() { return 1; }

int gui_color_get_weechat_colors_number() { return 1; }

int gui_color_search(const char *color_name) { return 0; }

void gui_color_init_weechat() {
  if (CONFIG_BOOLEAN(config_look_color_basic_force_bold) ||
      (gui_color_term_colors < 16)) {
    gui_weechat_colors = gui_weechat_colors_bold;
  } else {
    gui_weechat_colors = gui_weechat_colors_no_bold;
  }

  gui_color_build(GUI_COLOR_SEPARATOR, CONFIG_COLOR(config_color_separator),
                  CONFIG_COLOR(config_color_chat_bg));

  gui_color_build(GUI_COLOR_CHAT, CONFIG_COLOR(config_color_chat),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_TIME, CONFIG_COLOR(config_color_chat_time),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_TIME_DELIMITERS,
                  CONFIG_COLOR(config_color_chat_time_delimiters),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_PREFIX_ERROR,
                  CONFIG_COLOR(config_color_chat_prefix[GUI_CHAT_PREFIX_ERROR]),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(
      GUI_COLOR_CHAT_PREFIX_NETWORK,
      CONFIG_COLOR(config_color_chat_prefix[GUI_CHAT_PREFIX_NETWORK]),
      CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(
      GUI_COLOR_CHAT_PREFIX_ACTION,
      CONFIG_COLOR(config_color_chat_prefix[GUI_CHAT_PREFIX_ACTION]),
      CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_PREFIX_JOIN,
                  CONFIG_COLOR(config_color_chat_prefix[GUI_CHAT_PREFIX_JOIN]),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_PREFIX_QUIT,
                  CONFIG_COLOR(config_color_chat_prefix[GUI_CHAT_PREFIX_QUIT]),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_PREFIX_MORE,
                  CONFIG_COLOR(config_color_chat_prefix_more),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_PREFIX_SUFFIX,
                  CONFIG_COLOR(config_color_chat_prefix_suffix),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_BUFFER, CONFIG_COLOR(config_color_chat_buffer),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_SERVER, CONFIG_COLOR(config_color_chat_server),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_CHANNEL,
                  CONFIG_COLOR(config_color_chat_channel),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_NICK, CONFIG_COLOR(config_color_chat_nick),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_NICK_SELF,
                  CONFIG_COLOR(config_color_chat_nick_self),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_NICK_OTHER,
                  CONFIG_COLOR(config_color_chat_nick_other),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_HOST, CONFIG_COLOR(config_color_chat_host),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_DELIMITERS,
                  CONFIG_COLOR(config_color_chat_delimiters),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_HIGHLIGHT,
                  CONFIG_COLOR(config_color_chat_highlight),
                  CONFIG_COLOR(config_color_chat_highlight_bg));
  gui_color_build(GUI_COLOR_CHAT_READ_MARKER,
                  CONFIG_COLOR(config_color_chat_read_marker),
                  CONFIG_COLOR(config_color_chat_read_marker_bg));
  gui_color_build(GUI_COLOR_CHAT_TEXT_FOUND,
                  CONFIG_COLOR(config_color_chat_text_found),
                  CONFIG_COLOR(config_color_chat_text_found_bg));
  gui_color_build(GUI_COLOR_CHAT_VALUE, CONFIG_COLOR(config_color_chat_value),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_PREFIX_BUFFER,
                  CONFIG_COLOR(config_color_chat_prefix_buffer),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_TAGS, CONFIG_COLOR(config_color_chat_tags),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_INACTIVE_WINDOW,
                  CONFIG_COLOR(config_color_chat_inactive_window),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_INACTIVE_BUFFER,
                  CONFIG_COLOR(config_color_chat_inactive_buffer),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_PREFIX_BUFFER_INACTIVE_BUFFER,
                  CONFIG_COLOR(config_color_chat_prefix_buffer_inactive_buffer),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_NICK_OFFLINE,
                  CONFIG_COLOR(config_color_chat_nick_offline),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_NICK_OFFLINE_HIGHLIGHT,
                  CONFIG_COLOR(config_color_chat_nick_offline_highlight),
                  CONFIG_COLOR(config_color_chat_nick_offline_highlight_bg));
  gui_color_build(GUI_COLOR_CHAT_NICK_PREFIX,
                  CONFIG_COLOR(config_color_chat_nick_prefix),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_NICK_SUFFIX,
                  CONFIG_COLOR(config_color_chat_nick_suffix),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_EMPHASIS, CONFIG_COLOR(config_color_emphasized),
                  CONFIG_COLOR(config_color_emphasized_bg));
  gui_color_build(GUI_COLOR_CHAT_DAY_CHANGE,
                  CONFIG_COLOR(config_color_chat_day_change),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_VALUE_NULL,
                  CONFIG_COLOR(config_color_chat_value_null),
                  CONFIG_COLOR(config_color_chat_bg));

  /*
   * define old nick colors for compatibility on /upgrade with previous
   * versions: these colors have been removed in version 0.3.4 and replaced
   * by new option "weechat.color.chat_nick_colors", which is a list of
   * colors (without limit on number of colors)
   */
  gui_color_build(GUI_COLOR_CHAT_NICK1_OBSOLETE, gui_color_search("cyan"),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_NICK2_OBSOLETE, gui_color_search("magenta"),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_NICK3_OBSOLETE, gui_color_search("green"),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_NICK4_OBSOLETE, gui_color_search("brown"),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_NICK5_OBSOLETE, gui_color_search("lightblue"),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_NICK6_OBSOLETE, gui_color_search("default"),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_NICK7_OBSOLETE, gui_color_search("lightcyan"),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_NICK8_OBSOLETE,
                  gui_color_search("lightmagenta"),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_NICK9_OBSOLETE, gui_color_search("lightgreen"),
                  CONFIG_COLOR(config_color_chat_bg));
  gui_color_build(GUI_COLOR_CHAT_NICK10_OBSOLETE, gui_color_search("blue"),
                  CONFIG_COLOR(config_color_chat_bg));
}

void gui_color_buffer_assign() {}
void gui_color_buffer_display() {}
void gui_color_buffer_open() {}
void gui_color_display_terminal_colors() {}
void gui_color_dump() {}
void gui_color_free_vars() {}
void gui_color_info_term_colors(char *buffer, int size) {}
void gui_color_palette_build_aliases() {}
void gui_color_palette_free(struct t_gui_color_palette *color_palette) {}
struct t_gui_color_palette *gui_color_palette_new(int number,
                                                  const char *value) {}
void gui_color_reset_pairs() {}
void gui_color_switch_colors() {}