#include "../../header/minishell.h"

char	*bultin_1(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char) * 100);
	while (str[i] != '>')
	{
		tmp[i] = str[i];
		i++;
	}
	if (tmp[i] == ' ')
		i--;
	tmp[i] = '\0';
	return (tmp);
}

void	ft_redirection(char **tmp, char **env, char *str)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (ft_strncmp(tmp[i], ">", 10) == 0)
			ft_redirection_1(tmp, env, str);
		else if (ft_strncmp(tmp[i], "<", 10) == 0)
			ft_redirection_2(tmp, env, str);
		else if (ft_strncmp(tmp[i], ">>", 10) == 0)
			ft_redirection_3(tmp, env, str);
		else if (ft_strncmp(tmp[i], "<<", 10) == 0)
			ft_redirection_4(tmp, env, str);
		i++;
	}
}
