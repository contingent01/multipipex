/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:41:47 by mdkhissi          #+#    #+#             */
/*   Updated: 2021/11/04 16:06:16 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	cmd_notfound(void)
{
	ft_putendl_fd("Error: command not found", 2);
	exit(EXIT_FAILURE);
}

void	perrxit(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

void	free_arraystr(char **arraystr)
{
	int	i;

	i = 0;
	if (arraystr)
	{
		while (arraystr[i] != NULL)
			free(arraystr[i++]);
		free(arraystr);
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	lens1;
	size_t	lens2;
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	result = malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!result)
		return (NULL);
	result = ft_memcpy(result, s1, lens1);
	ft_memcpy(result + lens1, s2, lens2);
	result[lens1 + lens2] = '\0';
	return (result);
}

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	f;

	if (!(*s2) || !s2)
		return ((char *)s1);
	i = 0;
	j = 0;
	while (i < n && s1[i])
	{
		f = i;
		if (s1[i] != s2[j])
			i++;
		else
			while (s1[i] == s2[j] && s1[i] && s2[j++] && i++ < n)
				;
		if (s2[j] == '\0')
			return ((char *)&s1[f]);
		else
			j = 0;
	}
	return (NULL);
}
