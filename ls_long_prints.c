/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_long_prints.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:01:24 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/17 18:43:52 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_file_size(struct stat *stats)
{
	ft_putnbr(stats->st_size);
	ft_putchar(' ');
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

void	print_major_and_minor(struct stat *stats)
{
	int	major;
	int	minor;

	major = 0;
	minor = 0;
	major = return_major_or_minor(stats->st_rdev, 1);
	minor = return_major_or_minor(stats->st_rdev, 0);
	ft_putnbr(major);
	write(1, ", ", 2);
	ft_putnbr(minor);
	write(1, " ", 1);
}

void	write_long_output(t_file *arr, int f_count, int i)
{
	print_block_total(arr, f_count);
	while (f_count > i)
	{
		print_rights(&arr[i].stats, &arr[i]);
		print_links(&arr[i].stats);
		print_users(&arr[i].stats);
		if (arr[i].is_device == 1)
		{
			print_major_and_minor(&arr[i].stats);
		}
		else
			print_file_size(&arr[i].stats);
		print_mod_time(&arr[i].stats);
		print_filename(&arr[i].stats, arr[i].name);
		if (i != f_count - 1)
			ft_putchar('\n');
		i++;
	}
}
