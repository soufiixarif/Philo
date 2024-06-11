#include "philo.h"

void sleep_odd_philo(t_data *ph)
{
	if (ph->philos->id % 2 != 0)
		ft_usleep(ph->eating_time);
}

void	simulation(t_data *ph)
{
	sleep_odd_philo(ph);

	while(!is_dead(ph))
	{
		eating_time(ph);
		sleeping_time(ph);
		
	}
	
}