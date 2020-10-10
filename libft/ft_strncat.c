/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 21:44:58 by pkathy            #+#    #+#             */
/*   Updated: 2019/09/07 18:59:55 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char		*tmp;
	const char	*end;

	tmp = s1;
	end = s2 + n;
	while (*s1)
		s1++;
	while (s2 < end && *s2)
		*s1++ = *s2++;
	*s1 = 0;
	return (tmp);
}
