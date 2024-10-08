/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 00:37:01 by sarif             #+#    #+#             */
/*   Updated: 2024/10/08 20:44:16 by sarif            ###   ########.fr       */
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

typedef struct s_mtx
{
	pthread_mutex_t	mtx;
	bool			init;
}	t_mtx;

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
	t_mtx			protect;
}	t_philo;

struct s_data
{
	t_philo			*philos;
	pthread_t		mentor;
	t_mtx			*forks;
	long			philo_num;
	long			dying_time;
	long			eating_time;
	long			sleeping_time;
	long			meals;
	bool			dead_flag;
	t_mtx			print;
	t_mtx			lock;
	long			s_sim;
};

//philo----------------------------------------------
int		parcing_data(int ac, char **av, t_data *ph);
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
int		ft_mutex_init(t_mtx *mutex);
void	init_to_false(t_data *data);
void	mutex_unlock_norm(t_data *ph, t_philo *philo);

//libft----------------------------------------------
long	ft_atoi(char *str);
size_t	ft_strlen(char *s);

#endif