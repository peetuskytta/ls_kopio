/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_parse_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:20:30 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/17 21:30:33 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	init_variables(t_data *info)
{
	info->f_all = 0;
	info->f_long = 0;
	info->f_reve = 0;
	info->f_recu = 0;
	info->f_time = 0;
	info->nb_of_args = 0;
	info->file_count = 0;
	info->flag_count = 0;
	info->link_count = 0;
	info->arg_count = 0;
	info->arguments_on = 0;
	info->dir = NULL;
	info->ent = NULL;
}

static void	flag_save(char c, t_data *info)
{
	if (c == 'l')
		info->f_long = 1;
	else if (c == 'a')
		info->f_all = 1;
	else if (c == 'r')
		info->f_reve = 1;
	else if (c == 'R')
		info->f_recu = 1;
	else if (c == 't')
		info->f_time = 1;
	else
		ch_error(c);
}

static void	flag_check(t_data *info, char *str)
{
	int		i;
	size_t	len;

	i = 1;
	len = ft_strlen(str);
	if (len == 2)
		flag_save(str[1], info);
	if (len > 2)
	{
		while (str[i] != '\0')
		{
			flag_save(str[i], info);
			i++;
		}
	}
}

static void	parse_flags(char **str, t_data *info)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		if (str[i][0] == '-')
		{
			info->flag_count++;
			flag_check(info, str[i]);
		}
		i++;
	}
	info->arg_count = info->arg_count - info->flag_count;
}

void	primary_checks(char **str, int args, t_data *info)
{
	init_variables(info);
	info->nb_of_args = args;
	info->arg_count = args - 1;
	if (args > 1)
	{
		if (str[1][0] == '-' && str[1][1] != '\0')
			parse_flags(str, info);
		else
			return ;
	}
	if (args == 0)
		ft_putendl("usage: ./ft_ls [-larRt] [file ...]");
}
