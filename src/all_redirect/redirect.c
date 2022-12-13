#include "../../header/minishell.h"

char	*malloc_and_chr(char *line)
{
	char	*tp;
	int		i;

	i = 0;
	tp = NULL;
	tp = malloc(sizeof(char) * 1000);
	if (!tp)
		return (NULL);
	while (line[i] != RDCTION_D)
	{
		tp[i] = line[i];
		i++;
	}
	if (tp[i] == SPACE_N)
		i--;
	tp[i] = END;
	return (tp);
}

void	ft_redirect(char **tp, char **env, char *line)
{
	int	i;

	i = 0;
	while (tp[i])
	{
		if (ft_strncmp(tp[i], ">", MAX_SIZE + 4) == 0)
			ft_redirect_one(tp, env, line);
		else if (ft_strncmp(tp[i], "<", MAX_SIZE + 4) == 0)
			ft_redirect_two(tp, env, line);
		else if (ft_strncmp(tp[i], ">>", MAX_SIZE + 4) == 0)
			ft_redirect_tree(tp, env, line);
		else if (ft_strncmp(tp[i], "<<", MAX_SIZE + 4) == 0)
			ft_redirect_four(tp, env, line);
		i++;
	}
}
