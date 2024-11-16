/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toon <toon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:27:34 by khkomasa          #+#    #+#             */
/*   Updated: 2024/11/16 18:48:38 by toon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process1(t_data *data, char **envp)
{
	int	fd;

	fd = data->fd_infile;
	close(data->pid[0]);
	dup2(fd, 0);
	close(fd);
	dup2(data->pid[1], 1);
	close(data->pid[1]);
	if (access(data->cmd1, R_OK) == -1)
	{
		write(2, data->cmd1_arg[0], ft_strlen(data->cmd1_arg[0]));
		write(2, ": command not found", 20);
		write(2, "\n", 1);
		cleanup(data);
		exit(127);
	}
	if (execve(data->cmd1, data->cmd1_arg, envp) == -1)
		err_handler("execve\n", 205);
}

void	process2(t_data *data, char **envp)
{
	int	fd;

	fd = data->fd_outfile;
	close(data->pid[1]);
	dup2(fd, 1);
	close(fd);
	dup2(data->pid[0], 0);
	if (access(data->cmd2, R_OK) == -1)
	{
		write(2, data->cmd2_arg[0], ft_strlen(data->cmd2_arg[0]));
		write(2, ": command not found", 20);
		write(2, "\n", 1);
		cleanup(data);
		exit(127);
	}
	if (execve(data->cmd2, data->cmd2_arg, envp) == -1)
		err_handler("execve\n", 205);
}

void	ipc_setup(t_data *data, char **envp)
{
	pid_t	pid;

	if (pipe(data->pid) == -1)
		err_handler("pipe\n", 202);
	if (pid == -1)
		err_handler("fork\n", 203);
	if (pid == 0)
		process1(data, envp);
	else
		process2(data, envp);
}

void	pipex(t_data *data, char **argv, char **envp)
{
	data->path_arr = NULL;
	data->cmd1_arg = NULL;
	data->cmd2_arg = NULL;
	data->cmd1 = NULL;
	data->cmd2 = NULL;
	get_path_arr(data, envp);
	data->cmd1_arg = ft_split(argv[2], ' ');
	data->cmd2_arg = ft_split(argv[3], ' ');
	data->fd_infile = open(argv[1], O_RDONLY);
	if (data->fd_infile == -1)
		err_handler(ft_strjoin("bash: ", argv[1]), errno);
	data->fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (data->fd_outfile == -1)
		err_handler(ft_strjoin("bash: ", argv[4]), errno);
	parse_in_commands(data, NULL);
	parse_out_commands(data, NULL);
	ipc_setup(data, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 5)
		err_handler("Example: ./pipex <infile> 'CMD1' 'CMD2' <outfile>\n", 200);
	else
	{
		if (!envp)
			err_handler("PATH variable is not set\n", 201);
		if (access(argv[1], O_RDONLY) == -1)
			err_handler(ft_strjoin("-bash: ", argv[1]), errno);
		if (access(argv[1], R_OK) == -1)
			err_handler(ft_strjoin("-bash: ", argv[1]), errno);
		pipex(&data, argv, envp);
	}
	return (0);
}
