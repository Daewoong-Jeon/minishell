/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeon <djeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 14:56:10 by djeon             #+#    #+#             */
/*   Updated: 2021/07/02 18:12:53 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				check_digit(t_cmd *cmd_list)
{
	int			i;

	i = -1;
	while (cmd_list->cmdline[1].cmd[++i] != '\0') // 인자로 입력된 문자열에서 문자 하나씩 확인합니다.
		if (ft_isdigit(cmd_list->cmdline[1].cmd[i]) == 0) // 문자가 숫자가 아닐경우, 0을 반환합니다.
		{
			cmd_list->err_manage.errcode = 4;
			cmd_list->err_manage.errindex = 1;
			print_errstr(cmd_list); // 에러메시지를 출력합니다.
			if (cmd_list->exit_flag == 1) // 파이프가 없을 경우, 오류로 프로세스를 종료합니다.
				exit(-1);
			else
				return (0);
		}
	return (1);
}

int				ft_exit(t_cmd *cmd_list)
{
	if (cmd_list->exit_flag == 1) // exit 문자열은 파이프없이 단독으로 exit 명령어만 주어졌을 때 출력됩니다. 그리고 exit_flag 역시 파이프가 없을 떄 설정됩니다.
		printf("exit\n");
	if (cmd_list->cmdline[1].cmd != NULL) // exit 명령어에 인자가 주어졌을 때
	{
		if (check_digit(cmd_list) == 0) // 인자로 입력된 문자열 중에 숫자가 아닌 문자가 있는지 확인합니다. 숫자가 아닌 문자가 있을 경우, 0을 반환합니다.
			return (0); // check_digit 함수에서 오류메시지를 출력하므로 더이상 오류메시지를 출력하면 안되기 때문에 0을 반환합니다.
		if (cmd_list->cmdline[2].cmd != NULL) // 인자가 2개 이상 입력되었을 때, 오류로 인식하여 -1을 반환합니다.
		{
			cmd_list->err_manage.errcode = 2; // 오류메시지로 too many~ 를 출력합니다.
			return (-1); // 오류메시지만 출력하고 exit가 실행되면 안될 때, -1을 반환합니다.
		}
	}
	else if (cmd_list->exit_flag == 1) // 파이프가 없고 인자도 주어져지 않을 때
		exit(0);
	if (cmd_list->exit_flag == 1) // 파이프가 없고 숫자인자 한개가 주어졌을 때
		exit(ft_atoi(cmd_list->cmdline[1].cmd) % 256);
	return (0);
}
