/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 10:42:08 by warchang          #+#    #+#             */
/*   Updated: 2021/08/18 10:42:10 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <curses.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <dirent.h>

# define SPEC_REDIR ">|<"
# define SPEC_PIP "|"
# define QUOTE_SYM "\"\'"

typedef struct s_lst_env
{
	char				*env;
	char				*key;
	char				*val;
	struct s_lst_env	*next;
	struct s_lst_env	*prev;
}	t_lst_env;

typedef struct s_redir
{
	int		type_redir;
	char	*filename;
	int		num_redir;
}	t_redir;

typedef struct s_comm
{
	char		*command;
	char		**arg;
	int			flag_nonarg;
	char		*specs;
	int			cnt_arg;
	pid_t		pid;
	int			fd_read;
	int			fd_write;
	t_list		*lst_redir;
	int			flag_after_redir;
}	t_comm;

typedef struct s_data
{
	size_t		count_env;
	char		**my_env;
	t_lst_env	*lst_env;
	int			count_pipe;
	int			flag_end;
	int			ret;
}	t_data;

typedef struct s_count
{
	int	i;
	int	j;
	int	k;
	int	z;
	int	start;
	int	len;
	int	flag;
	int	count_drop_token;
	int	count_drop_token_redir;

}				t_count;

typedef struct s_global // use for signals
{
	int	return_value;
}	t_global;

t_global	g_global;

void		wexitstatus(int ret_value);
void		signals_new(void);
void		signals_def(void);
void		signals_ign(int signo);
void		kill_child_process(t_list *lst_comm);
t_list		*ft_preparser(t_data *data, char *input);
void		wait_child_process(t_list *lst_comm);
void		cycle_readline(t_list *lst_comm, t_data *data, char *input);
void		signal_normal(void);
void		conrol_d(void);
char		*tolower_str(char *str);
int			is_bins(t_comm *comm, t_data *data);
int			is_bins1(t_comm *comm, t_data *data);
int			execution1(char *path, t_comm *comm, t_data *data);
int			execution2(char *path, t_comm *comm, t_data *data);
int			exec_fd(t_comm *comm);
int			open_read(char *name);
int			open_add(char *name);
int			open_stop(char *name);
int			is_builtin(t_comm *comm, t_data *data);
int			exec_fork(t_list *lst_comm, t_data *data, int stdin);
int			simplest_exec(t_comm *comm, t_data *data);
char		*ft_strstr(const char *big, const char *little);
int			echo_b(t_comm *comm, int fd);
int			unset_built(char **args, t_data *data);
void		print_env(t_data *data, int fd);
t_list		*ft_put_syntax_error(char *str_error);
void		ctrl_c(int signo);
void		ctrl_slash(int status);
void		change_directory(char *path, int new_path, t_data *data);
int			cd_b(char **args, t_data *data);
char		*path_home(char *path, int rev_pars, t_data *data);
int			var_position(char *key, t_data *data);
char		*env_val(char *var, t_data *data);
char		**realloc_envv(int new_size, t_data *data);
void		new_val(char *key, char *value, t_data *data);
int			export(char **args, t_data *data, int in_fd);
int			ifkey(char c);
////dduck
t_list		*ft_parser(t_data *data, t_list *lst_token);
t_lst_env	*ft_get_envlist_of_envarr(char **ev, t_data *data);
char		**ft_get_envarr_of_envlst(t_lst_env	*first_lstenv, t_data *data);
void		ft_free_arr(char **arr);
void		ft_free_ptr(void *ptr);
void		ft_init_count(t_count *count);
////ft_parser
char		*ft_parse_processor(char *str, char **env, int *flag_qoute);
char		*ft_slash(char *str, int *i);
////ft_token
t_list		*ft_get_list_comm(t_data *data, t_list *token);
int			ft_its_redir(char *str);
void		ft_tkn_proc_arg(t_count *cnt, t_comm *comm, t_list *tkn);
void		ft_comm_processing(t_list **lst_tkn, t_count *cnt,
				t_list **lst_rdr);
char		**ft_get_ararg_is_lstarg(t_list *lst_arg);
////ft_token_utils
t_list		*ft_get_token(char *str, int *flag_error_syntax);
void		ft_check_tokensym(char *str, t_count *tc);
t_list		*ft_get_pos_list_token(int count_drop, t_list *lst_token);
////ft_token_redir_utils
t_list		*ft_get_list_redirect(t_list *token, t_count *cnt);
void		ft_get_number_lst_redir(t_list *lst_redir);
void		ft_get_flag_redir(int *flag_redir_read, int *flag_redir_write,
				t_list *lst_redir);
////ft_check_syntax
int			ft_check_syntax(char *str, int str_len);
int			ft_check_token_syntax(t_list *lst_token);
int			ft_check_sym(char sym, int flag);
////ft_init
int			ft_get_counttoken(t_list *token);
int			ft_init_dollar(t_count *cnt, int *i, char *str);
void		ft_init_count(t_count *count);
t_data		*ft_init_data(char **env);
t_comm		*ft_init_command_struct(void);
////ft_parse_dollar
char		*ft_dollar(char *str, int *i, char **env);
char		*ft_dollar_in_quote(char *str, int *i, char **env);
int			*ft_get_posenv(char *str, int *i);
////ft_parse_dollar_utils
void		ft_check_env(char **env, t_count *cnt, char *tmp);
////ft_parse_dquote
char		*ft_dquot(char *str, int *i, char **env, int *flag_quote);
////ft_parser_utils
//int	ft_symcount(t_list *lst_comm);
////ft_utils
int			ft_put_error(char *str, int flag_ret);
size_t		ft_size_double_arr(char **arr);
void		ft_refresh_dollar_quest(t_data *data);
////ft_utils2
void		ft_up_shlvl(t_lst_env *lst_env, t_data *data);
int			ft_get_count_pipe(t_list *lst_token);
////ft_env
void		ft_print_export(t_data *data, int in_fd);
int			ft_parse_env(t_lst_env *env);

t_lst_env	*ft_get_lst_ienv(t_data *data);
////ft_env_utils
t_lst_env	*ft_sort_env(t_lst_env *lst_env);
void		ft_free_env_struct(t_lst_env *lst_env);
t_lst_env	*ft_lst_env_del_elem(t_lst_env *lst_before, t_lst_env *lst_env);
////ft_export_utils
void		ft_rewrite_arr_env(t_data *data, char *env);
int			ft_export_check(char **args, int i);
////ft_list_utils_env
t_lst_env	*ft_refresh_env_of_arrenv(t_data *data);
////ft_free
void		ft_free_lst_env(t_lst_env **lst_env);
void		ft_free_lst_comm(t_list *lst_comm);
void		ft_free_redir_str(void *redir_strct);
////ft_export
void		ft_get_new_lst_env(t_data *data, char *new_str_env, char *key,
				char *val);
int			ft_flag_token(t_list *lst_token, t_data *data);
////
int			ft_exit(char **args);
int			ft_pwd(t_comm *comm);
int			ft_print_env(t_data *data, t_comm *comm, char **args);
int			dub_rev_redir(char *stop_word);
t_lst_env	*ft_lst_env_del_head(t_lst_env *tmp_lst_env);
t_lst_env	*ft_lst_env_del_elem(t_lst_env *lst_before, t_lst_env *lst_env);
void		ft_new_val_for_key(t_data *data, char *key, char *val);
////TEST
int			ft_print_arr_env(char **arr);
int			ft_print_token(t_list *token, char *name);
void		ft_print_env_test(t_lst_env *lst_env);
void		ft_print_comm(t_list *lst_comm, char *name);

////List_Utils
t_lst_env	*ft_init_lst_env(char *cont_env);
void		ft_lstadd_back_env(t_lst_env **lst, t_lst_env *new);
t_lst_env	*ft_lstlast_env(t_lst_env *lst);

//// Sklyapa
void		rl_replace_line(const char *c, int i);

#endif
