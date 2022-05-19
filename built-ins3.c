#include "simple_shell.h"

/**
 * ltoa - Converts linked list to array
 * @head: Pointer to first node
 *
 * Return: Converted array
 */
char **ltoa(list_t *head)
{
	int i = 0, len = list_len(head);
	char **arr = NULL;

	if (!head)
		return (NULL);
	arr = malloc(sizeof(char *) * (len + 1));
	if (!arr)
		return (NULL);

	while (head)
	{
		arr[i] = head->str;
		head = head->next;
		++i;
	}
	arr[i] = NULL;
	return (arr);
}

/**
 * _unsetenv - Unsets the specified environment variable
 * @args: Arugements structure
 * Return: 1 on success
 */
int _unsetenv(arguments_t *args)
{
	list_t *tmp = args->head;
	size_t i = 0;

	if (args->arr[1])
	{
		while (tmp)
		{
			args->index = i;
			if (!(_strncmp(tmp->str, args->arr[1], _strlen(args->arr[1]))))
			{
				delete_node_at_index(&(args->head), i);
				break;
			}
			tmp = tmp->next;
			++i;
		}
		return (1);
	}
	error(args, 1);
	return (1);
}

/**
 * _setenv - Sets specified enviroment variable
 * @args: Arguments structure
 *
 * Return: 1 on success
 */
int _setenv(arguments_t *args)
{
	char *variable = NULL;
	char *value = NULL;
	char temp[PATH_MAX] = {0};

	if (args->arr[1] && args->arr[2])
	{
		variable = args->arr[1];
		value = args->arr[2];
		_unsetenv(args);
		_strcat(temp, variable);
		_strcat(temp, "=");
		_strcat(temp, value);
		/* add_node_end(&(args->head), temp); */
		insert_node_at_index(&(args->head), args->index, temp);
		return (1);
	}
	error(args, 1);
	return (1);
}

/**
 * _help - Display information about builtin commands
 * @args: Arguments structure
 *
 * Return: 1
 */
int _help(arguments_t *args)
{
	if (args->arr[1])
	{
		_help2(args);
	}
	else
	{
		_puts("Type 'help name' to find out more about the function 'name'.\n\n"
				"env\nexit [n]\ncd [dir]\nunsetenv [name]\nsetenv [name]\nhelp [pattern...]\n");
	}
	return (1);
}

/**
 * _help2 - Display information about builtin commands
 * @args: Arguments structure
 */
void _help2(arguments_t *args)
{
	if (!_strcmp(args->arr[1], "env"))
		_puts("env\n"
				"    Prints the full environment\n");
	else if (!_strcmp(args->arr[1], "exit"))
		_puts("exit: exit [n]\n"
				"    Exit the shell.\n\n"
				"    Exits the shell with a status of N. If N is omitted, the exit status\n"
				"    is that of the last command executed.\n");
	else if (!_strcmp(args->arr[1], "cd"))
		_puts("cd: cd [dir]\n"
				"    Change the shell working directory.\n\n"
				"    Change the current directory to DIR. The default DIR is the value of the\n"
				"    HOME shell variable.\n");
	else if (!_strcmp(args->arr[1], "unsetenv"))
		_puts("unsetenv: unsetenv [name]\n"
				"    Remove an environmental variable.\n\n"
				"    Deletes the variable name from the enviroment. If the name does not\n"
				"    exist in the enviromnent, then the builtin succeeds, and the\n"
				"    environment is unchanged\n");
	else if (!_strcmp(args->arr[1], "setenv"))
		_puts("setenv: setenv [name] [value] [overwrite]\n"
				"    Change or add an environmental variable.\n\n"
				"    Adds the variable name to the environment with the value value, if name\n"
				"    does not already exist. If name does exist in the environment, then it's\n"
				"    value is changed to value if overwrite is nonzero; if overwrite is zero,\n"
				"    then the value of name is not changed.\n");
	else if (!_strcmp(args->arr[1], "help"))
		_puts("help: help [pattern...]\n"
				"    Displays brief summaries of builtin commands.\n\n"
				"    If PATTERN is specified, give detailed help on all commands matching PATTERN,\n"
				"    otherwise the list if help topics is printed.\n");
	else
		error(args, 2);
}
