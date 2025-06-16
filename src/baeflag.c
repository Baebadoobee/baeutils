/* This file is meant for flag parsing functions, it is suposed to be called by 'baelib.h' */
void help_msg()
{
  for (int i = 0; i < FLAG_COUNT; ++i)
    printf("%s\t%s\t%s\n", flag[i].sc, flag[i].flag, flag[i].desc);
  printf("\n");
}

void update(int argc, char *argv[])
{
  for (int i = 2; i < argc; ++i) {
    if (strcmp(argv[i], "theme") == 0) theme_att();
    else if (strcmp(argv[i], "bar") == 0) waybar_att();
    else if (strcmp(argv[i], "palette") == 0) c_palette();
    else if (strcmp(argv[i], "wallpaper") == 0) wallpaper_att();
  }
}

void install(int argc, char *argv[])
{
  for (int i = 2; i < argc; ++i) {
    if (strcmp(argv[i], "dotfiles") == 0) dot_install();
    else if (strcmp(argv[i], "colorscheme") == 0) colors_setup();
  }
}

void wallpaper()
{
  char *wallpaper = wallpaper_get();
  if (wallpaper) {
    printf("%s\n", wallpaper);
    free(wallpaper);
  } else {
    fprintf(stderr, "Failed to get wallpaper\n");
  }
}

void set(int argc, char *argv[])
{
  for (int i = 2; i < argc; ++i) {
    int j = i + 1;
    if (strcmp(argv[i], "wallpaper") == 0) {
      if (!argv[j]) {
        fprintf(stderr, "No value to set\n");
        return;
      }

      const char *src = "/home/bae/.config/waypaper/config.ini";
      const char *temp = "/home/bae/.config/waypaper/config.ini.temp";
      char dec[MAX_LINE_LENGTH] = "wallpaper = ";
      change_line(temp, src, 4, strcat(dec, strcat(argv[j], "\n")));
    }
    else if (strcmp(argv[i], "volume") == 0) {
      if (!argv[j]) {
        fprintf(stderr, "No value to set\n");
        return;
      }

      int new_volume = atoi(argv[j]);
      alsa_volume_control(new_volume);
    }
  }
}
