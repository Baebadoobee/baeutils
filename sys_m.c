#include "baeutils.h"

typedef struct {
  const char *sc;
  const char *flag;
  const char *desc;
} Arg;

Arg flag[] = {
 /* S_CUT    FLAG             DESCRIPTION */
  { "-u",    "--update",      "Updates/reset some running applications. Can be called with: bar, theme, wallpaper or palette." },
  { "-i",    "--install",     "The manager install flag can be used to install dotfiles or a colorscheme"                      },
  { "-w",    "--wallpaper",   "Returns the current wallpaper"                                                                  },
  { "-h",    "--help",        "\tPrints this help message"                                                                     },
};

void 
help_msg() {
    for (int i = 0; i < 4; ++i)
      printf("%s\t%s\t%s\n", flag[i].sc, flag[i].flag, flag[i].desc);
    printf("\n");
}

int
main(int argc, char *argv[]) {

  if (!argv[1]) {
    help_msg();
  }

  // Update
  else if (strcmp(argv[1], flag[0].sc) == 0 || strcmp(argv[1], flag[0].flag) == 0) {
    for (int i = 2; i < argc; ++i) {
      if (strcmp(argv[i], "theme") == 0)
        theme_att();
      else if (strcmp(argv[i], "wallpaper") == 0)
        wallpaper_att();
      else if (strcmp(argv[i], "bar") == 0)
        waybar_att();
      else if (strcmp(argv[i], "palette") == 0)
        c_palette();
    }
  }

  // Install
  else if (strcmp(argv[1], flag[1].sc) == 0 || strcmp(argv[1], flag[1].flag) == 0) {
    for (int i = 2; i < argc; ++i) {
      if (strcmp(argv[i], "dotfiles") == 0)
        dot_install();
      else if (strcmp(argv[i], "colorscheme") == 0)
        colors_setup();
    }
  }

  // Wallpaper
  else if (strcmp(argv[1], flag[2].sc) == 0 || strcmp(argv[1], flag[2].flag) == 0) {
    char *wallpaper = wallpaper_get();
    printf("%s\n", wallpaper);

    free(wallpaper);
  }

  // Help
  else if (strcmp(argv[1], flag[3].sc) == 0 || strcmp(argv[1], flag[3].flag) == 0) {
    help_msg();
  }

  return 0;
}
