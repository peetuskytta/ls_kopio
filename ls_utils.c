/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:05:23 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/21 13:48:31 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Writes short output.
*/
void	print_short(t_file *arr, int f_count)
{
	int	i;

	i = 0;
	while (i < f_count)
	{
		write(1, arr[i].name, ft_strlen(arr[i].name));
		if (i != f_count - 1)
			write(1, "\n", 1);
		i++;
	}
}

/*
**	Utility function to write from string[start] n amount of characters.
**	Used in long print time output. Adds extra whitespace after the output.
*/
void	print_from_string(char *str, int start, int n)
{
	char	*temp;

	temp = str;
	while (n > 0)
	{
		write(1, &temp[start], 1);
		start++;
		n--;
	}
	write(1, " ", 1);
}

/*
**	Utility function to check how many arguments are files and directories.
**	Used in counters and to define break from loops.
*/
void	count_files_directories(t_file *arr, t_data *info, int i)
{
	while (i < info->arg_count)
	{
		if (arr[i].file_ok == TRUE)
		{
			if (S_ISDIR(arr[i].stats.st_mode))
				info->f_d_count[0]++;
			if (!(S_ISDIR(arr[i].stats.st_mode)))
				info->f_d_count[1]++;
		}
		i++;
	}
}

void	allocation_check(t_data *info, t_file *arr, char *ft_name)
{
	if (arr == NULL)
	{
		free(info);
		ft_error_handler(1, ft_name);
	}
	else
		return ;
}

void	space_after_str(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, " ", 1);
}
