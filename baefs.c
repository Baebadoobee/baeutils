/* This header is meant for file system operation, it is suposed to be called by 'baelib.h' */
FILE *read_file(const char *file) {
  FILE *read_file = fopen(file, "r");
  if (!read_file) 
    fprintf(stderr, "Error msg: %s\n", strerror(errno));

  return read_file;
}

FILE *write_file(const char *file) {
  FILE *write_file = fopen(file, "w");
  if (!write_file)
    fprintf(stderr, "Error msg: %s\n", strerror(errno));

  return write_file;
}

FILE *append_file(const char *file) {
  FILE *append_file = fopen(file, "a");
  if (!append_file)
    fprintf(stderr, "Error msg: %s\n", strerror(errno));

  return append_file;
}

void change_line(const char *temp, const char *src, const int line_nbr, const char *text) {
  FILE *ftr = read_file(src); // File to read
  FILE *ftw = write_file(temp); // File to write
  char buffer[MAX_LINE_LENGTH];
  int start_line_nbr = 1;

  if (ftr && ftw) {
    while (fgets(buffer, sizeof(buffer), ftr) != NULL) {
      if (start_line_nbr != line_nbr) {
        fputs(buffer, ftw);
      } else {
        fputs(text, ftw);
      }

      ++start_line_nbr;
    }

    fclose(ftr);
    fclose(ftw);

    remove(src);
    rename(temp, src);
  } else {
    fprintf(stderr, "Error changing line(s) in file(s).\n");
  }
}

void copy_file(const char *dest, const char *src) {
  FILE *ftr = read_file(src); // File to read
  FILE *ftw = write_file(dest); // File to write
  char buffer[MAX_LINE_LENGTH];

  if (ftr && ftw) {
    while (fgets(buffer, sizeof(buffer), ftr) != NULL) {
      fputs(buffer, ftw);
    }

    fclose(ftr);
    fclose(ftw);
  } else {
    fprintf(stderr, "Error copying file(s).\n");
  }
}
