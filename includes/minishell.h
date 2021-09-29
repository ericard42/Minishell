#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>
# include "../libft/libft.h"
# include <termios.h>
# include <sys/wait.h> 
# include <errno.h> 
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <curses.h>
# include <term.h>

# define ENTER_KEY 10
# define DEL_KEY 127

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}				t_env;

typedef struct s_echo
{
	int		n;
	char	*text;
}				t_echo;

typedef struct s_quote
{
	int	si_quote;
	int	si_start;
	int	si_end;
	int	do_quote;
	int	do_start;
	int	do_end;
}				t_quote;

typedef struct s_redirector
{
	int	in;
	int	out;
	int	app;
}				t_redirector;

typedef struct s_input
{
	char			c;
	struct s_input	*next;
	struct s_input	*prev;
}				t_input;

typedef struct s_history
{
	char				*str;
	int					pos;
	struct s_history	*next;
	struct s_history	*prev;
}				t_history;

typedef struct s_operator
{
	struct s_list2		*cmd_lines;
	struct s_operator	*next;
	struct s_operator	*prev;
}				t_operator;

typedef struct s_frame
{
	t_operator		*pipes;
	t_operator		*operator;
	t_history		*history;
	struct s_list2	*arg;
	struct s_list2	*cmd_lines;
	char			*cmd;
	char			*line;
	char			*line_tmp;
	char			*cmd_line;
	int				semicolon;
	int				last;
	char			*path;
	int				ret;
	char			*ret_str;
	char			*pwd;
	t_echo			echo;
	int				fd;
	t_env			*env;
	t_input			*input;
	int				cur_now;
	int				hist_pos;
	int				hist_pos_last;
	char			*hist_now;
	char			*first_hist;
	int				i;
	int				j;
	int				p;
	int				y;
	int				redirector;
	t_redirector	red;
	int				nb_pipes;
	int				cp_stdin;
	int				cp_stdout;
	int				ext_code;
	int				sigquit;
	int				fbreak;
	t_quote			quote;
	struct termios	origin_term;
	pid_t			*pid;
	pid_t			first_pid;
	pid_t			exec_pid;
}				t_frame;

t_frame			*g_frame;

void			restore_term(void);
void			init_term(void);
void			sigint(int code);
void			frame_init(void);
void			stock_input(void);
void			ft_echo(void);
int				full_n(char *str);
char			*ft_strjoin_space(char *s1, char const *s2);
void			ft_pwd(int deb);
void			ft_exit(int exit_code);
void			env_init(char **env_str);
int				special_operator(t_list2 *cmd_lines);
void			print_env(void);
int				ft_export(char *str);
int				verif_env(char *str);
int				ft_unset(char *var);
char			*find_var_env(char *var);
int				redirector_verif(t_list2 *cmd_lines);
char			*ft_strjoin_n(char *s1, char *s2, int y, int n);
int				termcaps_init(void);
int				lexer_new(void);
t_quote			single_quote(t_quote quote);
t_quote			double_quote(t_quote quote);
void			add_char_input(char c);
int				del_char_input(void);
void			input_loop(void);
void			input_join(void);
int				add_history(void);
int				ft_putchar(int	c);
int				history_up(void);
int				history_down(void);
void			change_input(void);
void			ft_errors(int exit, char *error);
int				expension_new(int i);
char			*space_clear(char *str);
int				cd(char *path);
int				cmd_redirector(t_list2 *cmd_lines);
void			echo_call(t_list2 *cmd_lines);
void			export_call(t_list2 *cmd_lines);
void			unset_call(t_list2 *cmd_lines);
int				exec(t_list2 *cmd_lines);
int				chained_pipe(void);
void			ft_lstdelete_pipe(void);
void			append_operator(t_operator **head_ref, t_list2 *new_data);
void			ft_lstprint_operator(t_operator *pipe);
void			pipe_redirector(void);
void			ft_lstdelete_operator(void);
void			operator_redirection(void);
int				operators_verification(void);
void			quotes_verification(void);
void			exit_code(void);
char			**separate_path(void);
int				verification_prev_next(t_list2 *cmd_lines, int p);
int				redirector_split_utils(t_list2 *cmd_lines, char *tmp);
void			run_first_fork(void);
int				filename(char *str);
t_list2			*redirector_1(t_list2 *cmd_lines, t_list2 *tmp);
t_list2			*redirector_4(t_list2 *cmd_lines, t_list2 *tmp);
int				fd_redirector_1(t_operator *operator, int *fd);
int				fd_redirector_2(t_operator *operator, int *fd);
int				fd_redirector_3(t_operator *operator, int *fd);
void			ft_signal(int code);
void			cut(int i);
void			cut_ext(int j, int size, char *str);
int				lexer_1(int i);
int				lexer_2(int i);
int				lexer_3(int i);
int				lexer_4(int i, int j, t_quote quote);
int				lexer_6(int i, t_quote quote);
int				lexer_7(int i, int j, t_quote quote);
int				lexer_8(int i, int j, t_quote quote);
int				lexer_9(int i, int j, t_quote quote, int ret);
t_quote			lexer_5(int i, int j, t_quote quote);
t_quote			lexer_do(int i, int j, t_quote quote);
t_quote			lexer_si(int i, int j, t_quote quote);
char			**arglist_setup(t_list2 *cmd_lines);
char			**env_setup(void);
void			cmd_error(int x, char **arglist);
int				exec_loop(int *i, char **arglist, char **env, char **path);
void			exec_ext(char **path, char **arglist, char **env, int *i);
int				operator_check(t_list2 *cmd_lines, char quote, int i);
int				pipe_split(t_list2 *cmd_lines, int i);
int				redirector_split(t_list2 *cmd_lines, int i);
void			quotes_check(t_list2 *cmd_lines, char *tmp, char quote);
int				expension_ext_ext(int i, int y, int n, int ret);
char			*expension_ext(int i, char *str, int n);
char			*expension_quoting(char *str);
char			*expension_plus(char *tmp, int x, int y, int n);
void			normishell_goodbye(void);
void			ft_err_identifier(char *str);
void			print_env_declare(void);
int				find_cd_env(char *var);
void			delet_redir_amb(t_list2 *cmd_lines);
void			amb_redir(t_list2 *cmd_lines);

#endif
