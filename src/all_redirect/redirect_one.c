#include "../../header/minishell.h"

static	char	*split_strdup(char *line)
{
	char	**tp;
	char	*tp1;

	tp = NULL;
	tp1 = NULL;
	tp = ft_split(line, RDCTION_D);
	tp1 = ft_strdup(tp[0]);
	ft_free_line(tp);
	return (tp1);
}

void	static	ft_redirect_echo_1(char **tp, char **env, char *str)
{
	pid_t	pid;
	int		line;
	char	*tp1;

	tp1 = split_strdup(str);
	line = open(tp[3], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	pid = fork();
	if (pid == 0)
	{
		if (line == -1)
		{
			free(tp1);
			exit(EXIT_FAILURE);
		}
		close(1);
		dup2(line, 1);
		ft_get_tram(tp1, env, str, NULL);
		exit(0);
	}
	else
		wait(&pid);
	close(line);
	free(tp1);
}

void	static	redirect_exec_1(char **tp, char **env, char *str)
{
	pid_t	pid;
	int		line;

	line = 0;
	line = open(tp[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	pid = fork();
	if (pid == 0)
	{
		if (line == -1)
			exit(EXIT_FAILURE);
		close(1);
		dup2(line, 1);
		if (ft_strncmp(tp[0], "echo", 10) == 0
			&& ft_strncmp(tp[1], ">", 10) == 0)
			printf("\n");
		ft_get_tram(tp[0], env, str, NULL);
		exit(0);
	}
	else
		wait(&pid);
	close(line);
}

void	static	redirect_echo_one(char **tp)
{
	pid_t	pid;
	int		line;

	line = 0;
	line = open(tp[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	pid = fork();
	if (pid == 0)
	{
		if (line == -1)
			exit(EXIT_FAILURE);
		close(1);
		dup2(line, 1);
		exit(0);
	}
	else
		wait(&pid);
	close(line);
}

void	ft_redirect_one(char **tp, char **env, char *line)
{
	if ((ft_strncmp(tp[0], ">", MAX_SIZE + 4) == 0) && tp[1])
		redirect_echo_one(tp);
	else if ((ft_strncmp(tp[1], ">", MAX_SIZE + 4) == 0) && tp[2])
		redirect_exec_1(tp, env, line);
	else if ((ft_strncmp(tp[2], ">", MAX_SIZE + 4) == 0) && tp[3])
		ft_redirect_echo_1(tp, env, line);
}
