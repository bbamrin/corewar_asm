/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <pkathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 22:22:07 by pkathy            #+#    #+#             */
/*   Updated: 2019/09/07 18:17:18 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*end;

	if (!*s && c != 0)
		return (NULL);
	end = (char *)s;
	s += ft_strlen(s);
	while (s != end)
	{
		if (*s == (char)c)
			return ((char *)s);
		s--;
	}
	return ((char *)((char)c == *s ? s : NULL));
}
