/* This file is meant for to be called by 'baelib.h' */
void dot_install()
{
  Symlink file_list[] = {
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

void colors_setup()
{
  Symlink file_list[] = {
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

/* Utils Section */
char *wallpaper_get()
{
  FILE *waypaper_conf = read_file("/home/bae/.config/waypaper/config.ini"); //wppc
  char buffer[MAX_LINE_LENGTH], line[30][MAX_LINE_LENGTH], *newline, *wallpaper;
  wallpaper = NULL;
  int i = 0;

  if (waypaper_conf) {
    while (fgets(buffer, sizeof(buffer), waypaper_conf) != NULL && i < 30) {
      strcpy(line[i], buffer);
      ++i;
    }

    wallpaper = malloc(strlen(line[3] + 12) + 1);
    if (wallpaper) 
      strcpy(wallpaper, line[3] + 12);

    newline = strchr(wallpaper, '\n');
    if (newline) 
      *newline = '\0';

    fclose(waypaper_conf);
  } else {
    free(wallpaper);
  }

  return wallpaper;
}

void c_palette()
{
  char command[256], *wallpaper;
  wallpaper = wallpaper_get();

  strncpy(command, "wal -e -ni ", strlen(command + 12));
  strncat(command, wallpaper, strlen(command) + strlen(wallpaper));

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

/* Att. Section*/
void waybar_att()
{
  c_palette();
  waybar_reset();
}

void wallpaper_reset()
{
  system("waypaper --random");
}

void wallpaper_att()
{
  wallpaper_reset();
  c_palette();
}

void theme_att()
{
  wallpaper_att();
  waybar_att();
}

/* Alsa Section */
void alsa_ctl_list()
{
  char **hints;

  snd_device_name_hint(-1, "ctl", (void***)&hints);

  for (int i = 0; i < sizeof(hints) - 3; ++i) {
    printf("- %s\n", snd_device_name_get_hint((void**)hints[i], "NAME"));
    free(snd_device_name_get_hint((void**)hints[i], "NAME"));
  }

  snd_device_name_free_hint((void**)hints);
  
}

void alsa_volume_control(const int percent_increment)
{
  snd_mixer_t *mixer;
  snd_mixer_selem_id_t *sid;
  long min_volume, max_volume, volume;
  int percent = percent_increment;

  if (percent_increment == 0) {
    int percent = 1;
  }
  
  snd_mixer_open(&mixer, 0);
  snd_mixer_attach(mixer, "default");
  snd_mixer_selem_register(mixer, NULL, NULL);
  snd_mixer_load(mixer);
  
  snd_mixer_selem_id_malloc(&sid);
  snd_mixer_selem_id_set_index(sid, 0);
  snd_mixer_selem_id_set_name(sid, "Master");
  
  snd_mixer_elem_t *elem = snd_mixer_find_selem(mixer, sid);
  if (!elem) {
    snd_mixer_selem_id_set_name(sid, "PCM");
    elem = snd_mixer_find_selem(mixer, sid);
  }

  snd_mixer_selem_get_playback_volume_range(elem, &min_volume, &max_volume);
  snd_mixer_selem_get_playback_volume(elem, SND_MIXER_SCHN_FRONT_LEFT, &volume);
  
  volume += ((max_volume - min_volume) * percent / 100);
  if (volume < min_volume) volume = min_volume;
  else if (volume > max_volume) volume = max_volume;
  
  snd_mixer_selem_set_playback_volume_all(elem, volume);

  free(sid);

  snd_mixer_close(mixer);
}
