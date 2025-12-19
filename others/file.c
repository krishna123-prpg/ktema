#ifndef FILE_C
#define FILE_C
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#ifdef _WIN32
#include <direct.h> /* _mkdir */
#include <windows.h>
#define PATH_SEP '\\'
#else
#include <sys/stat.h> /* mkdir */
#include <sys/types.h>
#define PATH_SEP '/'
#endif

/*
 * Creates a file at `path`.
 * Any missing directories in the path are created recursively.
 *
 * Returns true on success, false on failure.
 */
bool create_file_with_dirs(const char *path) {
  if (!path || *path == '\0') {
    return false;
  }

  char tmp[4096];
  size_t len = strlen(path);

  if (len >= sizeof(tmp)) {
    return false; /* path too long */
  }

  strcpy(tmp, path);

  /* Walk through the path, creating directories as needed */
  for (char *p = tmp + 1; *p; p++) {
    if (*p == '/' || *p == '\\') {
      char old = *p;
      *p = '\0';

#ifdef _WIN32
      if (_mkdir(tmp) != 0 && errno != EEXIST) {
        return false;
      }
#else
      if (mkdir(tmp, 0755) != 0 && errno != EEXIST) {
        return false;
      }
#endif
      *p = old;
    }
  }

  /* Create the file itself */
  FILE *f = fopen(path, "wb");
  if (!f) {
    return false;
  }

  fclose(f);
  return true;
}
bool is_file_exists(char filename[]) {
  FILE *file = fopen(filename, "rb");
  if (file == NULL)
    return false;
  else {
    fclose(file);
    return true;
  }
}
#define COPY_BUFFER_SIZE 4096
bool copyfile(char src[], char dest[]) {
  bool is_copied_file = false;
  FILE *srcfile = fopen(src, "rb");
  if (srcfile == NULL)
    return false;
  FILE *destfile = fopen(dest, "wb");
  if (destfile == NULL)
    if (create_file_with_dirs(dest) != false)
      destfile = fopen(dest, "wb");

  if (destfile == NULL) {
    fclose(srcfile);
    return false;
  }
  char buffer[COPY_BUFFER_SIZE];
  uint64_t read_bytes;
  uint64_t write_bytes;
  while ((read_bytes = fread(buffer, 1, COPY_BUFFER_SIZE, srcfile)) > 0) {
    write_bytes = fwrite(buffer, 1, read_bytes, destfile);
    if (read_bytes != write_bytes) {
      if (ferror(srcfile))
        printf("read error: error occured while reading from %s\n", src);
      else if (ferror(destfile))
        printf("write error: error occured while writing from %s\n", dest);
      else
        printf("unknown error occured while copying file %s to %s\n", src,
               dest);
      goto exit;
    }
  }
  is_copied_file = true;
exit:
  fclose(srcfile);
  fclose(destfile);
  return is_copied_file;
}
#endif
