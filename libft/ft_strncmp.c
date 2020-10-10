/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 17:59:57 by pkathy            #+#    #+#             */
/*   Updated: 2019/09/14 17:11:47 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*ts1;
	unsigned char	*ts2;

	if (!n)
		return (0);
	ts1 = (unsigned char *)s1;
	ts2 = (unsigned char *)s2;
	while (*ts1 != 0 && *ts2 != 0 && *ts1 == *ts2 && --n)
	{
		if (*ts1 != *ts2)
			return (*ts1 - *ts2);
		ts1++;
		ts2++;
	}
	return (*ts1 - *ts2);
}
