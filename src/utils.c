#include "../header/minishell.h"

int	ft_count(char **line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_strncmp(line[i], ">", MAX_SIZE + 1000) == 0 || ft_strncmp(line[i], "<", MAX_SIZE + 1000) == 0
			|| ft_strncmp(line[i], ">>", MAX_SIZE + 1000) == 0
			|| ft_strncmp(line[i], "<<", MAX_SIZE + 1000) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	*parsing_getenv(char **line, char *find)
{
	char	**tp;
	char	*sav;
	int		a;

	a = 0;
	tp = NULL;
	sav = NULL;
	while (line[a])
	{
		tp = ft_split(line[a], EGAL);
		if (ft_strncmp(tp[0], find, 1000) == 0)
		{	
			sav = tp[1];
			ft_free_getenv(tp);
			return (sav);
		}
		if (line[a + 1])
			ft_free_line(tp);
		a++;
	}
	free(tp);
	return (NULL);
}

int	check_nbr(char *line)
{
	int	i;
	
	i = 0;
	while (line[i] != EGAL)
	{
		if (line[i] >= ONE && line[i] <= NINE)
			return (0);
		i++;
	}
	return (1);
}

int	nbr_pipe(char *line)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (line[i])
	{
		if (line[i] == PIPE_N)
			nbr++;
		i++;
	}
	return (nbr);
}

int	ft_check_str(char *str)
{
	int		i;
	char	**tp;

	i = 0;
	tp = NULL;
	tp = ft_split(str, SPACE_N);
	while (tp[i])
	{
		if (check_quote(tp[i]) == 1)
		{
			ft_free_line(tp);
			return (1);
		}
		i++;
	}
	ft_free_line(tp);
	return (0);
}


// edit 1