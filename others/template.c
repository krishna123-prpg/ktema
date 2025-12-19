/*
 * contains functions to manage templates made by user
 * refer documentation or README or header file for more details(if available)
 */
#ifndef TEMPLATE_C
#define TEMPLATE_C
#include "template.h"
#include "file.h"
#include "sources.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/*
 * template functions internally uses a file that contains template names
 * it is used to identify whether a template exists or not
 * it is usually referred as template list file
 *
 * they also use another file as temporary file
 * it is used as temporary file while adding/deleting from template list file
 * it is usually referred as new template list file
 */
#ifndef not_strcmp
#define not_strcmp(str1, str2) (!strcmp(str1, str2))
#endif
// static functions, implementations are at the end of the file
static bool readline(char *str, int max, FILE *fptr);
static bool putline(char *str, FILE *fptr);
// global/extern functions
bool is_template_present(char name[]) {
  FILE *template_list = fopen(templatelist_file_path, "rb");
  if (template_list == NULL)
    return false;
  char template_name[TEMPLATE_NAME_MAX];
  bool is_template_present = false;
  if (not_strcmp(templatelist_filename, name) ||
      not_strcmp(new_templatelist_filename, name))
    return false;
  while (readline(template_name, TEMPLATE_NAME_MAX, template_list) != false) {
    if (!strcmp(name, template_name))
      is_template_present = true;
  }
  fclose(template_list);
  return is_template_present;
}
bool add_template(char name[], char src[]) {
  if (strlen(name) > TEMPLATE_NAME_MAX || is_template_present(name))
    return false;
  // add the template file
  char dest[template_path_max + TEMPLATE_NAME_MAX + 4];
  strcpy(dest, template_path);
  strcat(dest, name);
  strcat(dest, ".txt");
  if (copyfile(src, dest) == false)
    return false;
  // add the template in record
  FILE *template_list = fopen(templatelist_file_path, "a");
  if (template_list == NULL)
    return false;
  putline(name, template_list);
  fclose(template_list);
  return true;
}
bool delete_template(char name[]) {
  if (!is_template_present(name) || strlen(name)>TEMPLATE_NAME_MAX)
    return false;
  FILE *template_list = fopen(templatelist_file_path, "rb");
  if (template_list == NULL)
    return false;
  FILE *new_template_list = fopen(new_templatelist_file_path, "wb");
  if (new_template_list == NULL) {
    fclose(template_list);
    return false;
  }

  // delete the template from the record
  char template_name[TEMPLATE_NAME_MAX];
  while (readline(template_name, TEMPLATE_NAME_MAX, template_list) != false) {
    if (strcmp(name, template_name))
      putline(template_name, new_template_list);
  }
  // delete the template file itself
  char template[template_path_max + TEMPLATE_NAME_MAX + 4];
  strcpy(template, template_path);
  strcat(template, name);
  strcat(template, ".txt");
  remove(template);
  // close all files
  fclose(template_list);
  fclose(new_template_list);
  remove(templatelist_file_path);
  rename(new_templatelist_file_path, templatelist_file_path);
  return true;
}
bool update_template(char name[], char src[]) {
  if (!(is_template_present(name) || is_file_exists(src))||strlen(name)>TEMPLATE_NAME_MAX)
    return false;
  delete_template(name);
  if (!add_template(name, src))
    return false;
  return true;
}
bool print_template_names(FILE *stream) {
  FILE *template_list = fopen(templatelist_file_path, "rb");
  if (template_list == NULL)
    return false;
  char template_name[TEMPLATE_NAME_MAX];
  for (int i = 1;
       readline(template_name, TEMPLATE_NAME_MAX, template_list) != false;
       ++i) {
    fprintf(stream, "%-10d\t%s\n", i, template_name);
  }
  fclose(template_list);
  return true;
}
bool write_template_to_file(char template_name[], char destfile[]) {
  if (!is_template_present(template_name)||strlen(template_name)>TEMPLATE_NAME_MAX)
    return false;
  if (!create_file_with_dirs(destfile))
    return false;
  int len = strlen(template_path) + strlen(template_name) +
            5; // other 5 are for ".txt" and '\0'
  char *p = malloc(len);
  strcpy(p, template_path);
  strcat(p, template_name);
  strcat(p, ".txt");
  if (copyfile(p, destfile) == false) {
    free(p);
    return false;
  }
  free(p);
  return true;
}
// static functions
static bool readline(char *str, int max, FILE *fptr) {
  if (fgets(str, max, fptr) == NULL)
    return false;
  str[strcspn(str, "\n")] = '\0';
  return true;
}
static bool putline(char *str, FILE *fptr) {
  fputs(str, fptr);
  fputs("\n", fptr);
  return true;
}
#endif
