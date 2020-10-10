/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 22:51:08 by pkathy            #+#    #+#             */
/*   Updated: 2019/09/13 22:21:31 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		len;
	char	*new;

	len = 0;
	while (src[len] != '\0')
		len++;
	new = (char*)malloc(len + 1);
	if (new == 0)
		return (0);
	len = 0;
	while (src[len] != '\0')
	{
		new[len] = src[len];
		len++;
	}
	new[len] = '\0';
	return (new);
}
