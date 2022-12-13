#include "../header/minishell.h"

void	ft_cls_pipe(int *fd, int i)
{
	(void) i;
	close(fd[0]);
	close(fd[1]);
}

void	ft_exec_pipe(char *str, char **env, char *tps)
{
	char	**tp;

	tp = NULL;
	tp = parsing(str);
	if (ft_count(tp) == 1)
	{
		ft_redirect(tp, env, tps);
		return ;
	}
	str = ft_strjoin("/bin/", tp[0]);
	if (execve(str, tp, env))
	{
		str = ft_strjoin("/usr/bin/", tp[0]);
		if (ft_strchr(tp[0], SLASH_D) != NULL)
			ft_exec_slash(tp, env);
		else if (execve(str, tp, env))
			printf("can't find the command\n");
	}
	free(str);
}

void	ft_exec_chld(int fd_in, int *fd, char **str, int i)
{
	dup2(fd_in, STDIN_FILENO);
	if (str[i + 1] != NULL)
		dup2(fd[1], STDOUT_FILENO);
	close(fd_in);
	ft_cls_pipe(fd, 1);
}

void	ft_chk_pid(char *line, int fd, pid_t pid)
{
	int	i;
	int	stat;

	i = 0;
	stat = 0;
	close(fd);
	i = nbr_pipe(line);
	while (i > 0)
	{
		waitpid(pid, &stat, 0);
		wait(NULL);
		i--;
	}
	ft_dollar_point(stat);
}

void	ft_pipe_build(char **str, char **env, char *tp)
{
	pid_t	pid;
	int		fd_in;
	int		fd[2];
	int		j;

	fd_in = dup(STDIN_FILENO);
	j = 0;
	while (str[j])
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			ft_exec_chld(fd_in, fd, str, j);
			ft_exec_pipe(str[j], env, tp);
			exit(0);
		}
		else
		{
			dup2(fd[0], fd_in);
			ft_cls_pipe(fd, j++);
		}
	}
	ft_chk_pid(tp, fd_in, pid);
	ft_free_line(str);
}

// edit 1