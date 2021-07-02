/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 16:33:46 by djeon             #+#    #+#             */
/*   Updated: 2021/07/02 17:34:46 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			error_write(char *error_str, char *err_cmdline, char *err_cmdline2)
{
	int i;
	int j;

	i = -1;
	j = -1;
	if (err_cmdline == 0 || error_str == 0)
		return ;
	while (error_str[++i])
	{
		j = -1;
		if (error_str[i] == '%' && error_str[i + 1] == 's' && err_cmdline != 0)
		{
			while (err_cmdline[++j])
				write(2, &err_cmdline[j], 1);
			err_cmdline = err_cmdline2;
			i++;
		}
		else
			write(2, &error_str[i], 1);
	}
}

void			print_errstr(t_cmd *cmd_list)
{
	if (cmd_list->err_manage.errcode == 1)
	{
		error_write("minishell: %s: command not found\n" ,cmd_list->cmdline[0].cmd, 0); //status = 127
		g_exit_status = 127;

	}
	else if (cmd_list->err_manage.errcode == 2)
	{
		error_write("minishell: %s: too many arguments\n", cmd_list->cmdline[0].cmd, 0); //status = 1
		g_exit_status = 1;

	}
	else if (cmd_list->err_manage.errcode == 3)
	{
		error_write("minishell: %s: No such file or directory\n", cmd_list->cmdline[cmd_list->err_manage.errindex].cmd, 0); //status = 1
		g_exit_status = 1;

	}
	else if (cmd_list->err_manage.errcode == 4)
	{
		error_write("minishell: %s: %s: numeric argument required\n" ,cmd_list->cmdline[0].cmd, cmd_list->cmdline[cmd_list->err_manage.errindex].cmd); // status = 255
		g_exit_status = 255;

	}
	else if (cmd_list->err_manage.errcode == 5)
	{
		error_write("minishell: %s: not an identifier : %s\n", cmd_list->cmdline[0].cmd, ft_split(cmd_list->cmdline[1].cmd, '=')[0]); //status = 1
		g_exit_status = 1;
	}
}
