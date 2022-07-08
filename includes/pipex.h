/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:47:47 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/07 22:48:45 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_pipex
{
	int fd[2];
}				t_pipex;

typedef struct s_cmd
{
	char		**cmd_path;
	char		***cmd_args;
	t_pipex		*pips;
	char		**envr;
	//int		pid;
}				t_cmd;

char	*parse_path(char **path_array, char *cmd);

char	*getpath_worker(char *cmd, t_cmd *data);
void	get_path(char **lst, t_cmd *data, int i);
void	cmdarg_free(t_cmd *data, int n);
void	cmdarg_init(int n, t_cmd *data, char **env);
char	**ft_split(char const *s, char c);
void	run_cmd(char **lst, t_cmd *data, int i, int n);
void	pipex(int ac, char **av, char **env);
size_t	ft_strlen(const char *s);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	cmd_notfound(void);
void	perrxit(char *s);
void	free_arraystr(char **arraystr);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);

#endif