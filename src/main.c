#include "../header/minishell.h"

int	ft_init_and_malloc(t_data *data)
{
	data = malloc(sizeof(t_data));

	if (!data)
		return (0);
	data->tp = NULL;
	data->line = NULL;
	data->i2 = -1;
	data->j2 = 1;
	data->i = 0;
	data->j = 0;
	return (0);
}

void	signal_handler(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", 1);
	//rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_erreur(int signum)
{
	if (signum == SIGSEGV)
	{
		printf("Erreur\n");
		exit(0);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data		*data;
	char		*line;

	(void)argc;
	(void)argv;
	data = NULL;
	ft_init_and_malloc(data);
	signal(SIGSEGV, ft_erreur);
	signal(SIGINT, signal_handler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (68)
	{
		line = readline("\001\033[1;34m\002minishell -_-' ▸ \001\033[0;0m\002");
		if (!line)
		{
			printf("minishell: exit ");
			return (0);
		}
		add_history(line);
		if (*line)
			ft_tram(line, env); 
		free(line);
	}
	return (0);
}


// edite 1