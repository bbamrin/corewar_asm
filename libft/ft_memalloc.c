/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <pkathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 20:52:48 by pkathy            #+#    #+#             */
/*   Updated: 2019/09/07 21:31:18 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	unsigned char	*ret;
	size_t			i;

	i = 0;
	ret = (unsigned char *)malloc(size);
	if (!ret)
		return (NULL);
	while (i < size)
		ret[i++] = 0;
	return (ret);
}
