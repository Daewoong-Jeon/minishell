/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 19:54:23 by djeon             #+#    #+#             */
/*   Updated: 2021/07/01 19:54:46 by seuyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "../libft/libft.h"
# include "structs.h"
# include "alloc_token.h"
# include "unset.h"

# define STDIN 			0
# define STDOUT 		1
# define STDERR 		2

extern int g_exit_status;

void				parse(t_cmd **cmd_list, char *line, char **envp);
t_cmd				*ft_new(char *line, int pipe_flag, char **envp, int exit_flag);
char				check_quote(char *line);
int					exec_function(t_cmd *cmd_list, char *argv[], char **envp[], int fds[]);
char				*strjoin_path(char const *s1, char const *s2);
int					check_whitespace(char *line);
void				exec(t_cmd *cmp_list, char *argv[], char **envp[]);
int					ft_cd(t_cmd *cmd_list);
int					ft_exit(t_cmd *cmd_list);
int					ft_pwd(int fd);
void				print_errstr(t_cmd *cmd_list);
//void				free_all(t_cmd *cmd_list);
void        		ft_echo(t_cmd *cmd_list);
void				free_list(t_cmd *cmd_list);

// env
void				ft_env(char **envp, int fd);
char				**copy_envp(char **envs);
//export
void				ft_export(t_cmd *cmd_list, char ***envp, int fd);
int					add_envp(t_cmd *cmd_list, char ***envp);
int					isvalid_export(char *line);
int					cnt_envp_row(char **envp);
char				**sort_env(char **envp);
int					haveequal(char *line);
void				add_key_envp(char ***envp, t_cmd *cmd_list, int keyindex);
//signal
void				set_signal(void);

//redirect
void				redirect(t_cmd *cmd_list, int **fds);
int					redirect_check(t_cmd *cmd_list);
#endif
