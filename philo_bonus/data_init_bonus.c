/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:14:50 by sarif             #+#    #+#             */
/*   Updated: 2024/09/16 21:57:08 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*get_philo_name(int id)
{
	char	*name;
	char	*id_n;
	int		i;
	int		j;

	i = -1;
	j = 0;
	id_n = ft_itoa(id);
	if (!id_n)
		return (NULL);
	name = malloc(ft_strlen("/philo_sem_name") + ft_strlen(id_n) + 1);
	if (!name)
		return (NULL);
	while ("/philo_sem_name"[++i])
		name[i] = "/philo_sem_name"[i];
	while (id_n[j])
		name[i++] = id_n[j++];
	name[i] = '\0';
	free(id_n);
	return (name);
}

void	data_init(t_data *data)
{
	unsigned int	i;
	char			*name;

	if (data->philo_num == 0 || data->meals == 0)
		return ;
	i = -1;
	data->philos = malloc(sizeof (t_philo) * data->philo_num);
	if (!data->philos)
		return ;
	while (++i < data->philo_num)
	{
		name = get_philo_name(i + 1);
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].meals = 0;
		data->philos[i].full = false;
		data->philos[i].philo_name = name;
		sem_unlink(name);
		data->philos[i].philo_sem = sem_open(name, O_CREAT | O_EXCL, 0644, 1);
		if (data->philos[i].philo_sem == SEM_FAILED)
		{
			perror("Failed to open semaphore");
			exit(EXIT_FAILURE);// to change it (clean code after exit)
		}
	}
	sem_unlink("/forks");
	sem_unlink("/ft_printf");
	data->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, data->philo_num);
	data->ft_printf = sem_open("/ft_printf", O_CREAT | O_EXCL, 0644, 1);
	if (data->forks == SEM_FAILED || data->ft_printf == SEM_FAILED)
	{
		perror("Failed to open semaphore");
		exit(EXIT_FAILURE);// to change it (clean code after exit)
	}
	start_simulation(data);
}
