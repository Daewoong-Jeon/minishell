/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 14:13:20 by seojeong          #+#    #+#             */
/*   Updated: 2021/07/02 15:03:15 by seojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			print_quote(char *str, int fd)
{
	int i;

	i = 0;
	if (haveequal(str))
	{
		while (str[i] != '=')
			i++;
		write(fd, str, ++i);
		write(fd, "\"", 1);
		write(fd, str + i, ft_strlen(str + i));
		write(fd, "\"", 1);
	}
	else
	{
		while (str[i])
			i++;
		write(fd, str, ++i);
		write(fd, "=", 1);
		write(fd, "\"\"", 2);
	}
}

void			print_export(char **envp, int fd)
{
	int		i;
	char	**sorted;

	i = 0;
	sorted = sort_env(envp);
	while (sorted[i])
	{
		ft_putstr_fd("declare -x ", fd);
		print_quote(sorted[i], fd);
		ft_putchar_fd('\n', fd);
		free(sorted[i]);
		i++;
	}
	free(sorted);
}

int				check_key(char **envp, char *line)
{
	int i;
	int key;

	i = 0;
	key = 0;
	if (haveequal(line))
	{
		while (line[key] != '=')
			key++;
	}
	else
	{
		while (line[key])
			key++;
	}
	while (envp[i])
	{
		if (ft_strncmp(envp[i], line, key) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int				add_envp(char *cmd, char ***envp)
{
	char		**new;
	int			row;
	int			i;

	i = 0;
	row = cnt_envp_row(*envp);
	if (!(new = (char **)malloc(sizeof(char *) * (row + 2))))
		return (0);
	while ((*envp)[i])
	{
		new[i] = ft_strdup((*envp)[i]);
		free((*envp)[i]);
		i++;
	}
	free(*envp);
	new[i] = ft_strdup(cmd);
	new[++i] = NULL;
	*envp = new;
	return (1);
}

void			ft_export(t_cmd *cmd_list, char ***envp, int fd)
{
	int			i;
	int 		keyindex;

	i = 1;
	if (cmd_list->cmdline[1].cmd)
	{
		while(cmd_list->cmdline[i].cmd && cmd_list->cmdline[i].redir_flag == 0)
		{
			if (isvalid_export(cmd_list->cmdline[i].cmd))
			{
				if ((keyindex = check_key(*envp, cmd_list->cmdline[i].cmd)) >= 0)
				{
					if (haveequal(cmd_list->cmdline[i].cmd))
						add_key_envp(envp, cmd_list->cmdline[i].cmd, keyindex);
				}
				else
					add_envp(cmd_list->cmdline[i].cmd, envp);
			}
			else
			{
				cmd_list->err_manage->errcode = 5;
				cmd_list->err_manage->errindex = i;
				print_errstr(cmd_list);
			}
			i++;
		}
	}
	else
		print_export(*envp, fd);
}
