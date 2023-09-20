#include "header.h"

/**
 * _getenv - retrieves the value of an environment
 * @n: input
 * Return: value of an environment variable
 */
char *_getenv(char *n)
{
	int j = -1;
	size_t n_len;

	if (n == NULL || *n == '\0')
		return (NULL);
	if (environ == NULL)
		return (NULL);

	n_len = _strlen(n);

	while (environ[++j])
	{
		if (!_strncmp(environ[j], n, n_len) && environ[j][n_len] == '=')
		{
			return (environ[j] + n_len + 1);
		}
	}
	return (NULL);
}

/**
 * _how - locate the executable file
 * @t: input
 */
int _how(data *t)
{
	char *toke, *pat,
		*path = malloc(_strlen(_getenv("PATH") ? _getenv("PATH") : "") + 1);
	size_t toke_len;
	int extract = -1;

	if (!_getenv("PATH"))
		goto step_out;
	_strcpy(path, _getenv("PATH"));
	if (path == NULL)
		goto step_out;
	toke = strtok(path, ":");
	while (toke)
	{
		toke_len = _strlen(toke) + _strlen(t->argv[0]) + 2;
		pat = malloc(toke_len);
		if (pat == NULL)
			return (extract);
		_strcpy(pat, toke);
		_strcat(pat, "/");
		_strcat(pat, t->argv[0]);
		if (access(pat, F_OK) == 0)
		{
			free(t->argv[0]);
			t->argv[0] = _strdup(pat);
			free(pat);
			extract = 0;
			break;
		}
		free(pat);
		toke = strtok(NULL, ":");
	}
step_out:
	free(path);
	return (extract);
}

/**
 * create_new_entry - Initialize a new environment variable,
 *  or modify an existing one
 * @n: variable name
 * @v: variable value
 */
char *create_new_entry(char *n, char *v)
{
	size_t new_len = strlen(n) + strlen(v) + 2;
	char *new_entry = malloc(new_len);

	if (new_entry == NULL)
		return (NULL);

	strcpy(new_entry, n);
	strcat(new_entry, "=");
	strcat(new_entry, v);

	return (new_entry);
}
/**
 * _new_environ - Initialize a new environment variable,
 *  or modify an existing one
 * @n: name
 * @v: value
 */
char **_new_environ(char *n, char *v)
{
	int env_len = 0, j = 0;
	char *new_entry;
	char **new_environ;

	while (environ[env_len])
		env_len++;
	new_entry = create_new_entry(n, v);
	if (new_entry == NULL)
		return (NULL);
	new_environ = _getenv(n) ? malloc((env_len + 1) * sizeof(char *))
								: malloc((env_len + 2) * sizeof(char *));

	if (!new_environ)
	{
		free(new_entry);
		return (NULL);
	}
	for (j = 0; environ[j]; j++)
	{
		new_environ[j] = malloc(strlen(environ[j]) + 1);
		if (!new_environ[j])
		{
			free_array(new_environ);
			free(new_entry);
			return (NULL);
		}
		if (strncmp(environ[j], n, strlen(n)) == 0
		&& environ[j][strlen(n)] == '=')
			strcpy(new_environ[j], new_entry);
		else
			strcpy(new_environ[j], environ[j]);
	}
	if (!_getenv(n))
	{
		new_environ[env_len] = new_entry;
		new_environ[env_len + 1] = NULL;
	}
	else
		new_environ[env_len] = NULL;
	return (new_environ);
}

/**
 * _setenv - Initialize a new environment variable, or modify an existing one
 * @t: data
 * @n: name
 * @v: value
 */
int _setenv(data *t, char *n, char *v)
{
	char **new_environ;

	if (!n || !v)
		return (-1);

	new_environ = _new_environ(n, v);
	if (!new_environ)
		return (-1);
	environ = new_environ;
	t->flag = 1;

	return (0);
}
