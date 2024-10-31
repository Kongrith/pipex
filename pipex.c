#include "pipex.h"

void pipex(t_data *data, char **argv, char **envp)
{

}

// int main(int argc, char **argv, char **envp)
// {
// 	if (argc != 5)
// 	{
// 		return (0);
// 	}
// 	pipex();
// 	return (0);
// }

// #include <stdlib.h>
// #include <unistd.h>
// #include <limits.h>
// #include <sys/wait.h>
// #include <sys/types.h>
// #include <fcntl.h>
#include <stdio.h>

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
