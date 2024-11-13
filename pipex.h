#ifndef PIPEX_H
# define PIPEX_H
// #include <limits.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdlib.h>
# include <stdio.h>

// #define BUFFER_SIZE 11
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
} t_data;

#include "pipex.h"

// int ft_is_delimiter(char c);
// int ft_words_len(char *str);
// char *ft_get_word(char *str);
char **ft_split(char *str, char delim);
int ft_strncmp(const char *s1, const char *s2, size_t n);
char *ft_strjoin(char const *s1, char const *s2);
size_t ft_strlen(const char *s);
size_t ft_strlcpy(char *dst, const char *src, size_t size);
// void ft_free(char **result);
void ipc_setup(t_data *data, char **argv, char **envp);
void parse_commands(t_data *data);
void get_path_arr(t_data *data, char **envp);
char *ft_strchr(const char *s, int c);

#endif
