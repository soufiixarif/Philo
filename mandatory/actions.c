#include "philo.h"

void eating_time(t_data *ph)
{
	pthread_mutex_lock(&ph->philos->r_fork);
	pthread_mutex_lock(&ph->philos->l_fork);
    pthread_mutex_lock(&ph->lock);
	ph->philos->last_meal = get_current_time();
    pthread_mutex_unlolock(&ph->lock);
	(*ph->philos).meals += 1;
	printf("philo %d is eating\n",ph->philos->id);
	ft_usleep(ph->eating_time);
	pthread_mutex_unlock(&ph->philos->r_fork);
	pthread_mutex_unlock(&ph->philos->l_fork);
}

void sleeping_time(t_data *ph)
{
	printf("philo %d is sleeping\n",ph->philos->id);
	ft_usleep(ph->sleeping_time);

}