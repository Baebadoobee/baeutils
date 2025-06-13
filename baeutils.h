#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define DOT_FOLDER "/home/bae/.dotfiles/hyprland/"
#define CONFIG_FOLDER "/home/bae/.config/"
#define HOME_FOLDER "/home/bae/"

typedef struct {
  const char *name;
  const char *dest;
  const char *src;
} sym_link_list;

int symlink(const char *src, const char *dest);

/*----  Install Section  ----*/
void dot_install() {
  sym_link_list files[] = {
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

  for (int i = 0; i < 12; ++i)
    symlink(files[i].src, files[i].dest);
}


void colors_setup() {
  sym_link_list files[] = {
   /* NAME                        DESTINATION                                         ORIGIN                                         */
    { "colors-alacritty.toml",    CONFIG_FOLDER "alacritty/colors-alacritty.toml",    HOME_FOLDER ".cache/wal/colors-alacritty.toml" },
    { "colors-wofi.css",          CONFIG_FOLDER "wlogout/colors-wlogout.css",         HOME_FOLDER ".cache/wal/colors-waybar.css"     },
    { "colors-wlogout.css",       CONFIG_FOLDER "waybar/colors-waybar.css",           HOME_FOLDER ".cache/wal/colors-waybar.css"     },
    { "colors-swaync.css",        CONFIG_FOLDER "swaync/colors-swaync.css",           HOME_FOLDER ".cache/wal/colors-waybar.css"     },
    { "colors-waybar.css",        CONFIG_FOLDER "wofi/colors-wofi.css",               HOME_FOLDER ".cache/wal/colors-waybar.css"     },
  };

  for (int i = 0; i < 4; ++i)
    symlink(files[i].src, files[i].dest);
}


/*----  Utils Section  ----*/
void copy_file(const char *dest, const char *src) {
  FILE *ftr, *ftw; //file to...
  char buffer[33];

  ftr = fopen(src, "r");
  ftw = fopen(dest, "w");

  while (fgets(buffer, sizeof(buffer), ftr) != NULL) {
    fputs(buffer, ftw);
  }

  fclose(ftr);
  fclose(ftw);
}


char *wallpaper_get() {
  FILE *waypaper_conf; //wppc
  char buffer[1024], line[30][1024], *newline, *wppc_path, *wallpaper;
  int i = 0;

  wallpaper = NULL;
  wppc_path = "/home/bae/.config/waypaper/config.ini";
  waypaper_conf = fopen(wppc_path, "r");
  if (!wppc_path) {
    printf("Config file not reachable");
  }

  while (fgets(buffer, sizeof(buffer), waypaper_conf) != NULL && i < 30) {
      strcpy(line[i], buffer);
      ++i;
  }

  wallpaper = malloc(strlen(line[4] + 12) + 1);
  if (wallpaper) {
      strcpy(wallpaper, line[4] + 12);
  }

  newline = strchr(wallpaper, '\n');
  if (newline) *newline = '\0';

  fclose(waypaper_conf);

  return wallpaper;
}


void c_palette() {
  char pw_cmd[1024], *wallpaper, wal[1024];
  strcpy(pw_cmd, "wal -ni ");

  wallpaper = wallpaper_get();
  strcpy(wal, wallpaper);
  strcat(pw_cmd, wal);

  system(pw_cmd);

  free(wallpaper);
}

void waybar_reset() {
  char commands[3][256] = {
    "killall -9 waybar nwg-dock-hyprland",
    "exec nwg-dock-hyprland -p \"right\" -l \"top\" -nolauncher -i 25 -mr -10 &",
    "exec waybar &",
  };

  for (int i = 0; i < 4; i++)
    system(commands[i]);
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
