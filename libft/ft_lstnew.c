/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 20:31:09 by pkathy            #+#    #+#             */
/*   Updated: 2019/09/10 21:01:30 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*res;
	void	*l_content;

	res = (t_list *)ft_memalloc(sizeof(t_list));
	if (!res)
		return (NULL);
	if (!content)
	{
		res->content = NULL;
		res->content_size = 0;
	}
	else
	{
		if (!(l_content = ft_memalloc(content_size)))
		{
			free(l_content);
			free(res);
			return (NULL);
		}
		ft_memmove(l_content, content, content_size);
		res->content = l_content;
		res->content_size = content_size;
	}
	res->next = NULL;
	return (res);
}
