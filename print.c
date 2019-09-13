/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 19:48:09 by sstark            #+#    #+#             */
/*   Updated: 2019/09/13 20:06:15 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			type_parser(t_param *lst, t_list **ml)
{
	if (ft_charinstr("di", lst->type))
	{
		makestr_di(lst, ml);
		precision_dioux(lst, ml);
	}
	else if (ft_charinstr("csp", lst->type))
		makestr_csp(lst, ml);
	else if (ft_charinstr("ouxXb", lst->type))
	{
		makestr_oux(lst, ml);
		precision_dioux(lst, ml);
	}
	else if (ft_charinstr(FLOATS, lst->type))
		makestr_f(lst, ml);
	else
	{
		lst->str = (char *)sm((void *)ft_strnew(1), ml, 0);
		lst->str[0] = lst->type;
	}
}

int					ft_printf(const char *format, ...)
{
	t_list	*ml;
	t_param	*start;
	t_param	*lst;
	va_list	factor;
	int		i;

	va_start(factor, format);
	ml = NULL;
	convert_param((lst = size_revision(searching(format, &ml))), factor, &ml);
	va_end(factor);
	start = lst;
	while (lst)
	{
		type_parser(lst, &ml);
		check_flags(lst, &ml);
		lst = lst->next;
	}
	i = print((char *)format, start);
	exit_pf(ml, 0);
	return (i);
}
