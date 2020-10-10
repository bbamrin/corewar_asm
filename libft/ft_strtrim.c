/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 19:13:32 by pkathy            #+#    #+#             */
/*   Updated: 2019/09/08 19:58:58 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

static size_t	skip_space(char *str, char direction, size_t start, size_t end)
{
	size_t i;

	i = start;
	if (direction)
		while (is_space(str[i]) && i < end)
			i++;
	else
		while (is_space(str[i]) && i > end)
			i--;
	return (i);
}

char			*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	j;
	size_t	size;
	char	*str;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	i = skip_space((char *)s, 1, 0, size);
	if (i == size)
		return (ft_strnew(0));
	j = skip_space((char *)s, 0, size - 1, 0);
	str = ft_strnew(j - i + 1);
	if (!str)
		return (NULL);
	str = ft_strncpy(str, (char *)&s[i], j - i + 1);
	return (str);
}
