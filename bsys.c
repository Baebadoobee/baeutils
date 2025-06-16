#include "baelib.h"

int flag_parser(int argc, char *argv[]) 
{
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

  return 1;
}

int flag_error(int flag) 
{
  if (flag != 0) {
    fprintf(stderr, "Argument not recognized. Please try one of the standard flags.\n");
    return 1;
  }

  return 0;
}

int main(int argc, char *argv[]) 
{
  if (!argv[1]) {
    help_msg();
    return 0;
  } else {
    int flag_call = flag_parser(argc, argv);
    if (flag_error(flag_call) != 0) {
      help_msg();
    }

    return flag_call;
  }
}
