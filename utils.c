#include "pipex.h"

// void pipex_perror(char *param, int err)
// {
// 	ft_putstr_fd("pipex: ", 2);
// 	if (err == CMD_NOT_FOUND)
// 		ft_putstr_fd("command not found: ", 2);
// 	if (err == NO_FILE)
// 		ft_putstr_fd("no such file or directory: ", 2);
// 	if (err == NO_PERM)
// 		ft_putstr_fd("permission denied: ", 2);
// 	if (err == CMD_FAIL)
// 		ft_putstr_fd("command failed: ", 2);
// 	if (err == INV_ARGS)
// 		ft_putstr_fd("invalid number of arguments", 2);
// 	if (err == NO_MEMORY)
// 		ft_putstr_fd("no memory left on device", 2);
// 	if (err == DUP_ERR)
// 		ft_putstr_fd("could not dup fd", 2);
// 	if (err == PIPE_ERR)
// 		ft_putstr_fd("could not create pipe", 2);
// 	if (err == FORK_ERR)
// 		ft_putstr_fd("could not fork process", 2);
// 	if (err == NO_PATH)
// 		ft_putstr_fd("PATH variable is not set", 2);
// 	if (param && (err == CMD_NOT_FOUND || err == NO_FILE || err == NO_PERM ||
// 				  err == CMD_FAIL))
// 		ft_putstr_fd(param, 2);
// 	ft_putstr_fd("\n", 2);
// }


size_t ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		++i;
	return (i);
}

void ft_free(char **result)
{
	int i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		result[i] = NULL;
		i++;
	}
	free(result);
	result = NULL;
}

void get_path_arr(t_data *data, char **envp)
{
	int i;

	i = 0;
	data->path_arr = NULL;
	while (envp[i])
	{
		if (ft_strncmp("PATH", envp[i], 4) == 0)
			data->path_arr = ft_split(envp[i] + 5, ':');
		i++;
	}
	if (data->path_arr == NULL)
		printf("Error: Empty PATH !!\n");
}

void parse_commands(t_data *data)
{
	int i;
	char *path;
	char *cmd1_path;
	char *cmd2_path;

	i = 0;
	path = NULL;
	cmd1_path = NULL;
	cmd2_path = NULL;
	while (data->path_arr[i])
	{
		path = ft_strjoin(data->path_arr[i], "/");
		if (ft_strchr(data->cmd1_arg[0], '/') == NULL)
			cmd1_path = ft_strjoin(path, data->cmd1_arg[0]);
		else
			cmd1_path = data->cmd1_arg[0];
		if (ft_strchr(data->cmd2_arg[0], '/') == NULL)
			cmd2_path = ft_strjoin(path, data->cmd2_arg[0]);
		else
			cmd2_path = data->cmd2_arg[0];
		// dprintf(2, "cmd1_path: %s\n", cmd1_path);
		// dprintf(2, "cmd2_path: %s\n", cmd2_path);

		if (access(cmd1_path, F_OK) == 0 && access(cmd2_path, F_OK) == 0)
		{
			data->cmd1 = cmd1_path;
			data->cmd2 = cmd2_path;
			break;
		}
		cmd1_path = NULL;
		cmd2_path = NULL;
		i++;
	}
}
