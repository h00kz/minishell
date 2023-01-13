/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:24:24 by pdubacqu          #+#    #+#             */
/*   Updated: 2023/01/13 11:24:27 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

int		make_cmd(t_cmds *cmd, char **input_split, int *i);
int		make_file(t_cmds *cmd, char **input_split, int *i, int *n);
char	**vars(char **envp, char **input_split);
int		ft_parse_input_next(char **cmd_split, t_cmds *cmd, \
		char *input, char **envp);
t_cmds	*parse_input(char *input, char **envp);
void	ft_fork(t_cmds *cmd, char *input, char **envp);
t_cmds	*get_some_shit(t_cmds *cmd, char *input, char **envp, int pid);
int		make_args(t_cmds *cmd, char **input_split, int *i, int *n);
int		make_args_next(t_cmds *cmd, char **input_split, int *i, int *n);
char	**ft_make_input_split(char *input, char **envp);
void	ft_create_heredoc_in(char *str, int i);
void	ft_create_heredoc_out(char *str, int i);
int		make_right_heredoc(t_cmds *cmd, char **input_split, int *i);
int		make_left_heredoc(t_cmds *cmd, char **input_split, int *i);
void	ft_make_heredoc_in(t_cmds *cmd, char **input_split, int *i);
t_cmds	*ft_make_here_doc(char *input, char **envp);
t_cmds	*ft_get_heredoc_in(char *input, char **envp);
void	ft_get_here_doc_in(t_cmds *cmd, int *i);
int		ft_get_heredoc_in_next(char **input_split, t_cmds *cmd, int *i);
int		ft_make_here_doc_next(char **input_split, t_cmds *cmd, int *i);
void	ft_free_some_shit(char **input_split, t_cmds *cmd);
void	ft_free_some_shit_2(char **input_split, \
		int j, char *input, t_cmds *cmd);
void	ft_free_some_shit_3(char *input, char **cmd_split);
void	ft_free_some_shit4(char **input_split);
int		ft_strlen_sep(char *str);
int		ft_check_bool(char *str, int i, int boolean);
char	*add_space_heredoc(char *str, char *s, int *i, int *j);
char	*add_space(char *str, char *s, int i, int *j);
int		ft_check_add_space(int j, char *str, int i, int boolean);
int		ft_check_bool_redir(int boolean, int *i, char *input);
int		ft_make_redir_pipe(char *input, int *i);
int		ft_make_redir_left(char *input, int *i);
int		ft_make_redir_right(char *input, int *i);
int		ft_check_redir(char *input);
int		ft_left_redir(char **input_split, int *i);
char	*ft_str_add_space(char *str);
int		make_left_redir(t_cmds *cmd, char **input_split, int *i);
int		make_right_redir(t_cmds *cmd, char **input_split, int *i);
void	ft_increment(int *i, int *n);
t_cmds	*make_arg(char **input_split, int j, t_cmds *cmd);
char	*translate_env_vars(char *input, char **envp);
t_cmds	*ft_lstnew_node(char **envp);
t_cmds	*lstnew_cmd(char **input_split, char **envp);
char	**ft_cpy_envp(char **envp);
void	free_cmd(t_cmds *cmd);
char	**ft_split_input(char const *s, char c);
void	ft_free_split(char **strs);
void	ft_nfree_split(char **strs, int n);
void	ft_free_split(char **strs);
void	ft_nfree_split(char **strs, int n);
int		ft_count_word_split(char c, char const *str);
int		ft_check_bool_split(const char *str, int i, int boolean);
void	ft_skip_char(char const *s, size_t *i, int *boolean, char c);
char	**ft_split_input(char const *s, char c);
char	*ft_translate(char **envp, char *input);
int		ft_check(char **input, int *i, char **str, int boolean);
int		ft_last_check(char *input, int boolean, char **tmp, int *i);
void	ft_translate_env_next(int *i, char *tmp, char *input, char **str);
char	*ft_getenv(const char *var, char **env);
char	*ft_get_path(t_cmds *cmd, char *path);
char	**ft_make_double(char *s, char *s2, char **files);
void	ft_execve(t_cmds *cmd);
void	ft_no_execve(t_cmds *cmd);
void	ft_fork_execution(t_cmds *cmd);
int		ft_is_builtins(char *input);
void	ft_dup(t_cmds *cmd, int i);
void	ft_make_pipe(t_cmds *cmd);
void	ft_close(t_cmds *cmd);
void	sig_handler(int sig);
char	**ft_make_double(char *s, char *s2, char **files);
void	ft_execve(t_cmds *cmd);
void	ft_no_execve(t_cmds *cmd);
void	ft_builtins(t_cmds *cmd, t_cmds *save, int i);
void	ft_fork_execution(t_cmds *cmd);
void	ft_fork_exec(t_cmds *cmd, int i, t_cmds *save);
void	ft_no_fork(t_cmds *cmd, int pid);
int		ft_no_dup(t_cmds *cmd);
char	*ft_get_path(t_cmds *cmd, char *path);
char	**ft_copy(char **files, int *j, int i, char **str);

#endif