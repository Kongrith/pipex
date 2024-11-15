#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_data
{
	pid_t pid[2];
	char **path_arr;
	char **cmd1_arg;
	char **cmd2_arg;
	char *cmd1;
	char *cmd2;
	int fd_infile;
	int fd_outfile;
	// int err_flag;
} t_data;

#include "pipex.h"

char **ft_split(char *str, char delim);
int ft_strncmp(const char *s1, const char *s2, size_t n);
char *ft_strjoin(char const *s1, char const *s2);
size_t ft_strlen(const char *s);
size_t ft_strlcpy(char *dst, const char *src, size_t size);
// void ft_free(char **result);
void ipc_setup(t_data *data, char **argv, char **envp);
// void parse_commands(t_data *data, char *path, int i);
void parse_in_commands(t_data *data, char *path);
void parse_out_commands(t_data *data, char *path);

void get_path_arr(t_data *data, char **envp);
char *ft_strchr(const char *s, int c);
void err_handler(char *cmd_failure, int err_code);
size_t ft_strlen(const char *s);
void ft_free(char **result);
void cleanup(t_data *data);
#endif
