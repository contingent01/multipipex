/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 18:32:50 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/09 00:05:10 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	run_cmd(char **lst, t_cmd *data, int i, int n)
{
	int		finput;
	int		foutput;
	int		r;
	int		w;
	int		j;

	//cmdarg_free(data, 2);
	//sleep(3);
	if (i == 0)
	{
		finput = open(lst[0], O_RDONLY);
		if (finput < 0)
		{
			cmdarg_free(data, i, n);
			perrxit("Error");
		}
	}
	if (i == n - 1)
	{
		foutput = open(lst[n + 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (foutput < 0)
		{
			cmdarg_free(data, i, n);
			perrxit("Error");
		}
	}
	if (i == 0)
		r = i;
	else
		r = i - 1;
	if (i == n - 1)
		w = i - 1;
	else
		w = i;
	//printf("i=%d\tr = %d\tw = %d\n",i, r, w);
	if (i == 0)
	{
		dup2(finput,STDIN_FILENO);
		close(finput);
	}
	else
		dup2(data->pips[r].fd[0], STDIN_FILENO);
	j = 0;
	while (j <= r)
	{
		close(data->pips[j].fd[0]);
		j++;
	}
	
	
	if (i == n - 1)
	{
		dup2(foutput, STDOUT_FILENO);
		close(foutput);
	}
	else
	{
		dup2(data->pips[w].fd[1], STDOUT_FILENO);
	}
	j = 0;
	while (j <= w)
	{
		close(data->pips[j].fd[1]);
		j++;
	}
	
	if (execve(data->cmd_path[i], data->cmd_args[i], data->envr) == -1)
	{
		cmdarg_free(data, i, n);
		if (!data->cmd_path[i])
			cmd_notfound();
		else
			perrxit("Error");
	}
}

void	pipex(int n, char **lst, char **env)
{
	t_cmd	data;
	int		i;
	int		pid;
	int		n_cmd;
	int		j;

	n_cmd = n - 2;
	printf("%d\n", n_cmd);
	cmdarg_init(n_cmd, &data, env);
	i = 0;
	while (i < n_cmd)
	{
		get_path(lst, &data, i);
		j = 0;
		while (data.cmd_args[i][j])
		{
			//printf("i = %d\tdata: %s\n", i, data.cmd_args[i][j]);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < n_cmd)
	{
		if (i < n_cmd - 1)
		{
			//printf("pippp\n");
			if (pipe(data.pips[i].fd) == (-1))
			{
				cmdarg_free(&data, i, n_cmd);
				perrxit("Error");
			}
		}
		pid = fork();
		if (pid == (-1))
		{
			cmdarg_free(&data, i, n_cmd);
			perrxit("Error");
		}
		else if (pid == 0)
			run_cmd(lst, &data, i, n_cmd);
		else
			i++;
	}
	cmdarg_free(&data, i, n_cmd);
	i = 0;
	while (i < n_cmd)
	{
		if (i < n_cmd - 1)
		{
			close(data.pips[i].fd[0]);
			close(data.pips[i].fd[1]);
		}
		wait(NULL);
		i++;
	}
	free(data.pips);

}
