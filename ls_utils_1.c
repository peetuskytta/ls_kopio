/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 19:55:57 by pskytta           #+#    #+#             */
/*   Updated: 2022/05/30 19:55:57 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	parse_flags(t_data *arr, char **str, int i)
{
	while (str[i] != NULL)
	{
		if ( str[i][0] == '-')
		{
			init_flags(arr, str[i]);
			arr->flag_count++;
			i++;
		}
		else
			return ;
	}
}

void	init_flags(t_data *arr, char *str)
{
	int		i;
	size_t	len;

	i = 1;
	len = ft_strlen(str);
	if (len == 2)
		flag_save(str[1], arr);
	if (len > 2)
	{
		while (str[i] != '\0')
		{
			flag_save(str[i], arr);
			i++;
		}
	}
}

void	flag_save(char c, t_data *arr)
{
		if (c == 'l')
		arr->flags[0] = 1;
	else if (c == 'a')
		arr->flags[1] = 1;
	else if (c == 'r')
		arr->flags[2] = 1;
	else if (c == 'R')
		arr->flags[3] = 1;
	else if (c == 't')
		arr->flags[4] = 1;
	else
		ch_error(c);
}

void	handle_flags(t_data *arr, char **str)
{
	parse_flags(arr, str, 2);
	arr->arg_count = arr->flag_count + 2;
}

void	ls_driver(t_data *arr)
{
	if (arr->flags[1] == 1)
		arr = dir_stream_all(".", arr, 0);
	arr = dir_stream(".", arr, 0);
	ft_putnbr_endl(arr->file_count);

	int	i = 0;
	while (i < arr->file_count)
	{
		ft_putendl(arr[i].f_name);
		i++;
	}
}

t_data	store_data(struct dirent *ent, t_data f)
{
	ft_strcpy(f.f_name, ent->d_name);
	stat(f.f_name, &f.info);
	return (f);
}
