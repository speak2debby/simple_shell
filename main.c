#include "simple_shell.h"

/**
 * main - Simple shell
 * @ac: number of args
 * @argv: args vector
 * Return: 0;
 */
int main(int ac, char **argv)
{
	arguments_t arguments;

	arguments.ac = ac;
	arguments.argv = argv[0];
	initialize_struct(&arguments);
	signal(SIGINT, signal_handler);
	_shell(&arguments);
	return (0);
}

/**
 * initialize_struct - Simple shell
 * @arguments: args
 */
void initialize_struct(arguments_t *arguments __attribute__((unused)))
{
	/* char buf[PATH_MAX] = {0}; */
	/* char *cwd = getcwd(cwd = NULL, 0); */

	arguments->buf = NULL;
	arguments->arr = NULL;
	arguments->count = 0;
	arguments->head = arrtol();
	arguments->exit_status = 0;
	/* _strcat(buf, "OLDPWD="); */
	/* _strcat(buf, cwd); */
	/* add_node_end(&arguments->head, buf); */
	/* free(cwd); */
}

/**
 * _exit_status - exit status
 * Return: Exit number
 */
int _exit_status(void)
{
	int number = 0;

	/* if (errno == ILLNUM || errno == NOTDIR) */
	/* number = 2; */
	if (errno == EACCES)
		number = 126;
	else if (errno == ENOTDIR || errno == ENOENT)
		number = 127;
	return (number);
}
