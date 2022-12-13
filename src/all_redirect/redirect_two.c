#include "../../header/minishell.h"

static	int	ft_find(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (ft_strncmp(tmp[i], "<", 10) == 0)
			return (i);
		i++;
	}
	return (0);
}

static	void	ft_malloc_cat(char **tmp)
{
	char	**tab;
	int		nb;

	tab = malloc(sizeof(char) * 3);
	nb = ft_strlen2(tmp) - 1;
	tab[0] = tmp[0];
	tab[1] = tmp[nb];
	tab[2] = NULL;
	ft_exec(tab, NULL);
	free(tab);
}

static	void	ft_malloc_error(char **tmp, int nb)
{
	char	**tab;
	int		i;

	i = -1;
	tab = malloc(sizeof(char) * 2);
	while (++i < nb)
		tab[i] = tmp[i];
	if (access(tmp[i + 1], F_OK))
	{
		printf("cd: no such file or directory: %s\n", tmp[2]);
		free(tab);
		return ;
	}
	tab[i] = NULL;
	ft_exec(tab, NULL);
	free(tab);
}

void	ft_redirect_two(char **tmp, char **env, char *str)
{
	int	nb;

	(void)str;
	(void)env;
	nb = ft_find(tmp);
	if ((ft_strncmp(tmp[1], "<", MAX_SIZE + 4) == 0)
		&& (ft_strncmp(tmp[0], "cat", MAX_SIZE + 4) == 0))
		ft_malloc_cat(tmp);
	else if (ft_strncmp(tmp[nb], "<", MAX_SIZE + 4) == 0)
		ft_malloc_error(tmp, nb);
}
