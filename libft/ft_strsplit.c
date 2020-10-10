/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 20:04:07 by pkathy            #+#    #+#             */
/*   Updated: 2019/09/09 22:27:00 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*safe_str_alloc(char **dict, size_t wc, size_t size)
{
	size_t	i;
	char	*str;

	str = (char *)ft_memalloc(sizeof(char) * (size));
	if (!str)
	{
		i = 0;
		while (i < wc)
		{
			free(dict[i]);
			i++;
		}
		return (NULL);
	}
	return (str);
}

static size_t	skip_space(size_t start, char const *str, char space)
{
	size_t i;

	i = start;
	while (str[i] == space && str[i])
		i++;
	return (i);
}

static size_t	skip_word(size_t start, char const *str, char space)
{
	size_t i;

	i = start;
	while (!(str[i] == space) && str[i] != '\0')
		i++;
	return (i);
}

static char		**arr_alloc(char const *str, char c)
{
	size_t	i;
	size_t	j;
	char	**arr;
	int		wc;

	wc = 0;
	i = skip_space(0, str, c);
	while (str[i])
	{
		j = skip_space(i, str, c);
		i = skip_word(i, str, c);
		if (j != i)
			wc++;
		i = skip_space(i, str, c);
	}
	arr = (char **)ft_memalloc((wc + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	arr[wc] = 0;
	return (arr);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	wc;
	char	**str_arr;

	if (!s || !(str_arr = arr_alloc(s, c)))
		return (NULL);
	i = skip_space(0, s, c);
	wc = 0;
	while (s[i] && (j = i) == i)
	{
		k = 0;
		i = skip_word(i, s, c);
		i = skip_space(i, s, c);
		if (!(str_arr[wc] = safe_str_alloc(str_arr, wc, i - j + 1)))
			return (NULL);
		str_arr[wc][i - j] = 0;
		while (s[j] != c && s[j])
			str_arr[wc][k++] = s[j++];
		wc++;
	}
	return (str_arr);
}
