#ifndef _SIMPLE_SHELL_H_
#define _SIMPLE_SHELL_H_

#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <errno.h>
#include <limits.h>

#define F_FLUSH -1
#define ILLNUM 666
#define NOTDIR 777

int _getc(int fd);
char *_fgets(char *s, int n, int fd);
int _getline(char **lineptr, int fd);

/* environmental variables */
extern char **environ;

/**
 * struct list_s - singly linked list
 * @str: string - (malloc'ed string)
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 * for Holberton project
 */

typedef struct list_s
{
	char *str;
	struct list_s *next;
} list_t;
/**
 * struct arguments - Values to be accessed by various functions
 * @buf: String
 * @arr: Array of strings
 * @count: Command count
 * @status: Exit status
 * @head: Pointer to first node
 * @argv: Name of the executable
 * @ac: argument count
 * @exit_status: Exit status of the previous cmd
 * @index: Index
 */
typedef struct arguments
{
	char *buf;
	char **arr;
	int count;
	pid_t status;
	list_t *head;
	char *argv;
	int ac;
	int exit_status;
	int index;
} arguments_t;

/**
 * struct built_ins - Struct for built-ins
 * @bi: Name of built-ins
 * @f: Function pointer
 */
typedef struct built_ins
{
	char *bi;
	int (*f)(arguments_t *args);
} built_ins_t;

/* main.c */
void initialize_struct(arguments_t *arguments);
int _exit_status(void);

/* strings_functions.c */
char *_strtok(char *buffer, const char *delim);
int _strlen(char *str);
char **tokarr(char *buffer);
int _putchar(int c);
int _puts(char *str);

/* string_functions2.c */
char *_memset(char *s, char b, unsigned int n);
char *_strcat(char *dest, char *src);
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
int printerr(char *str);

/* string_functions3.c */
char *_strdup(const char *str);
int _isalpha(int c);
char *comments(char *s);
char *_strchr(char *s, char c);

/* built-ins.c */
int print_env(arguments_t *args);
int builtins(arguments_t *args);
int custom_cd(arguments_t *args);
int call_exit(arguments_t *args);
int print_env(arguments_t *args);

/* built-ins2.c */
size_t list_len(const list_t *h);
int delete_node_at_index(list_t **head, size_t index);
void free_list(list_t *head);
list_t *add_node_end(list_t **head, const char *str);
list_t *arrtol(void);

/* built-ins3.c */
char **ltoa(list_t *head);
int _unsetenv(arguments_t *args);
int _setenv(arguments_t *args);
int _help(arguments_t *args);
void _help2(arguments_t *args);

/* built-insn4.c */
list_t *insert_node_at_index(list_t **head, unsigned int idx, char *str);

/* environment.c */
char *_getenv(char *name, arguments_t *args);
char *_append(char *s, char *token, char *buff);
char *get_path(arguments_t *args);
void evaluate_var(arguments_t *arguments);

/* shell.c */
void _fork(arguments_t *arguments);
void _shell(arguments_t *arguments);
char *convert(unsigned int num, int base);
void signal_handler(int signum);
void error(arguments_t *args, int errortype);

#endif /*_SIMPLE_SHELL_H_*/
