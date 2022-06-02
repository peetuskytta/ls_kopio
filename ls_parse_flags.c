/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_parse_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:20:47 by pskytta           #+#    #+#             */
/*   Updated: 2022/05/31 10:23:15 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ls_check(char *str)
{
	if (str)
	{
		if (ft_strcmp(str, "ls") != 0)
			command_not_found(str);
	}
}
void	flag_check(t_data *info, char *str)
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

void	flag_save(char c, t_data *info)
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


void	parse_flags(char **str, t_data *info)
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
}

void	primary_checks(char **str, int args, t_data *info)
{
	ls_check(str[1]);
	init_variables(info);
	if (args > 1)
		parse_flags(str, info);
	else
		usage_error();
}