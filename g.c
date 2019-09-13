/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 13:48:26 by sstark            #+#    #+#             */
/*   Updated: 2019/09/13 20:06:24 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	g_edit(t_param *lst, t_list **ml)
{
	char *str;

	if (!ft_charinstr("gG", lst->type))
		return ;
	lst->precision = lst->precision == -1 ? 4 : lst->precision;
	pr_f(lst, ml);
	str = lst->str;
	while (*str != '.')
		str++;
	str += lst->precision;
	while (*str == '0')
	{
		if (*(str + 1) < '5' || *(str + 1) == '\0')
			lst->precision--;
		str--;
	}
	lst->type--;
}