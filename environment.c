#include "simple_shell.h"

/**
 * _append - Appends strings together
 * @buff: String to be returned
 * @token: PATH string to be appended
 * @s: User command to append
 *
 * Return: Appended string
 */
char *_append(char *buff, char *token, char *s)
{
	_strcat(buff, token);
	_strcat(buff, "/");
	_strcat(buff, s);
	return (buff);
}

/**
 * _getenv - Prints environmental variables
 * @name: name of the environmental variable
 * @args: Arguments struct
 * Return: value of variable
 * NULL on failure
 */
char *_getenv(char *name, arguments_t *args)
{
	size_t len = _strlen(name);
	list_t *head = args->head;

	while (head)
	{
		if (!_strncmp(name, head->str, len))
		{
			name = head->str + len;
			return (name);
		}
		head = head->next;
	}
	return (NULL);
}

/**
 * get_path - Looks for files in the current path
 * @args: String being evaluated
 *
 * Return: Command location
 * String on fail
 */
char *get_path(arguments_t *args)
{
	char *str = _getenv("PATH=", args), *token, *strr;
	static char buff[256 + PATH_MAX];
	struct stat st;
	int i = 0, word = 0, count = 0;

	if (!str)
		return (args->arr[0]);
	if (str[0] == ':' && !stat(args->arr[0], &st))
		return (args->arr[0]);
	if (!_strncmp(args->arr[0], "./", 2))
		return (args->arr[0]);
	while (str && str[i])
	{
		if (!word && str[i] != ':')
		{
			word = 1;
			++count;
		}
		else if (word && str[i] == ':')
			word = 0;
		i++;
	}
	token = _strtok(str, ":");
	while (token && args->arr[0])
	{
		strr = _append(buff, token, args->arr[0]);
		if (!stat(buff, &st))
			return (strr);
		if (count-- > 1 && *(token + _strlen(token) + 1) == ':' &&
		    !stat(args->arr[0], &st))
			return (args->arr[0]);
		token = _strtok(NULL, ":");
		_memset(buff, 0, 256 + PATH_MAX);
	}
	return (args->arr[0]);
}

/**
 * evaluate_var - Looks for variables in the current environmental  * variables
 * @arguments: An array of tokenized commands
 */
void evaluate_var(arguments_t *arguments)
{
	int i = 0, j = 0, flag = 0, len = 0;
	static char *number;

	while ((arguments->arr)[i])
	{

		if (*((arguments->arr))[i] == '$')
		{
			flag = 1;
			break;
		}
		i++;
	}
	if (flag)
	{
		((arguments->arr))[i]++;
		len = _strlen(((arguments->arr))[i]);
		while (environ[j])
		{
			if (!strncmp(((arguments->arr))[i], environ[j], len))
			{
				((arguments->arr))[i] = environ[j] + len + 1;
				break;
			}
			j++;
		}
	}
	else if (flag && !_strcmp(arguments->arr[i], "?")
		&& WIFEXITED(arguments->status))
	{
		arguments->arr[i] = number = convert(WEXITSTATUS(arguments->status), 10);
	}
}
