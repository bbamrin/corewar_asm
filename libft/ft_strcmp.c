/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 17:24:47 by pkathy            #+#    #+#             */
/*   Updated: 2019/09/07 19:40:24 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *s1, const char *s2)
{
	int				s;
	unsigned char	*ts1;
	unsigned char	*ts2;

	ts1 = (unsigned char *)s1;
	ts2 = (unsigned char *)s2;
	s = 0;
	while (*ts1 != 0 && *ts2 != 0 && *ts1 == *ts2)
		s += *ts1++ - *ts2++;
	s += *ts1 - *ts2;
	return (s);
}
