/*
 * contains functions to manage templates made by user
 * refer documentation or README for more details(if available)
 */
 #ifndef COMMAND_H
 #define COMMAND_H
 #include "argtable3.h"
 /*
 some functions assume return 0 as success and 1 as failure
 but some functions follow the opposite

 to solve this,
 we use 'true' and 'false' present in stdbool if return 1 means success
 otherwise custom made 'SUCCESS' and 'FAILURE' for opposite
 */
#define SUCCESS 0
#define FAILURE 1
 int create_command(int argc, char *argv[], arg_dstr_t res, void *ctx);
 int delete_command(int argc, char *argv[], arg_dstr_t res, void *ctx);
 int print_command(int argc,char *argv[],arg_dstr_t res, void *ctx);
 int update_command(int argc,char *argv[],arg_dstr_t res, void *ctx);
 int write_command(int argc,char *argv[],arg_dstr_t res, void *ctx);
 #endif