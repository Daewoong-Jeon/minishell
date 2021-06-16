/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeon <djeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 18:06:01 by djeon             #+#    #+#             */
/*   Updated: 2021/06/16 18:38:01 by djeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				non_builtin(t_cmd *cmd_list, char *argv[], char *envp[])
{
	char		*path;
	int			status;
	pid_t		pid;
	pid_t		wait_pid;

	path = NULL;
	if (ft_strncmp("ls", cmd_list->cmdline[0], 3) == 0)
	{
		pid = fork();
		path = "/bin/ls";
	}
	else if (ft_strncmp("ps", cmd_list->cmdline[0], 3) == 0)
	{
		pid = fork();
		path = "/bin/ps";
	}
	if (path != NULL && pid == 0)
	{
		execve(path, argv, envp);
		path = NULL;
		exit(0);
	}
	else if (path != NULL && pid != 0)
	{
		while ((((wait_pid = wait(&status)) == -1) && errno == EINTR))
		{
		}
		return (1);
	}
	else if (path == NULL && pid == 0)
		exit(0);
	return (0);
}

void			exec(t_cmd *cmd_list, char *argv[], char *envp[])
{
	if (ft_strncmp("pwd", cmd_list->cmdline[0], 4) == 0)
		printf("%s\n", getcwd(NULL, 0));
	else if (ft_strncmp("cd", cmd_list->cmdline[0], 3) == 0)
		ft_cd(cmd_list->cmdline[1]);
	else if (ft_strncmp("exit", cmd_list->cmdline[0], 5) == 0)
		exit(0); // need free function
	else if (non_builtin(cmd_list, argv, envp) == 0)
		ft_putstr_fd("command not found\n", 1);
}
