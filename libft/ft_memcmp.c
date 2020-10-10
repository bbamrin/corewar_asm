/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <pkathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 17:28:23 by pkathy            #+#    #+#             */
/*   Updated: 2019/09/10 18:14:12 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int		s;
	size_t	i;

	s = 0;
	i = 0;
	if (!n)
		return (0);
	while (i < n - 1 && ((unsigned char *)s1)[i] == ((unsigned char *)s2)[i])
	{
		s += ((unsigned char *)s1)[i] - ((unsigned char *)s2)[i];
		i++;
	}
	s += ((unsigned char *)s1)[i] - ((unsigned char *)s2)[i];
	return (s);
}
