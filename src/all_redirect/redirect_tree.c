#include "../../header/minishell.h"

static	int	redirect_util(char **tmp, int fd)
{
	if ((ft_strncmp(tmp[1], ">>", 10) == 0) && tmp[2]
		&& access(tmp[2], F_OK) == -1)
		fd = open(tmp[2], O_WRONLY | O_CREAT, 0666);
	else if ((ft_strncmp(tmp[1], ">>", 10) == 0) && tmp[2]
		&& access(tmp[2], F_OK) == 0)
		fd = open(tmp[2], O_WRONLY | O_APPEND, 0666);
	else if ((ft_strncmp(tmp[2], ">>", 10) == 0) && tmp[3]
		&& access(tmp[3], F_OK) == -1)
		fd = open(tmp[3], O_WRONLY | O_CREAT, 0666);
	else if ((ft_strncmp(tmp[2], ">>", 10) == 0) && tmp[3]
		&& access(tmp[3], F_OK) == 0)
		fd = open(tmp[3], O_WRONLY | O_APPEND, 0666);
	return (fd);
}

void	static	ft_redirect_echo_3(char **tmp, char **env, char *str)
{
	pid_t	pid;
	int		ret;

	ret = 0;
	ret = redirect_util(tmp, ret);
	pid = fork();
	if (pid == 0)
	{
		close(1);
		dup2(ret, 1);
		if (ft_strncmp(tmp[0], "echo", 10) == 0
			&& ft_strncmp(tmp[1], ">>", 10) == 0)
			printf("\n");
		else
			ft_get_tram(tmp[0], env, str, NULL);
		exit(0);
	}
	else
		wait(&pid);
	close(ret);
}

void	static	ft_redirect_exec(char **tmp, char **env, char *str)
{
	pid_t	pid;
	int		ret;

	ret = 0;
	ret = redirect_util(tmp, ret);
	str = malloc_and_chr(str);
	pid = fork();
	if (pid == 0)
	{
		close(1);
		dup2(ret, 1);
		ft_get_tram(str, env, str, NULL);
		exit(0);
	}
	else
		wait(&pid);
	close(ret);
	free(str);
}

void	static	redirect_echo_one(char **tmp)
{
	pid_t	pid;
	int		ret;

	ret = open(tmp[1], O_WRONLY | O_CREAT, 0666);
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

void	ft_redirect_tree(char **tmp, char **env, char *str)
{
	if ((ft_strncmp(tmp[0], ">>", 10) == 0) && tmp[1])
		redirect_echo_one(tmp);
	else if ((ft_strncmp(tmp[1], ">>", 10) == 0) && tmp[2]
		&& ft_strncmp(tmp[0], "echo", 10) == 0)
		ft_redirect_echo_3(tmp, env, str);
	else if ((ft_strncmp(tmp[2], ">>", 10) == 0) && tmp[2])
		ft_redirect_exec(tmp, env, str);
	else if ((ft_strncmp(tmp[1], ">>", 10) == 0) && tmp[2])
		ft_redirect_exec(tmp, env, str);
}
