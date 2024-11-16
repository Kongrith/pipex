/*
./pipex in.txt "grep a" "wc -l" out.txt
*/

#include "pipex.h"
#include <string.h>

void process1(t_data *data, char **argv, char **envp)
{
	int fd;
	// char **args;

	fd = data->fd_infile;
	close(data->pid[0]);
	dup2(fd, 0);
	close(fd);
	dup2(data->pid[1], 1);
	close(data->pid[1]);
	// if (data->cmd1)
	if (access(data->cmd1, R_OK) == -1)
	{
		write(2, data->cmd1_arg[0], ft_strlen(data->cmd1_arg[0]));
		write(2, ": command not found", 20);
		write(2, "\n", 1);
		// if (data->path_arr)
		// 	ft_free(data->path_arr);
		// if (data->cmd1_arg)
		// 	ft_free(data->cmd1_arg);
		cleanup(data);
		// if (data->path_arr)
		// 	ft_free(data->path_arr);
		// if (data->cmd1_arg)
		// 	ft_free(data->cmd1_arg);
		// if (data->cmd2_arg)
		// 	ft_free(data->cmd2_arg);
		// if (data->cmd1)
		// 	free(data->cmd1);
		// if (data->cmd2)
		// 	free(data->cmd2);

		exit(127);
	}
	// if (data->cmd2 != NULL)
	// 	free(data->cmd2);
	// if (data->cmd2_arg)
	// 	ft_free(data->cmd2_arg);
	// ft_free(data->path_arr);
	// char *cmd1;
	// cmd1 = (char *)malloc(ft_strlen(data->cmd1 + 1));
	// char **cmd1_arg;
	// cmd1_arg = (char *)malloc(ft_strlen(data->cmd1_arg + 1));
	char *cmd1 = "/bin/grepp";
	char *cmd1_arg[] = { "grepp", "a", NULL};

	// strcpy(cmd1, data->cmd1);
	// strcpy(cmd1_arg, data->cmd1_arg);
	// cleanup(data);
	// if (execve(data->cmd1, data->cmd1_arg, envp) == -1)
	// 	err_handler("execve\n", 205);
	if (execve(cmd1, cmd1_arg, NULL) == -1)
	{
		dprintf(2, "no process1\n");
		err_handler("execve\n", 205);
	}

	dprintf(2, "process1\n");
	// {
	// 	perror("execve");
	// 	exit(126);
	// }
	// return (0);
}

void process2(t_data *data, char **argv, char **envp)
{
	int fd;
	// char **args;

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
		// if (data->path_arr)
		// 	ft_free(data->path_arr);
		// if (data->cmd2_arg)
		// 	ft_free(data->cmd2_arg);
		cleanup(data);
		exit(127);
	}
	char *cmd2 = "/bin/wc";
	char *cmd2_arg[] = {"wc", "-w", NULL};
	// cleanup(data);
	// if (data->cmd1 != NULL)
	// 	free(data->cmd1);
	// if (data->cmd1_arg)
	// 	ft_free(data->cmd1_arg);
	// ft_free(data->path_arr);
	if (execve(cmd2, cmd2_arg, NULL) == -1)
	{
		dprintf(2, "no process2\n");
		err_handler("execve\n", 205);
	}
	dprintf(2, "process2\n");
	// if (execve(data->cmd2, data->cmd2_arg, envp) == -1)
	// 	err_handler("execve\n", 205);
	// {
	// 	perror("execve");
	// 	exit(126);
	// }
	// return (0);
}

void ipc_setup(t_data *data, char **argv, char **envp)
{
	pid_t pid;

	if (pipe(data->pid) == -1)
		err_handler("pipe\n", 202);
	// {
	// 	perror("pipe");
	// 	exit(EXIT_FAILURE);
	// }
	pid = fork();
	if (pid == -1)
		err_handler("fork\n", 203);
	// {
	// 	perror("fork");
	// 	exit(EXIT_FAILURE);
	// }
	if (pid == 0)
	{
		// if (data->cmd1 != NULL && data->cmd2 != NULL)
		// if (data->cmd1 && data->cmd1_arg)
			process1(data, argv, envp);
	}
	else
	{
		// if (data->cmd1  && data->cmd2)
		// if (data->cmd2 && data->cmd2_arg)
		// wait(NULL);
		process2(data, argv, envp);
	}
}

void pipex(t_data *data, char **argv, char **envp)
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
		// exit(EXIT_FAILURE);

	data->fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (data->fd_outfile == -1)
		err_handler(ft_strjoin("bash: ", argv[4]), errno);
		// exit(EXIT_FAILURE);

	parse_in_commands(data, NULL);
	parse_out_commands(data, NULL);
	ipc_setup(data, argv, envp);
}

int main(int argc, char **argv, char **envp)
{
	t_data data;

	// *data = NULL;
	// data = NULL;
	if (argc != 5)
		err_handler("Example Usage: ./pipex <infile> 'CMD1' 'CMD2' <outfile>\n", 200);
	// {
	// 	write(2, "Example Usage: ./pipex <infile> 'CMD1' 'CMD2' <outfile>\n", 56);
	// 	exit(EXIT_FAILURE);
	// }
	else
	{
		if (!envp)
			err_handler("PATH variable is not set\n", 201);
		// {
		// 	write(2, "PATH variable is not set\n", 25);
		// 	exit(EXIT_FAILURE);
		// }
		if (access(argv[1], O_RDONLY) == -1)
		{
			err_handler(ft_strjoin("-bash: ", argv[1]), errno);
			// exit(EXIT_FAILURE);
		}
		if (access(argv[1], R_OK) == -1)
		{
			err_handler(ft_strjoin("-bash: ", argv[1]), errno);
			// exit(EXIT_FAILURE);
		}
		dprintf(1, "------------- before -------------\n");
		pipex(&data, argv, envp);
		dprintf(1, "------------- after -------------\n");
		// cleanup(&data);
		// if (data.path_arr)
		// 	ft_free(data.path_arr);
		// if (data.cmd1_arg)
		// 	ft_free(data.cmd1_arg);
		// if (data.cmd2_arg)
		// 	ft_free(data.cmd2_arg);
	}
	return (0);
}
