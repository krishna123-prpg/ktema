/*
 * contains functions to manage templates made by user
 * refer documentation or README or header file for more details(if available)
 */
#ifndef COMMAND_C
#define COMMAND_C
#include "command.h"
#include "argtable3.h"
#include "sources.h"
#include "template.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define isflag(str) (str[0] == '-')
#define not_flag(str) (!isflag(str))
static void create_less_arg_message_err(arg_dstr_t res, char func_name[],
                                        int given_argc, int required_argc) {
  if (res != NULL)
    arg_dstr_catf(res, "Expected %d arguments for '%s' but received only %d",
                  required_argc, func_name, given_argc);
}
int create_command(int argc, char *argv[], arg_dstr_t res, void *ctx) {
  if (argc < 2) {
    create_less_arg_message_err(res, "create", argc, 2);
    return FAILURE;
  }
  char *template_name = argv[0];
  char *template_file = argv[1];
  if (isflag(template_name) || isflag(template_file))
    return FAILURE;
  bool template_added_or_not = !add_template(template_name, template_file);
  if (template_added_or_not == FAILURE && res != NULL) {
    arg_dstr_reset(res);
    arg_dstr_catf(res, "Error occured while adding template '%s'\n",
                  template_name);
    arg_dstr_catf(res,
                  "Try '%s print' to check if the template already exists\n",
                  program_name);
    arg_dstr_catf(res,
                  "Also check whether the file '%s', which is given as input "
                  "exists or not\n",
                  template_file);
    arg_dstr_catf(res, "Note: the template name must be less than %d letters\n",
                  TEMPLATE_NAME_MAX);
  }
  return template_added_or_not;
}
int update_command(int argc, char *argv[], arg_dstr_t res, void *ctx) {
  if (argc < 2) {
    create_less_arg_message_err(res, "update", argc, 2);
    return FAILURE;
  }
  char *template_name = argv[0];
  char *template_file = argv[1];
  if (isflag(template_name) || isflag(template_file))
    return FAILURE;
  bool template_updated_or_not = !update_template(template_name, template_file);
  if (template_updated_or_not == FAILURE && res != NULL) {
    arg_dstr_reset(res);
    arg_dstr_catf(res, "Error occured while updating template '%s'\n",
                  template_name);
    arg_dstr_catf(res,
                  "Try '%s print' to check if the template already exists\n",
                  program_name);
    arg_dstr_catf(res,
                  "Also check whether the file '%s', which is given as input "
                  "exists or not\n",
                  template_file);
    arg_dstr_catf(res, "Note: the template name must be less than %d letters\n",
                  TEMPLATE_NAME_MAX);
  }
  return template_updated_or_not;
}
int print_command(int argc, char *argv[], arg_dstr_t res, void *ctx) {
  bool printed_or_not = !print_template_names(stdout);
  if (printed_or_not == FAILURE && res != NULL) {
    arg_dstr_reset(res);
    arg_dstr_catf(res, "Error occured while printing template\n");
    arg_dstr_catf(res,
                  "It is possible that '%s' was unable to find any templates\n",
                  program_name);
    arg_dstr_catf(res, "Check whether adding any new template resolve this\n");
  }
  return printed_or_not;
}
int delete_command(int argc, char *argv[], arg_dstr_t res, void *ctx) {
  if (argc == 0) {
    create_less_arg_message_err(res, "delete", argc, 1);
    return FAILURE;
  }
  char *template_name = argv[0];
  bool template_deleted_or_not = !delete_template(template_name);
  if (template_deleted_or_not == FAILURE && res != NULL) {
    arg_dstr_reset(res);
    arg_dstr_catf(res, "Error occured while delete template '%s'\n",
                  template_name);
    arg_dstr_catf(res,
                  "Try '%s print' to check if the template exists or not\n",
                  program_name);
    arg_dstr_catf(res, "Note: the template name must be less than %d letters\n",
                  TEMPLATE_NAME_MAX);
  }
  return template_deleted_or_not;
}
int write_command(int argc, char *argv[], arg_dstr_t res, void *ctx) {
  if (argc < 2) {
    create_less_arg_message_err(res, "write", argc, 2);
    return FAILURE;
  }
  char *template_name = argv[0];
  char *destfile = argv[1];
  if (isflag(template_name) || isflag(destfile))
    return FAILURE;
  bool template_written_to_file_or_not =
      !write_template_to_file(template_name, destfile);
  if (template_written_to_file_or_not == FAILURE && res != NULL) {
    arg_dstr_reset(res);
    arg_dstr_catf(res,
                  "Error occured while writing template '%s' to file '%s'\n",
                  template_name, destfile);
    arg_dstr_catf(res,
                  "Try '%s print' to check if the template already exists\n",
                  program_name);
    arg_dstr_catf(res, "Note: the template name must be less than %d letters\n",
                  TEMPLATE_NAME_MAX);
  }
  return template_written_to_file_or_not;
}
#endif
