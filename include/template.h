/*
 * contains functions to manage templates made by user
 * refer documentation or README for more details(if available)
 */
#ifndef TEMPLATE_H
#define TEMPLATE_H
#include "sources.h"
#include <stdbool.h>
#include <stdio.h>
/*
this library uses true and false from stdbool.h for returns*/
/*
 * template functions take 2 things as argument
 * first, what is the name of the template
 * second, if you are making new template, where is the current template stored.
 Ex: if your new template is in file exp/hello.txt, give the argument as
 exp/hello.txt
 */
#define TEMPLATE_NAME_MAX 30
bool is_template_present(char name[]);
bool add_template(char name[], char src[]);
bool delete_template(char name[]);
bool update_template(char name[], char src[]);
/*
* in function print_template_names(FILE *stream) :
* give stream as stdout to print in terminal
* or give any file to output in
* 
* make sure that file mode is writable(w,a etc...)
* otherwise, you may get undefined behaviour
*/
bool print_template_names(FILE *stream); 
bool write_template_to_file(char template_name[],char destfile[]);
#endif
