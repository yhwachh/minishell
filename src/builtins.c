#include "../header/minishell.h"

void	ft_unset(char **str, char **env)
{
	t_data	data;
	int		len;

	len = 0;
	while (env[++data.i2] && str[data.j2])
	{
		data.line = ft_split(env[data.i2], EGAL);
		len = ft_strlen(data.line[0]);
		data.i = ft_strlen(str[data.j2]);
		if ((ft_strncmp(str[data.j2], data.line[0], len) == 0)
			&& (ft_strncmp(str[data.j2], data.line[0], data.i) == 0))
		{
			if (str[data.j2 + 1])
				ft_free_line(data.line);
			data.j2++;
			data.i = data.i2 - 1;
			while (env[++data.i])
				env[data.i] = env[data.i + 1];
			env[data.i + 1] = NULL;
			data.i2 = -1;
		}
		else
			ft_free_line(data.line);
	}
	ft_free_line(data.line);
}

void	cd(char **line)
{
	char	*back;

	back = getenv("HOME");
	if (chdir(line[1]) == -1)
		printf("cd: no such file or directory: %s\n", line[1]);
	else if (line[1] == NULL)
		chdir(back);
	g_pid = 0;
}

void	pwd(char **tp)
{
	char	*line;

	if (tp[1])
	{
		printf("pwd: too many arguments\n");
		return ;
	}
	g_pid = 0;
	line = getcwd(0, 10000);
	printf("%s\n", line);
	free(line);
}


// edit 1