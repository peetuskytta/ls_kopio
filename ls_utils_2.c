/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:16:33 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/10 14:45:10 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_filename(struct stat *stats, char *name)
{
	char	linkname[255];

	ft_memset(linkname, '\0', sizeof(linkname));
	if (S_ISLNK(stats->st_mode))
	{
		space_after_str(name);
		space_after_str("->");
		if (!(readlink(name, linkname, stats->st_size)))
			strerror(errno);
		ft_putstr(linkname);
	}
	else
		ft_putstr(name);
}


void	store_arguments(char **string, t_data *info, int i)
{
	info->list = (char **)ft_memalloc(sizeof(char *) * info->arg_count + 1);
	while (string[i] != NULL)
	{
		info->list[i] = ft_strdup(string[i]);
		i++;
	}
	info->list[i] = NULL;
	if (info->arg_count > 2)
		sort_list_ascending(info->list, info->arg_count);
}
/*DELETE BEFORE SUBMITTING*/
void	print_double(char **str)
{
	size_t	i;

	i = 0;
	while (str[i] != NULL)
	{
		ft_putendl(str[i]);
		i++;
	}
}
