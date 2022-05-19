#include "simple_shell.h"

/**
 * convert - Function that converts our int to hex, octal, or binary
 * @num: Number passed into the function
 * @base: Base to convert to
 *
 * Return: Converted number of a certain base
 */
char *convert(unsigned int num, int base)
{
	static const char rep[] = "0123456789ABCDEF";
	static char buffer[11];
	char *ptr;

	ptr = &buffer[10];
	*ptr = '\0';
	do {
		*--ptr = rep[num % base];
		num /= base;
	} while (num != 0);
	return (ptr);
}

/**
 * error - Displays an error
 * @args: Command from user
 * @errortype: Value indicating error type
 */
void error(arguments_t *args, int errortype)
{
	char *number = convert(args->count, 10);

	printerr(args->argv), printerr(": ");
	if (errno == ENOTDIR || errno == ENOENT || errno == ENOTTY)
	{
		printerr(number), printerr(": "), printerr(args->arr[0]);
		write(STDERR_FILENO, ": not found\n", 12);
	}
	else if (errortype == 1)
	{
		printerr(number), printerr(": "), printerr(args->arr[0]);
		printerr(": bad variable name\n");
	}
	else if (errortype == 2)
	{
		printerr(number), printerr(": "), printerr(args->arr[0]);
		write(STDERR_FILENO, ": no help topics match '", 24);
		write(STDERR_FILENO, args->arr[1], _strlen(args->arr[1]));
		write(STDERR_FILENO, "'.\n", 3);
	}
	else if (errno  == NOTDIR)
	{
		printerr(number), printerr(": "), printerr(args->arr[0]);
		write(STDERR_FILENO, ": can't cd to ", 14);
		write(STDERR_FILENO, args->arr[1], _strlen(args->arr[1]));
		write(STDERR_FILENO, "\n", 1);
	}
	else if (errno == ILLNUM)
	{
		printerr(number), printerr(": "), printerr(args->arr[0]);
		printerr(": Illegal number: "), printerr(args->arr[1]), printerr("\n");
	}
	else
	{
		printerr(number), printerr(": "),
			printerr(args->arr[0]), printerr(": ");
		perror(NULL);
	}
}

/**
 * _shell - Creates a buffer, forks, executes, free's if necessary
 * @args: args
 */
void _shell(arguments_t *args)
{
	int get, val = 0;
	size_t len = 0;
	char *pt1, *pt2;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDERR_FILENO, "$ ", 2);
		get = getline(&(args->buf), &len, stdin);
		if (get == -1)
		{
			if (isatty(STDIN_FILENO))
				_puts("\n");
			free(args->buf), free_list(args->head), exit(args->exit_status);
		}
		pt1 = args->buf, pt2 = strchr(pt1, ';');
		if (pt2)
			*pt2++ = '\0';
		while (pt1)
		{
			args->count++, args->arr = tokarr(comments(pt1));
			if (!args->arr[0])
			{
				free(args->arr);
				break;
			}
			/* evaluate_var(args); */
			val = builtins(args);
			if (!val)
				_fork(args);
			free(args->arr);
			pt1 = pt2;
			if (pt1)
				pt2 = _strchr(pt1, ';');
			if (pt2)
				*pt2++ = '\0';
		}
	}
	free(args->buf), free_list(args->head), free(args->arr);
}

/**
 * _fork - Creates a buffer, forks, executes, free's if necessary
 * @args: array of tokens
 */
void _fork(arguments_t *args)
{
	pid_t pid = 0;
	char **env = NULL;

	if (*args->arr[0] == '/' || _getenv("PATH=", args))
	{
		pid = fork();
		if (pid < 0)
			return;
		if (pid == 0)
		{
			args->arr[0] = get_path(args);
			env = ltoa(args->head);
			if (execve(args->arr[0], args->arr, env) == -1)
			{
				error(args, 0), free(args->arr), free(args->buf);
				free_list(args->head), free(env), exit(127);
			}
		}
		else
		{
			waitpid(-1, &(args->status), 0);
			if (WIFEXITED(args->status))
				args->exit_status = WEXITSTATUS(args->status);
		}
	}
	else
	{
		errno = ENOTDIR, args->exit_status = 127,  error(args, 0);
	}
}

/**
 * signal_handler - Handles Ctrl + C signal
 * @signum: number of the signal
 */
void signal_handler(int signum __attribute__((unused)))
{
	_puts("\n");
	write(STDERR_FILENO, "$ ", 2);
	fflush(stdout);
}
