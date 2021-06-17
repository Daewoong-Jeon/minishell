/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 19:54:23 by djeon             #+#    #+#             */
/*   Updated: 2021/06/17 16:52:09 by seojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <stdio.h>

# define STDIN 			0
# define STDOUT 		1
# define STDERR 		2


typedef struct	s_cmd
{
	char			**cmdline;
	int				pipe_flag;
	char			quote;
	struct s_cmd	*next;
}				t_cmd;

void				parse(t_cmd **cmd_list, char *line);
t_cmd				*ft_new(char *line, int pipe_flag, char quote);
char				check_quote(char *line);
void				exec(t_cmd *cmd_list, char *argv[], char **envp[]);
int					ft_cd(char *string);

// env
void				ft_env(char **envp);
char				**copy_envp(char **envs);
//export
void				print_envp(char **envp);
int					isvalid_export(char *line);
void				remove_char(char *str, char c);
int					cnt_envp_row(char **envp);
void				ft_export(t_cmd *cmd_list, char ***envp);
int					add_envp(t_cmd *cmd_list, char ***envp);
#endif
