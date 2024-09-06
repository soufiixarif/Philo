/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:14:40 by sarif             #+#    #+#             */
/*   Updated: 2024/09/06 14:27:02 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_t		philo;
	t_data			*data;
	int				id;
	size_t			last_meal;
	int				meals;
	unsigned long	sleeptime;
	int				pid;
}	t_philo;

struct	s_data
{
	t_philo				*philos;
	pthread_t			*mentor;
	sem_t				*forks;
	unsigned long		philo_num;
	unsigned long		dying_time;
	unsigned long		eating_time;
	unsigned long		sleeping_time;
	int					meals;
	size_t				stamp;
};

// time.c
size_t	ft_get_time(void);
int		ft_usleep(size_t milliseconds);

//philo
void	mentor_routine(t_philo	*philo);
void	start_simulation(t_data *data);
void	simulation(t_philo *philo);
void	data_init(t_data *data);
void	parcing_data(int ac, char **av, t_data *data);

//libft
size_t	ft_strlen(char *s);
long	ft_atoi(char *str);

#endif