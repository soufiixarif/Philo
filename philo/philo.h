/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 00:37:01 by sarif             #+#    #+#             */
/*   Updated: 2024/09/27 20:45:05 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_t		philo;
	t_data			*data;
	int				id;
	long			last_meal;
	long			meals;
	long			sleeptime;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	protect;
}	t_philo;

struct s_data
{
	t_philo			*philos;
	pthread_t		mentor;
	pthread_mutex_t	*forks;
	long			philo_num;
	long			dying_time;
	long			eating_time;
	long			sleeping_time;
	long			meals;
	long			start_sim;
	bool			dead_flag;
	pthread_mutex_t	print;
	pthread_mutex_t	lock;
	long			stamp;
};

//philo----------------------------------------------
void	parcing_data(int ac, char **av, t_data *ph);
int		checkvalidity(char *s);
void	*simulation(t_philo *philo);
int		ft_usleep(size_t milliseconds);
int		join_philos(t_data *ph);
int		philo_creator(t_data *ph);
int		fork_creator(t_data *ph);
int		data_init(t_data *ph);
void	mentor_routine(t_data *ph);
void	eating_time(t_philo *philo);
void	sleeping_time(t_philo *philo);
long	get_time(void);
void	ft_printf(int i, t_data *data, int id);
bool	get_bool(t_data *data, bool *src);
int		mentor_creator(t_data *data);
void	ft_mutex_destroy(t_data *data, int i);
int		ft_mutex_init(pthread_mutex_t *mutex, t_data *data);

//libft----------------------------------------------
long	ft_atoi(char *str);
size_t	ft_strlen(char *s);

#endif