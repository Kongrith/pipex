/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toon <toon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:41:12 by khkomasa          #+#    #+#             */
/*   Updated: 2024/11/16 21:31:41 by khkomasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	pid_t	pid[2];
	pid_t	id;
	char	**path_arr;
	char	**cmd1_arg;
	char	**cmd2_arg;
	char	*cmd1;
	char	*cmd2;
	int		fd_infile;
	int		fd_outfile;
}	t_data;

// Utility Functions
void	get_path_arr(t_data *data, char **envp);
void	parse_in_commands(t_data *data, char *path);
void	parse_out_commands(t_data *data, char *path);
void	exit_handler(t_data *data, char *cmd_failure, int err_code);
void	err_handler(t_data *data, char *cmd_failure, int err_code);
void	free_double_ptr(char **result);
void	cleanup(t_data *data);
void	free_ptr(char *ptr);

// Libft Functions
char	**ft_split(char *str, char delim);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
