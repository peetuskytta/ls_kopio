/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_long_prints.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 09:48:02 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/16 16:49:50 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_file_size(struct stat *stats, int pad)
{
	int	len;

	len = pad - ft_nblen(stats->st_size);
	while (len > 0)
	{
		ft_putchar(' ');
		len--;
	}
	ft_putnbr(stats->st_size);
	ft_putchar(' ');
}

void	print_links(struct stat *stats, int pad)
{
	int	len;

	len = pad - ft_nblen(stats->st_nlink);
	while (len > 0)
	{
		ft_putchar(' ');
		len--;
	}
	ft_putnbr(stats->st_nlink);
	ft_putchar(' ');
}

void	space_after_nbr(int nbr)
{
	ft_putnbr(nbr);
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
	char	*str;

	str = ctime(&stats->st_mtime);
	str = ft_strsub(str, 4, 12);
	space_after_str(str);
	free(str);
}

void	write_long_output(t_file *arr, t_data *info, int f_count, int i)
{
	print_block_total(arr, f_count);
	while (f_count > i)
	{
		print_rights(&arr[i].stats);
		print_links(&arr[i].stats, info->padding[0]);
		print_users(&arr[i].stats);
		print_file_size(&arr[i].stats, info->padding[1]);
		print_mod_time(&arr[i].stats);
		print_filename(&arr[i].stats, arr[i].name);
		if (i != f_count - 1)
			ft_putchar('\n');
		i++;
	}
}
