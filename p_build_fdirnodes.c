/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_build_fdirnodes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 19:47:52 by sstark            #+#    #+#             */
/*   Updated: 2019/09/13 20:06:24 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					ft_build_filedirnode_С(char *entry, T_DRND **ptr, \
												T_STAT *curstat, void **pile)
{
	size_t			length;

	ft_stemman(ptr);
	length = ft_strlen(entry);
	if (!((*ptr)->pathname = (char *)malloc(length + 1UL)))
		return (ft_stemreg(NULL, (char *)__func__, 0));
	ft_memcpy((*ptr)->pathname, (CV *)entry, length + 1UL);
	(*ptr)->namelength = length;
	(*ptr)->dirstat = curstat;
	if (length > ((t_stemstat *)pile[13])->max_name)
		((t_stemstat *)pile[13])->max_name = length;
	((t_stemstat *)pile[13])->unit_num += 1;
	return (0);
}

static inline void	getmax_majmin_size(T_STAT *elemstat, t_maxvolume *statcont)
{
	if ((elemstat->st_mode & S_IFBLK) && !(elemstat->st_mode & S_IFDIR))
	{
		if (statcont->maxmajor < major(elemstat->st_rdev))
			statcont->maxmajor = major(elemstat->st_rdev);
		if (statcont->maxminor < minor(elemstat->st_rdev))
			statcont->maxminor = minor(elemstat->st_rdev);
		return ;
	}
	if (statcont->maxsize < elemstat->st_size)
		statcont->maxsize = elemstat->st_size;
}

static inline void	ft_checkstats(t_maxvolume *statcont, T_STAT *elemstat)
{
	T_PSWD			my_passw;
	struct group	my_group;
	char			buff[statcont->substbuffsize];
	void			*useless_pointer[1];
	size_t			length;

	getpwuid_r(elemstat->st_uid, &my_passw, buff, statcont->substbuffsize, \
													(T_PSWD **)useless_pointer);
	if (statcont->maxlinks < elemstat->st_nlink)
		statcont->maxlinks = elemstat->st_nlink;
	length = ft_strlen(buff);
	if (statcont->maxuser < length)
		statcont->maxuser = length;
	statcont->total += elemstat->st_blocks * (elemstat->st_blksize / 4096);
	getgrgid_r(elemstat->st_gid, &my_group, buff, \
				statcont->substbuffsize, (struct group **)useless_pointer);
	length = ft_strlen(buff);
	if (statcont->maxgroup < length)
		statcont->maxgroup = length;
	getmax_majmin_size(elemstat, statcont);
}

int					ft_build_filedirnode_l(char *entry, T_DRND **ptr, \
												T_STAT *curstat, void **pile)
{
	size_t	length;

	ft_stemman(ptr);
	length = ft_strlen(entry);
	if (!((*ptr)->pathname = (char *)malloc(length + 1UL)))
		return (ft_stemreg(NULL, (char *)__func__, 0));
	ft_memcpy((void *)(*ptr)->pathname, (CV *)entry, length + 1UL);
	(*ptr)->namelength = length;
	(*ptr)->dirstat = curstat;
	ft_checkstats((t_maxvolume *)pile[13], curstat);
	return (0);
}

int					ft_build_filedirnode_1(char *entry, T_DRND **ptr, \
												T_STAT *curstat, void **pile)
{
	size_t			length;

	(void)pile;
	ft_stemman(ptr);
	length = ft_strlen(entry);
	if (!((*ptr)->pathname = (char *)malloc(length + 1UL)))
		return (ft_stemreg(NULL, (char *)__func__, 0));
	ft_memcpy((*ptr)->pathname, (CV *)entry, length + 1UL);
	(*ptr)->namelength = length;
	(*ptr)->dirstat = curstat;
	return (0);
}
