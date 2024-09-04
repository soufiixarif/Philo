/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:14:40 by sarif             #+#    #+#             */
/*   Updated: 2024/08/30 20:16:10 by sarif            ###   ########.fr       */
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

typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_t		philo;
	t_data			*data;
	int				id;
	int				last_meal;
	int				meals;
	int				sleeptime;
	int				pid;
}	t_philo;

struct	s_data
{
	t_philo		*philos;
	pthread_t	*mentor;
	sem_t		*forks;
	long		philo_num;
	long		dying_time;
	long		eating_time;
	long		sleeping_time;
	long		meals;
	long		start_sim;
	int			stamp;
};

// time.c
size_t	get_time(void);
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