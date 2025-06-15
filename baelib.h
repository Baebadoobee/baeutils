#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define HOME_FOLDER "/home/bae"                                         // Path to home folder
#define DOT_FOLDER HOME_FOLDER "/.dotfiles/hyprland/"                   // Path to dotfiles home folder
#define CONFIG_FOLDER HOME_FOLDER "/.config/"                           // Path to user's config folder
#define WALLPAPER_FOLDER DOT_FOLDER "/config/hypr/wallpaper"            // Path to wallpaper folder
#define FILE_COUNT (sizeof(file_list)/sizeof(file_list[0]))             // File list size
#define COMMAND_COUNT (sizeof(command_list)/sizeof(command_list[0]))    // Command list size
#define MAX_LINE_LENGTH 1024                                            // Max line length
#define FLAG_COUNT (sizeof(flag)/sizeof(flag[0]))                       // Flag list size

typedef struct {
  const char *name;
  const char *dest;
  const char *src;
} Symlink;

typedef struct {
  char *cmd;
} Command;

typedef struct {
  const char *sc;
  const char *flag;
  const char *desc;
} Arg;

Arg flag[] = {
 /* S_CUT    FLAG             DESCRIPTION */
  { "-u",    "--update",      "Updates/reset some running applications. Can be called with: bar, theme, wallpaper or palette." },
  { "-i",    "--install",     "The manager install flag can be used to install dotfiles or a colorscheme."                     },
  { "-w",    "--wallpaper",   "Returns the current wallpaper."                                                                 },
  { "-h",    "--help",        "\tPrints this help message."                                                                    },
  { "-s",    "--set",         "\tCan be used to set some general configurations"                                               },
};

#include "baefs.c"
#include "baelib.c"

/* baefs.c */
FILE *read_file(const char *file);
FILE *write_file(const char *file);
FILE *append_file(const char *file);
void change_line(const char *temp, const char *src, const int line_nbr, const char *text);
void copy_file(const char *dest, const char *src);
int symlink(const char *src, const char *dest);

/* baelib.c */
void dot_install();
void colors_setup();
char *wallpaper_get();
void c_palette();
void waybar_reset();
void waybar_att();
void wallpaper_reset();
void wallpaper_att();
void theme_att();
