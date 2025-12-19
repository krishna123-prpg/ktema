#include "argtable3.h"
#include "command.h"
#include "include/argtable3.h"
#include "include/sources.h"
#include "sources.h"
#include "template.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#ifndef not_strcmp
#define not_strcmp(str1, str2) (!strcmp(str1, str2))
#endif
int main(int argc, char *argv[]) {
  int exitcode = 0;
  if (argc == 1) {
    printf("Try '%s --help' for more information.\n", program_name);
    exitcode = 1;
    return exitcode;
  }
  arg_cmd_init();
  arg_cmd_register("create", create_command, "create a template", NULL);
  arg_cmd_register("print", print_command, "print all template", NULL);
  arg_cmd_register("delete", delete_command, "delete a template", NULL);
  arg_cmd_register("update", update_command, "update a template", NULL);
  arg_cmd_register("write", write_command, "write a template to a file", NULL);
  arg_lit_t *help = arg_lit0("h", "help", "show help");
  arg_lit_t *version = arg_lit0(NULL, "version", "display version");
  arg_lit_t *license =
      arg_lit0(NULL, "license", "display license name and author");
  // as we have already arranged for subcommands, it is now to discard here
  arg_str_t *subcommands = arg_strn(NULL, NULL, "<input>", 0, 10,
                                    "subcommands"); // to ignore subcommands
  arg_end_t *end = arg_end(20);
  void *argtable[] = {help, version, license, subcommands, end};
  if (arg_nullcheck(argtable) != 0) {
    printf("%s: insufficient memory\n", program_name);
    exitcode = 1;
    goto exit;
  }
  int nerrors = arg_parse(argc, argv, argtable);
  /* If the parser returned any errors then display them and exit */
  if (nerrors > 0) {
    /* Display the error details contained in the arg_end struct.*/
    arg_print_errors(stdout, end, program_name);
    printf("Try '%s --help' for more information.\n", program_name);
    exitcode = 1;
  } else if (help->count > 0) {
    printf("Usage(may change): %s", program_name);
    arg_print_syntax(stdout, argtable, "\n");
    printf("Demonstrate command-line parsing in argtable3.\n\n");
    arg_print_glossary_gnu(stdout, argtable);
    printf("\nThe following are the subcommands:\n");
    arg_cmd_itr_t itr = arg_cmd_itr_create();
    do {
      arg_cmd_info_t *info = arg_cmd_itr_value(itr);
      printf("%-25.24s %s\n", info->name, info->description);
    } while (arg_cmd_itr_advance(itr));
    arg_cmd_itr_destroy(itr);
    printf("Try '%s <command> --help' for more information\n", program_name);
  } else if (version->count > 0) {
    printf("version: %s\n", VERSION);
  } else if (license->count > 0) {
    printf("this software is %s licensed by %s\n\n", LICENSE, AUTHOR);
    printf("this software also uses some third-party open-source libraries\n");
    printf("kindly refer the code to know about them\n");
  } else // sub commands
  {
    bool valid_subcommand_or_not = false;
    arg_cmd_itr_t itr = arg_cmd_itr_create();
    do {
      arg_cmd_info_t *info = arg_cmd_itr_value(itr);
      if (!strcmp(info->name, argv[1])) {
        valid_subcommand_or_not = true;
        break;
      }
    } while (arg_cmd_itr_advance(itr));
    arg_cmd_itr_destroy(itr);
    if (valid_subcommand_or_not == false) {
      printf("Unknown command: %s\n", argv[1]);
      printf("Try '%s --help' for more information.\n", program_name);
      exitcode = 1;
      goto exit;
    }
    arg_dstr_t res = arg_dstr_create();
    int ret = arg_cmd_dispatch(argv[1], argc - 2, argv + 2, res);
    if (ret == SUCCESS)
      goto exit;
    else {
      printf("%s", arg_dstr_cstr(res));
      printf("\nTry '%s --help' for more information.\n", program_name);
      exitcode = 1;
    }
    arg_dstr_destroy(res);
  }
exit:
  arg_cmd_unregister("create");
  arg_cmd_unregister("print");
  arg_cmd_unregister("update");
  arg_cmd_unregister("delete");
  arg_cmd_unregister("write");
  arg_cmd_uninit();
  /* deallocate each non-null entry in argtable[] */
  arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
  return exitcode;
}
