#include "pipex.h"

void process1(t_data *data, char **argv, char **envp)
{
	printf("CMD1\n");
}

void process2(t_data *data, char **argv, char **envp)
{
	printf("CMD2\n");
}

void pipex(t_data *data, char **argv, char **envp)
{
	pid_t pid; // ต้อง include <sys/types.h>

	if (pipe(data->pd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE); // ต้อง include <stdlib.h>
	}
	if (pid == 0)
		process1(data, argv, envp);
	else
	{
		wait(NULL); // ต้อง include <sys/wait.h>
		process2(data, argv, envp);
	}
	close(data->pd[0]);
	close(data->pd[1]);
}

int main(int argc, char **argv, char **envp)
{
	t_data data;

	if (!envp)
		printf("Error: Empty ENV !!");
	if (argc != 5)
		printf("Example Usage: ./pipex infile 'ls -l' 'wc -l' outfile\n");
	pipex(&data, argv, envp);
	return (0);
}
