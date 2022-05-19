#include "simple_shell.h"

/**
 * _strdup - duplicates a string
 * @str: string
 *
 * Return: a pointer to the string
 */
char *_strdup(const char *str)
{
	char *s;
	int i = 0;

	if (str == NULL)
		return (NULL);
	while (str[i])
		i++;
	s = malloc(sizeof(char) * i + 1);
	if (s == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		s[i] = str[i];
		i++;
	}
	s[i++] = '\0';
	return (s);
}

/**
 * _isalpha - checks if the c is alpha
 * @c: takes character in ASCII
 *
 * Return: 0 or 1
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || ((c >= 'A' && c <= 'Z')) || c == '_')
		return (1);
	else
		return (0);
}

/**
 * comments - splits comments
 * @str: Takes string
 *
 * Return: string without comments
 */

char *comments(char *str)
{
	size_t i;
	char *s = NULL;

	i = 0;
	s = str;
	while (str && str[i])
	{
		if (str[0] == '#' || (str[i] == '#' && str[i - 1] == ' '))
		{
			*s = '\0';
		}
		s++;
		i++;
	}
	return (str);
}

/**
 * _strchr - locates a character in a string
 * @s: string
 * @c: character
 *
 * Return: returns a pointer
 */

char *_strchr(char *s, char c)
{
	while (*s && *s != c)
	{
		s++;
	}
	if (*s == c)
		return (s);
	return (NULL);
}
