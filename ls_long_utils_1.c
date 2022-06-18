/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_long_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 01:10:58 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/18 01:18:36 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_mod_time(struct stat *stats)
{
	char		*str;
	time_t		time_now;
	int			mod_time;

	str = ctime(&stats->st_mtime);
	mod_time = stats->st_mtime;
	time(&time_now);
	print_from_string(str, 4, 6);
	if ((time_now - mod_time > 15724800) && (time_now - mod_time > -1))
		print_from_string(str, 19, 5);
	else
		print_from_string(str, 11, 5);
}

void	print_users(struct stat *stats)
{
	struct passwd	*pw;
	struct group	*gr;

	pw = NULL;
	gr = NULL;
	pw = getpwuid(stats->st_uid);
	if (pw == NULL)
		space_after_nbr(stats->st_uid);
	else
		space_after_str(pw->pw_name);
	gr = getgrgid(stats->st_gid);
	if (gr == NULL)
		space_after_nbr(stats->st_gid);
	else
		space_after_str(gr->gr_name);
}

int	return_major_or_minor(int rdev, int option)
{
	if (option == 1)
		return (((int32_t)(((u_int32_t)(rdev) >> 24) & 0xff)));
	else
		return (((int32_t)((rdev) & 0xffffff)));
}

void	print_file_size(struct stat *stats)
{
	ft_putnbr(stats->st_size);
	ft_putchar(' ');
}
