#include "../../header/minishell.h"

static	int	ft_find(char **tp)
{
	int	i;

	i = 0;
	while (tp[i])
	{
		if (ft_strncmp(tp[i], "<<", MAX_SIZE + 4) == 0)
			return (i);
		i++;
	}
	return (0);
}

void	ft_redir_cat(char **tp)
{
	char	*buf;
	char	*str;

	buf = NULL;
	str = NULL;
	if (ft_strncmp(tp[1], "<<", 10) == 0)
	{
		str = malloc(sizeof(char) * 100000);
		buf = malloc(sizeof(char) * 100000);
		while (ft_strncmp(str, tp[2], 1000))
		{
			str = readline("heredoc> ");
			if (ft_strncmp(str, tp[2], 1000))
			{
				buf = ft_strjoin(buf, str);
				buf = ft_strjoin(buf, "\n");
			}
			free(str);
		}
		write(1, buf, ft_strlen(buf));
		free(buf);
	}
}

void	redir_one(char **tp)
{
	char	**tab;
	char	*buf;
	char	*str;

	tab = NULL;
	buf = NULL;
	str = NULL;
	tab = tp;
	if (ft_strncmp(tp[1], "<<", 10) == 0)
	{
		str = malloc(sizeof(char) * 100000);
		buf = malloc(sizeof(char) * 100000);
		while (ft_strncmp(str, tp[2], 1000))
		{
			str = readline("heredoc> ");
			if (ft_strncmp(str, tp[2], 1000))
			{
				buf = ft_strjoin(buf, str);
				buf = ft_strjoin(buf, "\n");
			}
			free(str);
		}
		tab[1] = NULL;
		ft_exec(tab, NULL);
		free(buf);
	}
}

void	redir_two(char **tp, int nb)
{
	char	*buf;
	char	*str;
	char	**tab;

	tab = NULL;
	str = NULL;
	buf = NULL;
	tab = tp;
	if (ft_strncmp(tp[nb], "<<", 10) == 0)
	{
		str = malloc(sizeof(char) * 100000);
		buf = malloc(sizeof(char) * 100000);
		while (ft_strncmp(str, tp[nb + 1], 1000))
		{
			str = readline("heredoc> ");
			if (ft_strncmp(str, tp[nb + 1], 1000))
			{
				buf = ft_strjoin(buf, str);
				buf = ft_strjoin(buf, "\n");
			}
			free(str);
		}
		tab[nb] = NULL;
		ft_exec(tab, NULL);
		free(buf);
	}
}

void	ft_redirect_four(char **tp, char **env, char *str)
{
	int	nb;

	(void)str;
	(void)env;
	nb = 0;
	nb = ft_find(tp);
	if ((ft_strncmp(tp[0], "cat", MAX_SIZE + 4) == 0)
		&& (ft_strncmp(tp[1], "<<", MAX_SIZE + 4) == 0))
		ft_redir_cat(tp);
	else if (ft_strncmp(tp[1], "<<", MAX_SIZE + 4) == 0)
		redir_one(tp);
	else if (nb > 1)
		redir_two(tp, nb);
}
