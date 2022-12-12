#include "../header/minishell.h"

void	ft_exec_ph(char **tp, char **env)
{
	char	*line;
	int		stat;
	pid_t	pid;

	pid = fork();
	line = ft_strjoin("/bin/", tp[0]);
	if (pid == 0)
	{
		if (execve(line, tp, env))
		{
			line = ft_strjoin("/usr/bin/", tp[0]);
			if (execve(line, tp, env))
			{
				write(2, "minishell: command not found\n", 30);
				g_pid = 127;
				free(line);
				exit(0);
			}
		}
		exit(0);
	}
	waitpid(pid, &stat, 0);
	ft_dollar_point(stat);
	wait(&pid);
	free(line);
}

void	chk_exec(char **tp, char **env)
{
	pid_t	pid;
	char	**str;
	char	*line;
	int		i;
	int		stat;

	i = -1;
	str = NULL;
	pid = fork();
	line = tp[0];
	if (pid == 0)
	{
		while (line[++i])
			if (line[i] == SLASH_D)
				break ;
		str = ft_split(line, SLASH_D);
		if (execve(str[1], tp, env))
			printf("%s : No such file or directory\n", tp[0]);
	}
	waitpid(pid, &stat, 0);
	ft_dollar_point(stat);
	wait(&pid);
	ft_free_line(str);
}

void	ft_exec_slash(char **tp, char **env)
{
	pid_t	pid;
	int		stat;

	pid = fork();
	if (pid == 0)
	{
		if (execve(tp[0], tp, env))
			printf("%s : No such file or directory\n", tp[0]);
	}
	waitpid(pid, &stat, 0);
	ft_dollar_point(stat);
	wait(&pid);
}

void	ft_exec(char **tp, char **env)
{
	if (ft_strncmp(tp[0], "./", 2) == 0)
		chk_exec(tp, env);
	else if (ft_strchr(tp[0], SLASH_D) != NULL)
		ft_exec_slash(tp, env);
	else
		ft_exec_ph(tp, env);
}

// edit 1
