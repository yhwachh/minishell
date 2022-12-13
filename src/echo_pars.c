#include "../header/minishell.h"

int	quoate_type(char *str, int nbr)
{
	int	i;
	int	j;
	int	f;

	i = 0;
	j = 1;
	while (str[i])
	{
		if (str[i] == DOLLAR && j == nbr)
			f = i;
		if (str[i] == DOLLAR)
			j++;
		i++;
	}
	if (j > 0)
	{
		while (str[f++])
		{
			if (str[f] == ONE_QUOTES)
				return (0);
			if (str[f] == TWO_QUOTES)
				break ;
		}
	}
	return (1);
}

int	ft_check_n(char **str)
{
	int		i;

	i = 1;
	while (ft_strncmp(str[i], "-n", MAX_SIZE) == 0)
	{
		i++;
	}
	g_pid = 0;
	return (i - 1);
}

int	rt_echo(char **str, int i, char **find, char *line)
{
	char	*env;
	char	**tp;
	int		id;

	id = 0;
	tp = ft_split(str[i], DOLLAR);
	env = parsing_getenv(find, tp[0]);
	free(tp);
	if (env)
	{
		if (ft_check_str(line) == 1)
			printf("%s", env);
		else if (ft_check_str(line) == 0)
			printf("%s ", env);
		id++;
	}
	return (id);
}

int	check_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (((str[i] == TWO_QUOTES && str[i + 1] == TWO_QUOTES)
				|| (str[i] == TWO_QUOTES && ft_isalpha(str[i - 1]) == 1))
			&& (ft_isalpha(str[i + 1]) == 1 && str[i + 1] != SPACE_N))
			return (1);
		i++;
	}
	return (0);
}

void	ft_echo(char **str, char **find, char *line)
{
	int	i;
	int	id;
	int	qt;

	if (ft_strncmp(str[1], "-n", MAX_SIZE) == 0 && !str[2])
		return ;
	qt = 1;
	i = ft_check_n(str);
	while (str[++i])
	{
		id = 0;
		qt = 1;
		if (str[i][0] == DOLLAR && quoate_type(line, qt))
			id = rt_echo(str, i, find, line);
		if (id == 0 && str[i][0] != ONE_QUOTES && ft_check_str(line) == 0 && str[1][0] != NEGAT)
			printf("%s ", str[i]);
		if (id == 0 && str[i][0] != ONE_QUOTES && ft_check_str(line) == 0 && str[1][0] == NEGAT)
			printf("%s", str[i]);
		else if (id == 0 && str[i][0] != ONE_QUOTES && ft_check_str(line) == 1)
			printf("%s", str[i]);
	}
	if (ft_strncmp(str[1], "-n", MAX_SIZE))
		printf("\n");
}


// edit 1