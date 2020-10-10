/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 18:47:32 by pkathy            #+#    #+#             */
/*   Updated: 2019/09/08 19:00:31 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	s1_size;
	size_t	s2_size;

	if (!s1 || !s2)
		return (NULL);
	s1_size = !s1 ? 0 : ft_strlen(s1);
	s2_size = !s2 ? 0 : ft_strlen(s2);
	new_str = ft_strnew(s1_size + s2_size);
	if (!new_str)
		return (NULL);
	ft_memmove(new_str, s1, s1_size);
	ft_strcat(new_str, s2);
	return (new_str);
}
