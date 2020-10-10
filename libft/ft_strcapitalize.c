/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 18:54:13 by pkathy            #+#    #+#             */
/*   Updated: 2019/07/09 19:24:34 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcapitalize(char *str)
{
	int		is_alpha_or_numeric_before;
	char	*tmp;

	tmp = str;
	is_alpha_or_numeric_before = 0;
	while (*str != '\0')
	{
		if (is_alpha_or_numeric_before && *str >= 'A' && *str <= 'Z')
			*str += 'a' - 'A';
		if (!is_alpha_or_numeric_before && *str >= 'a' && *str <= 'z')
			*str -= 'a' - 'A';
		if ((*str >= 'a' && *str <= 'z') || (*str >= 'A' && *str <= 'Z')
		|| (*str >= '1' && *str <= '9'))
			is_alpha_or_numeric_before = 1;
		else
			is_alpha_or_numeric_before = 0;
		str++;
	}
	return (tmp);
}
