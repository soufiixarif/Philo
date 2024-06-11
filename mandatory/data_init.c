#include "philo.h"

void	fork_creator(t_data *ph)
{
    t_fork *forks;
	int i;

    forks = ph->forks;
	if (!forks) 
	{
		perror("Failed to allocate memory for forks");
		exit(EXIT_FAILURE);
	}
	i = 1;
	while (forks)
	{
		if (pthread_mutex_init(forks, NULL) != 0)
		{
			perror("Failed to initialize fork mutex");
			exit(EXIT_FAILURE);
		}
        forks->id = i;
        i++;
        forks = forks->next;
	}
}

void join_philos(t_data *ph)
{
    t_philo *philos;

    philos = ph->philos;
    while(philos)
    {
        pthread_join(philos->philo, NULL);
        philos = philos->next;
    }
}

void	philo_creator(t_data *ph)
{
	int i;
    t_philo *philos;
    t_fork  *forks;

    philos = ph->philos;
    forks = ph->forks;
	i = 1;
	while (philos) 
	{
		philos->id = i;
		philos->r_fork = &ph->forks;
		philos->l_fork = &ph->forks->next;
		if (pthread_create(&philos->philo, NULL, (void *)simulation, philos->philo) != 0)
		{
			perror("Failed to create thread");
			exit(EXIT_FAILURE);
		}
        i++;
        philos = philos->next;
	}
    ph->mentor = malloc(sizeof (pthread_t));
	pthread_create(&ph->mentor,NULL,(void *)mentor_routine,ph);
    join_philos(ph);
	pthread_join(ph->mentor,NULL);
}

void data_init(t_data *ph)
{
	ph->start_sim = 0;
	ph->dead_flag = false;
	ph->philos->id = 0;
	ph->philos->last_meal = 0;
	ph->philos->meals = 0;
    ph->philos = malloc(sizeof(t_philo) * ph->philo_num);
    ph->forks = malloc(ph->philo_num * sizeof(t_fork));
    fork_creator(ph);
	philo_creator(ph);
}
