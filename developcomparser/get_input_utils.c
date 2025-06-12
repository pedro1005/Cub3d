/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte && gamado-x                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:15:40 by pedmonte          #+#    #+#             */
/*   Updated: 2025/06/12 17:49:06 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_countwords(char const *string, char c)
{
	int	i;
	int	countedwords;
	int	flag;

	i = 0;
	countedwords = 0;
	flag = 0;
	while (string[i])
	{
		if (string[i] != c && flag == 0)
		{
			flag = 1;
			countedwords++;
		}
		else if (string[i] == c)
			flag = 0;
		i++;
	}
	return (countedwords);
}

static char	*ft_allocate_insert(const char *string, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	while (start < end)
	{
		word[i] = string[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

static void	ft_all_ins_helper(const char *s, char c, char **tab)
{
	size_t	i;
	size_t	j;
	int		index;

	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			tab[j] = ft_allocate_insert(s, index, i);
			index = -1;
			j++;
		}
		i++;
	}
	tab[j] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = (char **)malloc((ft_countwords(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	ft_all_ins_helper(s, c, tab);
	return (tab);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;
	int	isneg;

	i = 0;
	isneg = 1;
	result = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			isneg = -1;
		i++;
	}
	while (nptr[i] > 47 && nptr[i] < 58)
	{
		result = (result * 10) + (nptr[i] - '0');
		i++;
	}
	return (result * isneg);
}
