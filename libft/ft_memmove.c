/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <pkathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:48:30 by pkathy            #+#    #+#             */
/*   Updated: 2019/09/06 16:58:09 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*temp_dst;
	unsigned char	*temp_src;

	if (dst <= src)
		ft_memcpy(dst, src, len);
	else
	{
		temp_dst = (unsigned char *)dst + len;
		temp_src = (unsigned char *)src + len;
		while (temp_dst != dst)
			*--temp_dst = *--temp_src;
	}
	return (dst);
}
