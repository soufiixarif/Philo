/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:21:41 by sarif             #+#    #+#             */
/*   Updated: 2024/05/21 12:12:31 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	simulation(t_data *ph)
{
	pthread_mutex_t *forks;
	int i;

	i = 0;
	forks = malloc(ph->philo_num *(sizeof (pthread_mutex_t)));
	while (i < ph->philo_num)
	{
		if (i % 2 == 0)
			usleep(1e4);
		else
		{	
			pthread_mutex_lock(forks);
			printf("philosopher %d eating ...\n",i);
			usleep(ph->eating_time);
			pthread_mutex_unlock(forks);
		}
		i++;
	}
	
	free(forks);
}
void	start_simulation(t_data *ph)
{
	pthread_t *philosophers;
	int i;

	i = 0;
	philosophers = malloc(ph->philo_num *(sizeof (pthread_t)));
	while (i < ph->philo_num)
		pthread_create(&philosophers[i++], NULL, (void *)simulation, NULL);
	i = 0;
	while (i < ph->philo_num)
		pthread_join(philosophers[i++], NULL);
	free(philosophers);
}
int	main(int ac, char **av)
{
	t_data *ph;

	ph = malloc(sizeof(t_data));
	if (!ph)
		return (1);
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