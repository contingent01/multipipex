/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 18:32:50 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/07 19:17:05 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	run_cmd(char **lst, t_cmd *data, int i, int n)
{
	int		finput;
	int		foutput;
	int		r;
	int		w;

	//cmdarg_free(data, 2);
	if (i == 0)
	{
		finput = open(lst[0], O_RDONLY);
		if (finput < 0)
		{
			//cmdarg_free(data, 1);
			perrxit("Error");
		}
	}
	if (i == n - 1)
	{
		foutput = open(lst[n], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (foutput < 0)
		{
			//cmdarg_free(data, 2);
			perrxit("Error");
		}
	}
	if (i == 0)
		r = i;
	else
		r = i - 1;
	w = i;
	if (i == 0)
		dup2(finput, data->pips[r].fd[0]);
		
	dup2(data->pips[r].fd[0], STDIN_FILENO);
	close(data->pips[r].fd[0]);
	
	if (i == n - 1)
		dup2(foutput, STDOUT_FILENO);
		
	dup2(data->pips[w].fd[1], STDOUT_FILENO);
	close(data->pips[w].fd[1]);
	if (execve(data->cmd_path[i], data->cmd_args[i], data->envr) == -1)
	{
		//cmdarg_free(data, 1);
		if (!data->cmd_path[i])
			cmd_notfound();
		else
			perrxit("Error");
	}
}

void	last_cmd(int *fd, char **av, char **env, t_cmd *data)
{
	int		foutput;

	//cmdarg_free(data, 1);
	foutput = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (foutput < 0)
	{
		cmdarg_free(data, 2);
		perrxit("Error");
	}
	waitpid(data->pid, 0, WNOHANG);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(foutput, STDOUT_FILENO);
	close(fd[1]);
	if (!data->fullpath_cmd2
		|| execve(data->fullpath_cmd2, data->cmd2, env) == -1)
	{
		cmdarg_free(data, 2);
		if (!data->fullpath_cmd2)
			cmd_notfound();
		else
			perrxit("Error");
	}
} // cmd1 < tst | cmd2 | cmd3 | cmd4

void	pipex(int n, char **lst, char **env)
{
	t_cmd	data;
	int		i;
	int		pid;
	int		n_cmd;
	int		j;

	cmdarg_init(n - 2, &data, env);
	i = 0;
	while (i < n)
		get_path(lst, &data, i++);
	n_cmd = n - 2;
	i = 0;
	j = 0;
	while (i < n_cmd)
	{
		if (pipe(data.pips[j].fd) == (-1))
		{
			cmdarg_free(&data, 0);
			perrxit("Error");
		}
		pid = fork();
		if (pid == (-1))
		{
			cmdarg_free(&data, 0);
			perrxit("Error");
		}
		else if (pid == 0)
			run_cmd(lst, &data, i, n_cmd);
		else
		{
			i++;
			pid = fork();
			if (pid == (-1))
			{
				cmdarg_free(&data, 0);
				perrxit("Error");
			}
			else if (pid == 0)
				run_cmd(lst, &data, i, n_cmd);
			else
				i++;
		}
		j++;
	}
	
	
}
