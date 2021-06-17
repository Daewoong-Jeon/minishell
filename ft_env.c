/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 14:13:14 by seojeong          #+#    #+#             */
/*   Updated: 2021/06/17 16:32:55 by seojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **envp) // 환경변수 목록 출력하는 함수
{
	int	i;
	
	i = 0;
	while (envp[i])
	{
			ft_putstr_fd(envp[i], STDOUT);
			ft_putchar_fd('\n', STDOUT);
			i++;
	}
}
