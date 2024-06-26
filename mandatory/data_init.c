#include "philo.h"

void	fork_creator(t_data *ph)
{
	int i;

	i = -1;
	while (i < ph->philo_num)
	{
		if (pthread_mutex_init(&ph->forks[i], NULL) != 0)
		{
			perror("Failed to initialize fork mutex");
			exit(EXIT_FAILURE);
		}
        i++;
	}
}

void join_philos(t_data *ph)
{
	int i;

	i = 0;
    while(i < ph->philo_num)
    {
        pthread_join(ph->philos[i].philo, NULL);
    }
}

void	philo_creator(t_data *ph)
{
	int 		i;
	pthread_t	mentor;

	i = -1;
	while (++i < ph->philo_num)
	{
		ph->philos[i].id = i + 1;
		ph->philos[i].last_meal = get_current_time();
		ph->philos[i].meals = 0;
		ph->philos[i].data = ph;
		ph->philos[i].sleeptime = ph->sleeping_time;
		ph->philos[i].r_fork = &ph->forks[i];
		ph->philos[i].l_fork = &ph->forks[(i + 1) % ph->philo_num];
		if (pthread_create(&ph->philos[i].philo, NULL, (void *)simulation, &ph->philos[i]) != 0)
		{
			perror("Failed to create thread");
			exit(EXIT_FAILURE);
		}
	}
    mentor = malloc(sizeof (pthread_t));
	pthread_create(&mentor,NULL,(void *)mentor_routine,ph);
	pthread_join(mentor,NULL);
    join_philos(ph);
}

void data_init(t_data *ph)
{
	ph->start_sim = 0;
	ph->dead_flag = false;
	if (ph->philo_num == 0 || ph->meals == 0)
		return ;
    ph->philos = malloc(sizeof(t_philo) * ph->philo_num);
    ph->forks = malloc(ph->philo_num * sizeof(pthread_mutex_t));
    fork_creator(ph);
	ph->stamp = get_current_time();
	philo_creator(ph);
}
