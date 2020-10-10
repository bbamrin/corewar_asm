/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:28:34 by pkathy            #+#    #+#             */
/*   Updated: 2019/09/13 20:41:58 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int		is_space(char c)
{
	if (c == '\n' || c == '\t'
	|| c == '\v' || c == '\f' || c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

static int		is_digit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);
	return (0);
}

int				ft_atoi(const char *str)
{
	int				sign;
	long long		n;

	n = 0;
	sign = 0;
	while (is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = 1;
		str++;
	}
	while (is_digit(*str))
	{
		n = n * 10 + *str++ - '0';
		if (n * 1000 < n)
			return (sign ? 0 : -1);
	}
	if (sign)
		return (n >= 0 ? -n : 0);
	return (n >= 0 ? n : -1);
}
