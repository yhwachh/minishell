#include "../header/minishell.h"

int	egal_chk(char *line)
{
	int	i;
	
	i = 0;
	while (line[i])
	{
		if (line[i] == EGAL)
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlen2(char **line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

int	chk_dbl(char *line, char **env)
{
	char	**tp1;
	char	**tp2;
	int		i;

	tp1 = NULL;
	tp2 = NULL;
	i = 0;
	tp2 = ft_split(line, EGAL);
	while (env[i])
	{
		tp1 = ft_split(env[i], EGAL);
		if (ft_strncmp(tp1[0], tp2[0], 10) == 0)
		{
			env[i] = ft_strdup(line);
			ft_free_line(tp1);
			ft_free_line(tp2);
			return (1);
		}
		if (env[i + 1])
			ft_free_line(tp1);
		i++;
	}
	ft_free_line(tp1);
	ft_free_line(tp2);
	return (0);
}

char	**ft_concat(char **line)
{
	t_data	data;
	int		len;

	len = 0;
	data.tp = ft_init_line(data.tp);
	data.tp[data.j] = line[0];
	data.j++;
	while (line[++len])
	{
		if (((egal_chk(line[len]) == 1 && line[len + 1] == NULL))
			|| (egal_chk(line[len]) == 0 && egal_chk(line[len]) == 1))
			data.tp[data.j] = line[len];
		else if ((ft_strncmp(line[len + 1], "=", 10) == 0)
			&& egal_chk(line[len]) == 0)
			return (NULL);
		else if (egal_chk(line[len]) == 1 && egal_chk(line[len + 1]) == 0)
		{
			data.tp[data.j] = ft_strjoin(line[len], line[len + 1]);
			len++;
		}
		else
			data.tp[data.j] = line[len];
		data.j++;
	}
	return (data.tp);
}

void	export(char **line, char **env)
{
	char	*tp;
	int		a;
	int		i;

	a = ft_strlen2(env) - 1;
	tp = env[a];
	i = 0;
	line = ft_concat(line);
	if (line == NULL)
		return ;
	while (line[++i] != NULL)
	{
		if (egal_chk(line[i]) == 0 || check_nbr(line[i]) == 0)
			return ;
		if (chk_dbl(line[i], env) == 0)
		{
			env[a] = ft_strdup(line[i]);
			a++;
		}
	}
	env[a++] = tp;
	env[a] = (void *) END;
	free(line);
	g_pid = 0;
}

// edit 1