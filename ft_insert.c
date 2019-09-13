/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 13:40:44 by sstark            #+#    #+#             */
/*   Updated: 2019/09/13 20:06:24 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_insert(char *where, char *what, size_t index)
{
	size_t	i;
	char	*str;

	i = 0;
	if (where)
		i += ft_strlen(where);
	if (index > i)
		return (NULL);
	if (what)
		i += ft_strlen(what);
	if (!(str = (char *)malloc(i)))
		return (NULL);
	ft_memcpy(str, where, index);
	str[index] = '\0';
	ft_strcat(str + index, what);
	ft_strcat(str, where + index);
	return (str);
}
