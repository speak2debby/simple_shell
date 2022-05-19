#include "simple_shell.h"

/**
 * _atoi - converts string to an integer
 * @s: takes string
 *
 * Return: returns an integer
 */
int _atoi(char *s)
{
	unsigned int i = 0;
	unsigned long n = 0;

	if (*s == '+')
		s++;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
			n = n * 10 + (s[i] - '0');
		else
			return (-1);
		i++;
	}
	if (n > INT_MAX)
		return (-1);
	return (n);
}

/**
 * print_env - Prints environmental variables
 * @args: Arguments struct
 *
 * Return: 1 on success
 */
int print_env(arguments_t *args)
{
	list_t *head = args->head;

	while (head)
	{
		_puts(head->str);
		_puts("\n");
		head = head->next;
	}
	return (1);
}

/**
 * call_exit - Exits shell and free's allocated memory
 * @args: Arguments structure
 *
 * Return: Nothing
 */
int call_exit(arguments_t *args)
{
	int number = 0;

	if (args->arr[1])
	{
		number = _atoi(args->arr[1]);
		if (number == -1)
		{
			errno = ILLNUM;
			error(args, 21);
			args->exit_status = 2;
			return (1);
		}
	}
	else
	{
		number = args->exit_status;
	}
	free(args->arr);
	free(args->buf);
	free_list(args->head);
	exit(number);
}

/**
 * custom_cd - Changes directory
 * @args: Arguments structure
 *
 * Return: 1 on success
 */
int custom_cd(arguments_t *args)
{
	char *cwd = NULL, *temp = NULL;
	char *oldwd = NULL;
	int val = 0;
	char *home = _getenv("HOME=", args);

	oldwd = getcwd(oldwd, 0);
	if (args->arr[1] == NULL)
	{
		val = chdir(home ? home : oldwd);
	}
	else if (*args->arr[1] == '-')
	{
		val = chdir(_getenv("OLDPWD=", args) ? _getenv("OLDPWD=", args) : oldwd);
		_puts(getcwd(temp, 0)), _puts("\n"), free(temp);
	}
	else
		val = chdir(args->arr[1]);
	if (val == -1)
	{
		errno = NOTDIR;
		error(args, 3);
	}
	if (1)
	{
		args->arr[1] = "OLDPWD", args->arr[2] = oldwd;
		_setenv(args);
		args->arr[1] = "PWD", args->arr[2] = cwd = getcwd(cwd, 0);
		_setenv(args);
		free(cwd);
	}
	free(oldwd);
	return (1);
}

/**
 * builtins - Function that determines which built in to call
 * @args: Arguments structure
 *
 * Return: 1 on success
 * 0 on error
 */
int builtins(arguments_t *args)
{
	built_ins_t func_array[] = {
		{"env", print_env},
		{"exit", call_exit},
		{"cd", custom_cd},
		{"unsetenv", _unsetenv},
		{"setenv", _setenv},
		{"help", _help},
		{NULL, NULL}
	};
	int  i = 0;

	while (func_array[i].bi)
	{
		if (!_strcmp(args->arr[0], func_array[i].bi))
			return (func_array[i].f(args));
		i++;
	}
	return (0);
}
