#include "../header/minishell.h"

int	tokenize(char **env, char *line, char **tp)
{
	if (ft_count(tp) == 1)
		ft_redirection(tp, env, line);
	else if ((ft_strncmp(tp[0], "echo", MAX_SIZE) == 0)
		&& ft_strncmp(tp[1], "$?", MAX_SIZE) == 0)
		echo_erreur(g_pid, 0);
	else if (ft_strncmp(tp[0], "echo", MAX_SIZE) == 0)
	{
		ft_echo(tp, env, line);
		//g_pid = 0;
	}
	else if (ft_strncmp(tp[0], "cd", MAX_SIZE) == 0)
		cd(tp);
	else if (ft_strncmp(tp[0], "pwd", MAX_SIZE) == 0)
		pwd(tp);
	else if (ft_strncmp(tp[0], "exit", MAX_SIZE) == 0)
		ft_exit_all(tp, env);
	else if (ft_strncmp(tp[0], "env", MAX_SIZE) == 0)
		ft_env(env);
	else if (ft_strncmp(tp[0], "unset", MAX_SIZE) == 0)
		ft_unset(tp, env);
	else if (ft_strncmp(tp[0], "export", MAX_SIZE) == 0)
		export(tp, env);
	else
		return (0);
	return (1);
}

void	ft_get_tram(char *str, char **env, char *line, char **pipe)
{
	char	**tp;

	tp = NULL;
	if (ft_strncmp(str, "$? + $?", MAX_SIZE + 1) == 0)
	{
		echo_erreur(g_pid, 1);
		ft_free_line(pipe);
		return ;
	}
	tp = parsing(str);
	if (ft_strncmp(tp[0], "echo", MAX_SIZE) == 0 && !tp[1])
	{
		printf("\n");
		return ;
	}
	ft_free_line(pipe);
	if (tp == NULL)
		return ;
	if (tokenize(env, line, tp) == 0)
		ft_exec(tp, env);
	ft_free_line(tp);
}

void	ft_tram(char *str, char **env)
{
	char	**pipe;
	int		i;

	pipe = NULL;
	i = 0;
	while (str[i] == SPACE_N)
		i++;
	if (str[i] == END)
		return ;
	if (!(nbr_quotes(str, 2) % 1 == 0))
		return ;
	if (!(nbr_quotes(str, 2) % 2 == 0))
		return ;
	pipe = ft_split(str, PIPE_N);
	if (pipe[1] && nbr_quotes(pipe[0], 2) == 0
		&& nbr_quotes(pipe[1], 2) == 0)
		ft_pipe_build(pipe, env, str);
	else
		ft_get_tram(str, env, str, pipe);
}

// edit 1