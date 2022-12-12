#include "../header/minishell.h"

void	ft_free_line(char **line)
{
	int	i;

	i = 0;
	while (line && line[i] != NULL)
	{
		free(line[i]);
		i++;
	}
	free(line);
}

void	ft_free_getenv(char **line)
{
	int	i;

	i = 0;
	while (line && line[i] != NULL)
	{
		if (i != 1)
			free(line[i]);
		i++;
	}
	free(line);
}

int	chk_digit(char *tp)
{
	int	i;

	i = 0;
	while (tp[i])
	{
		if (tp[i] == PLUS || tp[i] == NEGAT)
			i++;
		else if (ft_isdigit(tp[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit_all(char **tp, char **env)
{
	(void)env;
	if (ft_strlen2(tp) > 2)
	{
		printf("exit\nexit: too many arguments\n");
		g_pid = 1;
	}
	else if (tp[1] && chk_digit(tp[1]) == 0)
	{
		printf("exit\nbash: exit: %s: numeric argument required\n", tp[1]);
		ft_free_line(tp);
		exit(0);
	}
	else
	{
		printf("exit\n");
		if (tp[1])
		{
			ft_free_line(tp);
			exit(ft_atoi(tp[1]));
		}
		ft_free_line(tp);
		exit(0);
	}
}

// edit 1