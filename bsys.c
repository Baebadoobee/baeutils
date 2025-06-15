#include "baelib.h"

#define FLAG_COUNT (sizeof(flag)/sizeof(flag[0]))

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

void help_msg();
void update(int argc, char *argv[]);
void install(int argc, char *argv[]);
void wallpaper();
void set(int argc, char *argv[]);

int
main(int argc, char *argv[]) {

  if (!argv[1]) {
    help_msg();
    return 0;
  }

  // Update
  if (strcmp(argv[1], flag[0].sc) == 0 || strcmp(argv[1], flag[0].flag) == 0) {
    update(argc, argv);
    return 0;
  }

  // Install
  if (strcmp(argv[1], flag[1].sc) == 0 || strcmp(argv[1], flag[1].flag) == 0) {
    install(argc, argv);
    return 0;
  }

  // Wallpaper
  if (strcmp(argv[1], flag[2].sc) == 0 || strcmp(argv[1], flag[2].flag) == 0) {
    wallpaper();
    return 0;
  }

  // Help
  if (strcmp(argv[1], flag[3].sc) == 0 || strcmp(argv[1], flag[3].flag) == 0) {
    help_msg();
    return 0;
  }

  // Set
  if (strcmp(argv[1], flag[4].sc) == 0 || strcmp(argv[1], flag[4].flag) == 0) {
    set(argc, argv);
    return 0;
  }

  help_msg();
  return 1;
}

void
help_msg() {
  for (int i = 0; i < FLAG_COUNT; ++i)
    printf("%s\t%s\t%s\n", flag[i].sc, flag[i].flag, flag[i].desc);
  printf("\n");
}

void
update(int argc, char *argv[]) {
  for (int i = 2; i < argc; ++i) {
    if (strcmp(argv[i], "theme") == 0) theme_att();
    else if (strcmp(argv[i], "bar") == 0) waybar_att();
    else if (strcmp(argv[i], "palette") == 0) c_palette();
    else if (strcmp(argv[i], "wallpaper") == 0) wallpaper_att();
  }
}

void
install(int argc, char *argv[]) {
  for (int i = 2; i < argc; ++i) {
    if (strcmp(argv[i], "dotfiles") == 0) dot_install();
    else if (strcmp(argv[i], "colorscheme") == 0) colors_setup();
  }
}

void
wallpaper() {
  char *wallpaper = wallpaper_get();
  if (wallpaper) {
    printf("%s\n", wallpaper);
    free(wallpaper);
  } else {
    fprintf(stderr, "Failed to get wallpaper\n");
  }
}

void
set(int argc, char *argv[]) {
  for (int i = 2; i < argc; ++i) {
    int j = i + 1;
    if (strcmp(argv[i], "wallpaper") == 0) {
      const char *src = "/home/bae/.config/waypaper/config.ini";
      const char *temp = "/home/bae/.config/waypaper/config.ini.temp";
      char dec[MAX_LINE_LENGTH] = "wallpaper = ";
      
      change_line(temp, src, 4, strcat(dec, strcat(argv[j], "\n")));
    }
  }
}
