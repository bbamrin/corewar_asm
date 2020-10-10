/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:36:06 by pkathy            #+#    #+#             */
/*   Updated: 2019/09/10 16:11:32 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(long n)
{
	int		len;

	len = (!n ? 1 : 0);
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	char	*res;
	int		len;
	char	sign;
	long	temp;

	temp = n;
	len = int_len(temp);
	res = ft_strnew(n < 0 ? len + 1 : len);
	if (!res)
		return (NULL);
	if (!(sign = 0) && n < 0)
	{
		temp *= -1;
		res[0] = '-';
		sign = 1;
	}
	while (len > 0)
	{
		res[sign ? len : len - 1] = temp % 10 + '0';
		temp /= 10;
		len--;
	}
	return (res);
}
