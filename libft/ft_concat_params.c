/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concat_params.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 23:37:57 by pkathy            #+#    #+#             */
/*   Updated: 2019/09/13 22:04:14 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	str_arr_len(char **arr, int len)
{
	int sum;

	sum = 0;
	while (len-- > 1)
		sum += ft_strlen(arr[len]) + 1;
	return (sum);
}

char		*ft_concat_params(int argc, char **argv)
{
	char	*str;
	int		i;
	int		j;
	int		len;
	int		start;

	len = str_arr_len(argv, argc);
	i = 1;
	j = 0;
	start = 0;
	if (!(str = (char*)ft_memalloc(len * sizeof(char))))
		return (NULL);
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			str[start++] = argv[i][j++];
		}
		str[start++] = '\n';
		i++;
	}
	str[len - 1] = '\0';
	return (str);
}
