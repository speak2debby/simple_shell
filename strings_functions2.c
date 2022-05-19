#include "simple_shell.h"

/**
 * _memset - Fills memory with constant byte
 * @s: Array being filled
 * @b: Constant byte
 * @n: Amount of array elements to be filled with b
 *
 * Return: Filled buffer
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; ++i)
		s[i] = b;
	return (s);
}

/**
 * _strcat - Concatenates two strings
 * @dest: String being passed
 * @src: String being passed
 *
 * Return: Pointer to resulting string dest
 */
char *_strcat(char *dest, char *src)
{
	int i = _strlen(dest);
	int j = 0;

	while (src[j])
		dest[i++] = src[j++];
	dest[i] = src[j];
	return (dest);
}

/**
 * _strcmp - Compares two strings
 * @s1: First string being evaluated
 * @s2: Second string being evaluated
 *
 * Return: Difference between string characters being evaluated
 */
int _strcmp(const char *s1, const char *s2)
{
	size_t i = 0;

	while (s1[i] || s2[i])
	{
		if (s1[i] == s2[i])
			++i;
		else
			return (s1[i] - s2[i]);
	}
	return (0);
}

/**
 * _strncmp - Compares two strings at most n bytes
 * @s1: First string being evaluated
 * @s2: Second string being evaluated
 * @n: Amount of bytes to be evaluated
 *
 * Return: Difference between string characters being evaluated
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i = 0;

	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] == s2[i])
			++i;
		else
			return (s1[i] - s2[i]);
	}
	return (0);
}

/**
 * printerr - Prints error
 * @str: Error message
 *
 * Return: Number of characters printed
 */
int printerr(char *str)
{
	size_t i = _strlen(str);

	write(STDERR_FILENO, str, i);
	return (i);
}
