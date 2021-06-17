/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeon <djeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:01:44 by djeon             #+#    #+#             */
/*   Updated: 2021/06/17 17:34:56 by hoylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd			*ft_new(char *line, int pipe_flag, char quote)
{
	t_cmd		*result;

	if (!(result = (t_cmd*)malloc(sizeof(t_cmd))))
		return (NULL);
	result->cmdline = ft_split(line, ' ');
	result->pipe_flag = pipe_flag;
	result->quote = quote;
	result->next = NULL;
	return (result);
}

void			str_forward(char *line, int *i)
{
	int j;

	j = 0;
	while(line[(*i) + j + 1])
	{
		line[(*i) + j] = line[(*i) + j + 1];
		j++;
	}
	(*i)--;
}

char			check_quote(char *line)
{
	char		result;
	int			i;

	i = 0;
	result = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '"' && (result == 0 || result == '"'))
		{
			if (result == '"')
				result = 0;
			else
				result = '"';
			str_forward(line, &i);
		}
		else if (line[i] == '\'' && (result == 0 || result == '\''))
		{
			if (result == '\'')
				result = 0;
			else
				result = '\'';
			str_forward(line, &i);
		}
		i++;
	}
	return (result);
}



//char			check_quote(char *line)
//{
//	char		result;
//	int			i;
//	int			spc_flag;
//	int			first_spc_index;
//
//	i = 0;
//	result = 0;
//	spc_flag = 0;
//	first_spc_index = 0;
//	while (line[i] != '\0')
//	{
//		if(spc_flag == 0 && line[i] == ' ' && result != 0)
//			spc_flag = -1; //실행문 이상한거 그대로 넘겨줌.
//		if(line[i] == ' ' && spc_flag != -1)
//			spc_flag++;
//		if(first_spc_index == 0 && line[i] != ' ')
//			first_spc_index = -1;
//		else if(first_spc_index == -1 && line[i] == ' ' && result == 0)
//			first_spc_index = i;
//		if (line[i] == '"' && (result == 0 || result == '"'))
//		{
//			if (result == '"')
//				result = 0; //i 인덱스 " 없애 줘야함. 실행 cdㅇ같은 곳에도 있을ㄷ수 있음
//			else
//				result = '"';//i 인덱스 " 없애 줘야함.
//			str_forward(line, &i);
//		}
//		else if (line[i] == '\'' && (result == 0 || result == '\''))
//		{
//			if (result == '\'')
//				result = 0;
//			else
//				result = '\'';
//			str_forward(line, &i);
//		}
//		i++;
//	}
//	return (result);
//}
