#include "philo.h"

void eating_time(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	ft_printf(1,philo->data,philo->id);
	if (philo->data->philo_num > 1)
	{
		pthread_mutex_lock(philo->l_fork);
		ft_printf(1,philo->data,philo->id);
		pthread_mutex_lock(&philo->protect);
		philo->last_meal = get_current_time();
		pthread_mutex_unlock(&philo->protect);
		(*philo).meals += 1;
		ft_printf(2,philo->data,philo->id);
	}
	ft_usleep(philo->data->eating_time);
	// printf("philo %d is eating\n",philo->id);
	pthread_mutex_unlock(philo->r_fork);
	if (philo->data->philo_num > 1)
		pthread_mutex_unlock(philo->l_fork);
}

void sleeping_time(t_philo *philo)
{
	// printf("%lu %d is sleeping\n",get_current_time() -  philo->data->stamp,philo->id);
	if (philo->data->philo_num == 1)
		return ;
	ft_printf(3,philo->data,philo->id);
	ft_usleep(philo->sleeptime);
}

void ft_printf(int i, t_data *data, int id)
{
	pthread_mutex_lock(&data->print);
	if (i == 1 && !get_bool(data, &data->dead_flag))
		printf("%lu\t%d has taken a fork\n",get_current_time() - data->stamp, id);
	if (i == 2 && !get_bool(data, &data->dead_flag) && data->philo_num != 1)
		printf("%lu\t%d is eating\n",get_current_time() - data->stamp, id);
	if (i == 3 && !get_bool(data, &data->dead_flag) && data->philo_num != 1)
		printf("%lu\t%d is sleeping\n",get_current_time() - data->stamp, id);
	if (i == 4 && !get_bool(data, &data->dead_flag) && data->philo_num != 1)
		printf("%lu\t%d is thinking\n",get_current_time() - data->stamp, id);
	pthread_mutex_unlock(&data->print);
}