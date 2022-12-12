#include "../header/minishell.h"

void	ft_env(char **line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		printf("%s\n", line[i]);
		i++;
	}
	g_pid = 0;
}

void	ft_dollar_point(int pid)
{
	if (WIFSIGNALED(pid))
		g_pid = WTERMSIG(pid);
	else if (WIFEXITED(pid))
		g_pid = WEXITSTATUS(pid);
}

void	echo_erreur(pid_t status_global, int flag)
{
	if (flag == 1)
	{
		g_pid = 127;
		printf("%d: command not found\n", status_global);
	}
	else
	{
		g_pid = 127;
		printf("%d\n", status_global);
	}
}

char	**ft_init_line(char **line)
{
	int	i;

	i = 0;
	line = malloc (sizeof(char *) * 1000);
	while (i < 1000)
	{
		line[i] = NULL;
		i++;
	}
	return (line);
}
// edit 1