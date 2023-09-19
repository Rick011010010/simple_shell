#include "shell.h"

/**
 * getEnviron - Returns the string array copy of our environ.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0.
 */
char **getEnviron(info_t *info)
{
    if (!info->environ || info->env_changed)
    {
        info->environ = list_to_strings(info->env);
        info->env_changed = 0;
    }

    return (info->environ);
}

/**
 * Unsetenv - Remove an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 *            constant function prototype.
 * Return: 1 on delete, 0 otherwise.
 * @env_var: The string environment variable property.
 */
int Unsetenv(info_t *info, char *env_var)
{
    list_t *node = info->env;
    size_t index = 0;
    char *p;

    if (!node || !env_var)
        return (0);

    while (node)
    {
        p = starts_with(node->str, env_var);
        if (p && *p == '=')
        {
            info->env_changed = delete_node_at_index(&(info->env), index);
            index = 0;
            node = info->env;
            continue;
        }
        node = node->next;
        index++;
    }
    return (info->env_changed);
}

/**
 * Setenv - Initialize a new environment variable,
 *             or modify an existing one.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @env_var: The string environment variable property.
 * @value: The string environment variable value.
 * Return: Always 0.
 */
int Setenv(info_t *info, char *env_var, char *value)
{
    char *buf = NULL;
    list_t *node;
    char *p;

    if (!env_var || !value)
        return (0);

    buf = malloc(_strlen(env_var) + _strlen(value) + 2);
    if (!buf)
        return (1);
    _strcpy(buf, env_var);
    _strcat(buf, "=");
    _strcat(buf, value);
    node = info->env;
    while (node)
    {
        p = starts_with(node->str, env_var);
        if (p && *p == '=')
        {
            free(node->str);
            node->str = buf;
            info->env_changed = 1;
            return (0);
        }
        node = node->next;
    }
    add_node_end(&(info->env), buf, 0);
    free(buf);
    info->env_changed = 1;
    return (0);
}

