#include "../header/minishell.h"

int	nbr_quotes(char *line, int nbr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (nbr == 1)
	{
		while (line[i])
		{
			if (line[i] == ONE_QUOTES)
				j++;
			i++;
		}
	}
	if (nbr == 2)
	{
		while (line[i])
		{
			if (line[i] == TWO_QUOTES)
				j++;
			i++;
		}
	}
	return (j);
}

int	ft_quote(char *line)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (line[i])
	{
		if (line[i] == TWO_QUOTES || line[i] == ONE_QUOTES)
		{
			line[i++] = SPACE_N;
			while (line[i] != TWO_QUOTES && line[i] != ONE_QUOTES)
			{
				if (line[i] == SPACE_N)
					line[i] = (char)688;
				i++;
			}
			if (line[i] == TWO_QUOTES || line[i] == ONE_QUOTES)
				line[i] = SPACE_N;
			nbr = 2;
		}
		i++;
	}
	return (nbr);
}

void	delet_quote(char **line)
{
	int	i;
	int	j;

	j = 0;
	while (line[j])
	{
		i = 0;
		while (line[j][i])
		{
			if (line[j][i] == (char)688)
				line[j][i] = SPACE_N;
			i++;
		}
		j++;
	}
}


char	**parsing(char *line)
{
	char	**tmp;
	int		nbr;

	tmp = NULL;
	nbr = 0;
	if (!(nbr_quotes(line, 1) % 2 == 0))
		return (NULL);
	if (!(nbr_quotes(line, 2) % 2 == 0))
		return (NULL);
	nbr = ft_quote(line);
	if (nbr)
		tmp = ft_split(line, SPACE_N);
	if (nbr > 0)
		delet_quote(tmp);
	else
		tmp = ft_split(line, SPACE_N);
	return (tmp);
}

// edite 1
