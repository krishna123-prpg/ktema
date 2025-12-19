#ifndef FILE_H
#define FILE_H
#include <stdbool.h>
bool create_file_with_dirs(const char *path);
bool is_file_exists(char filename[]);
bool copyfile(char src[], char dest[]);
#endif