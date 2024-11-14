/*
./pipex in.txt "grep a" "wc -l" out.txt
*/

#include "pipex.h"
#include <string.h>

int process1(t_data *data, char **argv, char **envp)
{
	int fd;
	char **args;

	fd = data->fd_infile;
	close(data->pid[0]);
	dup2(fd, 0);
	close(fd);
	dup2(data->pid[1], 1);
	close(data->pid[1]);
	if (access(data->cmd1, R_OK) == -1)
	{

		write(2, data->cmd1_arg[0], strlen(data->cmd1_arg[0]));
		write(2, ": command not found", 20);
		write(2, "\n", 1);
		// data->err_flag = 1;
		// dprintf(2, "process1: %d\n", data->err_flag);
		exit(-1);
	}
	if (execve(data->cmd1, data->cmd1_arg, NULL) == -1)
	{
		perror("execve");
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int process2(t_data *data, char **argv, char **envp)
{
	int fd;
	char **args;

	fd = data->fd_outfile;
	close(data->pid[1]);
	dup2(fd, 1);
	close(fd);
	dup2(data->pid[0], 0);
	if (access(data->cmd2, R_OK) == -1)
	{
		write(2, data->cmd2_arg[0], strlen(data->cmd2_arg[0]));
		write(2, ": command not found", 20);
		write(2, "\n", 1);
		exit(1);
	}
	if (execve(data->cmd2, data->cmd2_arg, NULL) == -1)
	{
		perror("execve");
		exit(0);
	}
	return (0);
}

void ipc_setup(t_data *data, char **argv, char **envp)
{
	pid_t pid;

	data->err_flag = 0;
	if (pipe(data->pid) == -1)
	{
		perror("pipe");
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
		process1(data, argv, envp);
	else
	{
		// waitpid(pid, NULL, 0);
		// dprintf(2, "process2: %d\n", data->err_flag);
		if (data->err_flag == 0)
			process2(data, argv, envp);
		else
			exit(0);
	}
}

void pipex(t_data *data, char **argv, char **envp)
{
	data->fd_infile = open(argv[1], O_RDONLY);
	if (data->fd_infile == -1)
		exit (1);
	data->fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (data->fd_outfile == -1)
		exit(1);
	parse_commands(data);
	ipc_setup(data, argv, envp);
	// clean_up();
}

int main(int argc, char **argv, char **envp)
{
	t_data data;

	if (argc != 5)
		write(1, "Example Usage: ./pipex <infile> 'CMD1' 'CMD2' <outfile>\n", 56);
	else
	{
		if (!envp)
		{
			perror("PATH variable is not set");
			exit(EXIT_SUCCESS);
		}
		if (open(argv[1], O_RDONLY) == -1)
		{
			write(2, "x", 1);
			perror(ft_strjoin("-bash: ", argv[1]));
			exit(EXIT_SUCCESS);
		}
		if (access(argv[1], R_OK) == -1)
		{
			perror("permission");
			exit(EXIT_SUCCESS);
		}
		get_path_arr(&data, envp);
		data.cmd1_arg = ft_split(argv[2], ' ');
		data.cmd2_arg = ft_split(argv[3], ' ');
		pipex(&data, argv, envp);
	}
	return (0);
}
