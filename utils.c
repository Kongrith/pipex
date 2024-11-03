#include "pipex.h"

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
		cmd1_path = ft_strjoin(path, data->cmd1_arr[0]);
		cmd2_path = ft_strjoin(path, data->cmd2_arr[0]);
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
