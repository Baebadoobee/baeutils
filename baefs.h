FILE *read_file(const char *file) {
  FILE *read_file = fopen(file, "r");
  if (!file) {
    printf("File not reachable");
    fclose(read_file);
    return NULL;
  } 

  return read_file;
}

FILE *write_file(const char *file) {
  FILE *write_file = fopen(file, "w");
  if (!file) {
    printf("File not reachable");
    fclose(write_file);
    return NULL;
  } 

  return write_file;
}

FILE *append_file(const char *file) {
  FILE *append_file = fopen(file, "a");
  if (!file) {
    printf("File not reachable");
    fclose(append_file);
    return NULL;
  }

  return append_file;
}

void change_line(const char *temp, const char *src, const int linenbr, const char *text) {
  // char *temp = NULL;

  // strcpy(temp, src);
  // strcat(temp, ".temp");

  FILE *ftr = read_file(src); // File to read
  FILE *ftw = write_file(temp); // File to write
  char buffer[MAX_LINE_LENGTH];
  int start_linenbr = 1;

  while (fgets(buffer, sizeof(buffer), ftr) != NULL) {
    if (start_linenbr != linenbr) {
      fputs(buffer, ftw);
    } else {
      fputs(text, ftw);
    }

    ++start_linenbr;
  }

  fclose(ftr);
  fclose(ftw);

  remove(src);
  rename(temp, src);
}

void copy_file(const char *dest, const char *src) {
  FILE *ftr = read_file(src); // File to read
  FILE *ftw = write_file(dest); // File to write
  char buffer[MAX_LINE_LENGTH];

  while (fgets(buffer, sizeof(buffer), ftr) != NULL) {
    fputs(buffer, ftw);
  }

  fclose(ftr);
  fclose(ftw);
}
