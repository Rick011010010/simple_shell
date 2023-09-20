#include "shell.h"

/**
 * getHistoryFile - Gets the history file.
 * @info: Parameter struct.
 *
 * Return: Allocated string containing history file.
 */
char *getHistoryFile(info_t *info)
{
	char *history_file_path, *home_directory;

	home_directory = _getenv(info, "HOME=");
	if (!home_directory)
		return (NULL);
	history_file_path = malloc(sizeof(char) * (_strlen(home_directory) + _strlen(HIST_FILE) + 2));
	if (!history_file_path)
		return (NULL);
	history_file_path[0] = '\0';
	_strcpy(history_file_path, home_directory);
	_strcat(history_file_path, "/");
	_strcat(history_file_path, HIST_FILE);
	return (history_file_path);
}

/**
 * writeHistory - Creates a file or appends to an existing file.
 * @info: The parameter struct.
 *
 * Return: 1 on success, else -1
 */
int writeHistory(info_t *info)
{
	ssize_t file_descriptor;
	char *history_file = get_history_file(info);
	list_t *current_node = NULL;

	if (!history_file)
		return (-1);

	file_descriptor = open(history_file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(history_file);
	if (file_descriptor == -1)
		return (-1);
	for (current_node = info->history; current_node; current_node = current_node->next)
	{
		_putsfd(current_node->str, file_descriptor);
		_putfd('\n', file_descriptor);
	}
	_putfd(BUF_FLUSH, file_descriptor);
	close(file_descriptor);
	return (1);
}

/**
 * readHistory - Reads history from a file.
 * @info: The parameter struct.
 *
 * Return: Histcount on success, 0 otherwise
 */
int readHistory(info_t *info)
{
	int i, last = 0, line_count = 0;
	ssize_t file_descriptor, read_length, file_size = 0;
	struct stat file_stats;
	char *buffer = NULL, *history_file = get_history_file(info);

	if (!history_file)
		return (0);

	file_descriptor = open(history_file, O_RDONLY);
	free(history_file);
	if (file_descriptor == -1)
		return (0);
	if (!fstat(file_descriptor, &file_stats))
		file_size = file_stats.st_size;
	if (file_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return (0);
	read_length = read(file_descriptor, buffer, file_size);
	buffer[file_size] = '\0';
	if (read_length <= 0)
		return (free(buffer), 0);
	close(file_descriptor);
	for (i = 0; i < file_size; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			build_history_list(info, buffer + last, line_count++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buffer + last, line_count++);
	free(buffer);
	info->histcount = line_count;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * buildHistory_list - Adds an entry to a history linked list.
 * @info: Structure containing potential arguments. Used to maintain.
 * @buffer: Buffer.
 * @line_count: The history line count, histcount.
 *
 * Return: Always 0.
 */
int buildHistory_list(info_t *info, char *buffer, int line_count)
{
	list_t *current_node = NULL;

	if (info->history)
		current_node = info->history;
	add_node_end(&current_node, buffer, line_count);

	if (!info->history)
		info->history = current_node;
	return (0);
}

/**
 * renumberHistory - Renumbers the history linked list after changes.
 * @info: Structure containing potential arguments. Used to maintain.
 *
 * Return: The new histcount.
 */
int renumberHistory(info_t *info)
{
	list_t *current_node = info->history;
	int i = 0;

	while (current_node)
	{
		current_node->num = i++;
		current_node = current_node->next;
	}
	return (info->histcount = i);
}
