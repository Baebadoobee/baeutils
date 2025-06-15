#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define DOT_FOLDER "/home/bae/.dotfiles/hyprland/"                      // Path to dotfiles home folder
#define CONFIG_FOLDER "/home/bae/.config/"                              // Path to user's config folder
#define HOME_FOLDER "/home/bae/"                                        // Path to home folder
#define WALLPAPER_FOLDER (DOT_FOLDER "/config/hypr/wallpaper")          // Path to wallpaper folder
#define FILE_COUNT (sizeof(file_list)/sizeof(file_list[0]))             // File list size
#define COMMAND_COUNT (sizeof(command_list)/sizeof(command_list[0]))    // Command list size

#define MAX_LINE_LENGTH 1024                                            // Max line length

#include "baefs.h"

typedef struct {
  const char *name;
  const char *dest;
  const char *src;
} Symlink_t;

typedef struct {
  char *cmd;
} Command;

/* Remember to build the set functions */
// typedef struct {
//   char *wallpaper;
//   int mode;
// } Environment;

int symlink(const char *src, const char *dest);

/*----  Install Section  ----*/
void dot_install() {
  Symlink_t file_list[] = {
   /* NAME                    DESTINATION                           ORIGIN                                */
    { "nwg-dock-hyprland",    CONFIG_FOLDER "nwg-dock-hyprland",    DOT_FOLDER "config/nwg-dock-hyprland" },
    { "BetterDiscord",        CONFIG_FOLDER "BetterDiscord",        DOT_FOLDER "config/BetterDiscord"     },
    { "powershell",           CONFIG_FOLDER "powershell",           DOT_FOLDER "config/powershell"        },
    { "alacritty",            CONFIG_FOLDER "alacritty",            DOT_FOLDER "config/alacritty"         },
    { "wlogout",              CONFIG_FOLDER "wlogout",              DOT_FOLDER "config/wlogout"           },
    { "swaync",               CONFIG_FOLDER "swaync",               DOT_FOLDER "config/swaync"            },
    { "waybar",               CONFIG_FOLDER "waybar",               DOT_FOLDER "config/waybar"            },
    { "btop",                 CONFIG_FOLDER "btop",                 DOT_FOLDER "config/btop"              },
    { "hypr",                 CONFIG_FOLDER "hypr",                 DOT_FOLDER "config/hypr"              },
    { "wofi",                 CONFIG_FOLDER "wofi",                 DOT_FOLDER "config/wofi"              },
    { "pywal",                CONFIG_FOLDER "wal",                  DOT_FOLDER "config/wal"               },
    { "bashrc",               HOME_FOLDER ".bashrc",                DOT_FOLDER ".bashrc"                  },
    { "vimrc",                HOME_FOLDER ".vimrc",                 DOT_FOLDER ".vimrc"                   },
  };

  for (int i = 0; i < FILE_COUNT; ++i)
    symlink(file_list[i].src, file_list[i].dest);
}

// void config_install() {}

void colors_setup() {
  Symlink_t file_list[] = {
   /* NAME                        DESTINATION                                         ORIGIN                                         */
    { "colors-alacritty.toml",    CONFIG_FOLDER "alacritty/colors-alacritty.toml",    HOME_FOLDER ".cache/wal/colors-alacritty.toml" },
    { "colors-wofi.css",          CONFIG_FOLDER "wlogout/colors-wlogout.css",         HOME_FOLDER ".cache/wal/colors-waybar.css"     },
    { "colors-wlogout.css",       CONFIG_FOLDER "waybar/colors-waybar.css",           HOME_FOLDER ".cache/wal/colors-waybar.css"     },
    { "colors-swaync.css",        CONFIG_FOLDER "swaync/colors-swaync.css",           HOME_FOLDER ".cache/wal/colors-waybar.css"     },
    { "colors-waybar.css",        CONFIG_FOLDER "wofi/colors-wofi.css",               HOME_FOLDER ".cache/wal/colors-waybar.css"     },
  };

  for (int i = 0; i < FILE_COUNT; ++i)
    symlink(file_list[i].src, file_list[i].dest);
}

/*----  Utils Section  ----*/
char *wallpaper_get() {
  FILE *waypaper_conf; //wppc
  char buffer[MAX_LINE_LENGTH], line[30][MAX_LINE_LENGTH], *newline, *wallpaper;
  int i = 0;

  wallpaper = NULL;
  waypaper_conf = read_file("/home/bae/.config/waypaper/config.ini");
  while (fgets(buffer, sizeof(buffer), waypaper_conf) != NULL && i < 30) {
    strcpy(line[i], buffer);
    ++i;
  }

  wallpaper = malloc(strlen(line[3] + 12) + 1);
  if (wallpaper) {
    strcpy(wallpaper, line[3] + 12);
  }

  newline = strchr(wallpaper, '\n');
  if (newline) *newline = '\0';

  fclose(waypaper_conf);

  return wallpaper;
}

// void wallpaper_set(char *wallpaper) {
//
// }

void c_palette() {
  char command[256], *wallpaper;
  wallpaper = wallpaper_get();

  strcpy(command, "wal -e -ni ");
  strcat(command, wallpaper);

  system(command);

  free(wallpaper);
}

void waybar_reset() {
  char *command_list[] = {
    "killall -9 waybar nwg-dock-hyprland",
    "exec nwg-dock-hyprland -p \"right\" -l \"top\" -nolauncher -i 25 -mr -10 &",
    "exec waybar &",
  };

  for (int i = 0; i < COMMAND_COUNT; i++)
    system(command_list[i]);
}


/*----  Att. Section  ----*/
void waybar_att() {
  c_palette();
  waybar_reset();
}

void wallpaper_reset() {
  system("waypaper --random");
}

void wallpaper_att() {
  wallpaper_reset();
  c_palette();
}

void theme_att() {
  wallpaper_att();
  waybar_att();
}
