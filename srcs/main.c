/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:47:43 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/07 15:12:03 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av, char **env)
{
	int	n;

	if (ac < 5)
	{
		ft_putendl_fd("Usage: pipex [infile] cmd1 [args] cmd2 [args] [outfile]", 2);
		return (EXIT_FAILURE);
	}
	if (!env || (env && !*env))
		cmd_notfound();
	n = ac - 1;
	pipex(n, av + 1, env);
	return (EXIT_SUCCESS);
}
