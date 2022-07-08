/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:54:35 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/08 21:10:32 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*parse_path(char **path_array, char *cmd)
{
	int		i;
	char	*working_cmd;
	char	*slashcmd;
	int		found;

	slashcmd = ft_strjoin("/", cmd);
	found = 0;
	i = 0;
	while (!found && path_array && path_array[i] != NULL)
	{
		working_cmd = ft_strjoin(path_array[i++], slashcmd);
		if (access(working_cmd, F_OK) == 0)
			found = 1;
		if (!found)
			free(working_cmd);
	}
	free(slashcmd);
	if (found)
		return (working_cmd);
	else
		return (NULL);
}

char	*getpath_worker(char *cmd, t_cmd *data)
{
	int		i;
	char	*path_var;
	char	**path_array;
	char	*working_cmd;

	i = 0;
	if (data->envr[0])
	{
		while (data->envr[i] != NULL)
		{
			path_var = ft_strnstr(data->envr[i], "PATH=", 5);
			if (path_var != NULL)
				break ;
			i++;
		}
		if (!path_var)
			return (NULL);
		path_var += 5;
		path_array = ft_split(path_var, ':');
		working_cmd = parse_path(path_array, cmd);
		free_arraystr(path_array);
		if (working_cmd)
			return (working_cmd);
	}
	return (NULL);
}

void	get_path(char **lst, t_cmd *data, int i)
{
	char	**tmp;
	char	*fullpath_cmd;

	tmp = ft_split(lst[i + 1], ' ');
	if (!tmp || (tmp && !*tmp))
	{
		free_arraystr(tmp);
		return ;
	}
	fullpath_cmd = getpath_worker(*tmp, data);
	if (!fullpath_cmd)
	{
		free_arraystr(tmp);
		free(fullpath_cmd);
		return ;
	}
	data->cmd_args[i] = tmp;
	data->cmd_path[i] = fullpath_cmd;
}

void	cmdarg_init(int n, t_cmd *data, char **env)
{
	int	i;
	
	data->cmd_args = malloc(n * sizeof(char **));
	i = 0;
	while (i < n)
		data->cmd_args[i++] = NULL;
	data->cmd_path = malloc(n * sizeof(char *));
	i = 0;
	while (i < n)
		data->cmd_path[i++] = NULL;
	data->pips = malloc ((n - 1) * sizeof(t_pipex));
	data->envr = env;
}

void	cmdarg_free(t_cmd *data, int i, int n)
{
	int	j;

	//if (n == 1 || n == 0)
	//{
		//free_arraystr(data->cmd_path);
		j = 0;
		(void)i;
		while (j < n)
		{
			//if (j != i)
			//{
				free_arraystr(data->cmd_args[j]);
				j++;
			//}
		}
	//}
	/*if (n == 2 || n == 0)
	{
		free_arraystr(data->cmd_path);
		free_arraystr(data->cmd_args[i]);
	}*/
}
