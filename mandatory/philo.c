
#include "philo.h"

void mentor_routine(t_data *ph)
{
	t_philo *philo;
	int		cur_time;

	while (1)
	{
		philo = ph->philos;
		while(philo)
		{
			pthread_mutex_lock(&ph->lock);
			cur_time = get_current_time();
			if(cur_time - philo->last_meal > ph->dying_time)
			{
				pthread_mutex_lock(&ph->dead);
				ph->dead_flag = true;
				pthread_mutex_unlock(&ph->dead);
			}
			philo = philo->next;
		}
	}
}

void	start_simulation(t_data *ph)
{
	data_init(ph);
	simulation(ph);
}

int	main(int ac, char **av)
{
	t_data *ph;

	ph = malloc(sizeof(t_data));
	if (ac == 5 || ac == 6)
	{
		parcing_data(ac, av, ph);
		start_simulation(ph);
	}
	else
		printf("args error\n");
	free(ph);
	return (0);	
}