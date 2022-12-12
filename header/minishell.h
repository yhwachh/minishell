#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <limits.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/dir.h>
# include <getopt.h>
# include <signal.h>
# include <assert.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# define ONE_QUOTES 39
# define TWO_QUOTES 34
# define SPACE_N 	32
# define PIPE_N		124
# define RDCTION_D	62
# define RDCTION_G	60
# define MAX_SIZE	6
# define DOLLAR		36
# define EGAL		61
# define ONE		48
# define NINE		57
# define END		0
# define NEGAT		45
# define PLUS		43
# define SLASH_D	47

typedef struct s_data
{
	char	**tp;
	char	**line;
	int		i;
	int		j;
	int		i2;
	int		j2;
}	t_data;

pid_t	g_pid;

int		ft_count(char **str);
int		ft_strlen2(char **str);
int		nbr_pipe(char *str);
int		check_quote(char *str);
int		ft_check_str(char *str);
int		check_nbr(char *str);
int		nbr_quotes(char *str, int nb);
int		quoate_type(char *str, int nb);
char	**ft_init_line(char **line);
char	**parsing(char *str);
char	*parsing_getenv(char **str, char *find);
char	*bultin_1(char *str);
void	pwd(char **tp);
void	cd(char **str);
void	ft_env(char **str);
void	ft_echo(char **str, char **find, char *line);
void	ft_redirection(char **tp, char **env, char *str);
void	ft_free_line(char **tp);
void	ft_dollar_point(int status);
void	ft_free_getenv(char **str);
void	echo_erreur(pid_t pid, int flag);
void	ft_pipe_build(char **str, char **env, char *tp);
void	ft_exit_all(char **tp, char **env);
void	export(char **str, char **env);
void	ft_exec(char **tp, char **env);
void	ft_tram(char *str, char **env);
void	ft_unset(char **str, char **env);
void	ft_exec_slash(char **tp, char **env);
void	ft_redirection_1(char **tp, char **env, char *str);
void	ft_redirection_2(char **tp, char **env, char *str);
void	ft_redirection_3(char **tp, char **env, char *str);
void	ft_redirection_4(char **tp, char **env, char *str);
void	ft_get_tram(char *str, char **env, char *line, char **pipe);

#endif
