/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:53:28 by mdkhissi          #+#    #+#             */
/*   Updated: 2021/11/04 15:46:55 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	ft_strallocpy(char **dst, char const *src, int from, int upto)
{
	char	*dest;

	dest = (char *)malloc(sizeof(char) * (upto - from) + 1);
	if (!dest)
	{
		dest = NULL;
		*dst = dest;
		return (0);
	}
	dest = ft_memcpy(dest, src + from, upto - from);
	dest[upto - from] = '\0';
	*dst = dest;
	return (1);
}

static int	count_sarrsize(char const *s, char c)
{
	int	i;
	int	n;
	int	upto;
	int	from;

	i = 0;
	n = 0;
	from = 0;
	while (s[i])
	{
		while (s[i] != c && s[i])
			i++;
		upto = i;
		while (s[i] == c && s[i])
			i++;
		if (upto > from)
			n++;
		from = i;
	}
	return (n);
}

static char	**splitstoarr(char const *s, char c, char **stab, int *n)
{
	int	i;
	int	k;
	int	upto;
	int	from;

	i = 0;
	k = 0;
	from = 0;
	while (s[i])
	{
		while (s[i] != c && s[i])
			i++;
		upto = i;
		while (s[i] == c && s[i])
			i++;
		if (upto > from && ft_strallocpy(&stab[k++], s, from, upto) == 0)
		{
			*n = -1;
			break ;
		}
		from = i;
	}
	return (stab);
}

char	**ft_split(char const *s, char c)
{
	int		sarrsize;
	int		n;
	char	**sarr;

	if (!s)
		return (NULL);
	n = count_sarrsize(s, c);
	sarrsize = n;
	sarr = (char **)malloc(sizeof(char *) * (sarrsize + 1));
	if (!sarr)
		return (NULL);
	sarr = splitstoarr(s, c, sarr, &n);
	if (n == -1)
	{
		free_arraystr(sarr);
		return (NULL);
	}
	sarr[sarrsize] = NULL;
	return (sarr);
}
