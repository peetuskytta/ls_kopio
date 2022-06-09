/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_long_prints.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 09:48:02 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/09 17:12:17 by pskytta          ###   ########.fr       */
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

void	print_users(struct stat *stats)
{
	struct passwd	*pw;
	struct group	*gr;

	pw = NULL;
	gr = NULL;
	pw = getpwuid(stats->st_uid);
	ft_putstr(pw->pw_name);
	ft_putchar(' ');
	gr = getgrgid(stats->st_gid);
	if (gr != NULL)
	{
		ft_putstr(gr->gr_name);
		ft_putchar(' ');
	}
}

void	print_mod_time(struct stat *stats)
{
	char	*str;
	char	**str2;
	int		i;

	i = 0;
	str = ctime(&stats->st_mtimespec.tv_sec);
	str = ft_strtrim(str);
	str2 = ft_strsplit(str, ' ');
	space_after_str(str2[1]);
	if (ft_strlen(str2[2]) == 1)
		ft_putstr(" ");
	space_after_str(str2[2]);
	while (i < 5)
	{
		ft_putchar(str2[3][i++]);
	}
	ft_putstr(" ");
	ft_free_array(5, str2);
}

void	write_long_output(t_file *arr, t_data *info, int f_count, int i)
{
	while (f_count > i)
	{
		print_rights(&arr[i].stats);
		print_links(&arr[i].stats, info->padding[0]);
		print_users(&arr[i].stats);
		print_file_size(&arr[i].stats, info->padding[1]);
		print_mod_time(&arr[i].stats);
		ft_putendl(arr[i].name);
		//ft_putendl("");
		i++;
	}
}
