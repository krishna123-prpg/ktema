/*
 * contain filepaths and basic config settings
 * meant to be replaced by build tools to desired one
 * refer documentation or README for more details(if available)
 */
#ifndef SOURCES_H
#define SOURCES_H
#define program_name "ktema"
#define VERSION "0.0.1"
#define LICENSE "MIT"
#define AUTHOR "krishna bhat k"
#define template_path "ktema_templates/" // directory where templates are going to be stored
#define template_path_max 60
#define templatelist_filename "templatelist.txt"
#define new_templatelist_filename "new_templatelist.txt"
#define templatelist_file_path (template_path templatelist_filename) //file which has list of all templates
#define new_templatelist_file_path (template_path new_templatelist_filename) //used by some functions
#endif