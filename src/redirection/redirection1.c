#include "../../header/minishell.h"

static	char	*bultin(char *str)
{
	char	**tp;
	char	*tp1;

	tp = ft_split(str, '>');
	tp1 = ft_strdup(tp[0]);
	ft_free_line(tp);
	return (tp1);
}

void	static	ft_redirection_echo(char **tp, char **env, char *str)
{
	pid_t	pid;
	int		ret;
	char	*tp1;

	tp1 = bultin(str);
	ret = open(tp[3], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	pid = fork();
	if (pid == 0)
	{
		if (ret == -1)
		{
			free(tp1);
			exit(EXIT_FAILURE);
		}
		close(1);
		dup2(ret, 1);
		ft_get_tram(tp1, env, str, NULL);
		exit(0);
	}
	else
		wait(&pid);
	close(ret);
	free(tp1);
}

void	static	ft_redirection_exec(char **tp, char **env, char *str)
{
	pid_t	pid;
	int		ret;

	ret = open(tp[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	pid = fork();
	if (pid == 0)
	{
		if (ret == -1)
			exit(EXIT_FAILURE);
		close(1);
		dup2(ret, 1);
		if (ft_strncmp(tp[0], "echo", 10) == 0
			&& ft_strncmp(tp[1], ">", 10) == 0)
			printf("\n");
		ft_get_tram(tp[0], env, str, NULL);
		exit(0);
	}
	else
		wait(&pid);
	close(ret);
}

void	static	ft_redirection_echo_1(char **tp)
{
	pid_t	pid;
	int		ret;

	ret = open(tp[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	pid = fork();
	if (pid == 0)
	{
		if (ret == -1)
			exit(EXIT_FAILURE);
		close(1);
		dup2(ret, 1);
		exit(0);
	}
	else
		wait(&pid);
	close(ret);
}

void	ft_redirection_1(char **tp, char **env, char *str)
{
	if ((ft_strncmp(tp[0], ">", 10) == 0) && tp[1])
		ft_redirection_echo_1(tp);
	else if ((ft_strncmp(tp[1], ">", 10) == 0) && tp[2])
		ft_redirection_exec(tp, env, str);
	else if ((ft_strncmp(tp[2], ">", 10) == 0) && tp[3])
		ft_redirection_echo(tp, env, str);
}