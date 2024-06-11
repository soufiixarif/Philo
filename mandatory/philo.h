
#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct s_data t_data;
typedef struct s_forks
{
	pthread_mutex_t	fork;
	int				id;
	struct s_forks	*next;
}t_fork;

typedef struct s_philo
{
	pthread_t		philo;
	int				id;
	int				last_meal;
	int				meals;
	pthread_mutex_t *r_fork;
	pthread_mutex_t *l_fork;
	struct s_philo	 *next;
} t_philo;

struct s_data
{
	t_philo			*philos;
	t_fork			*forks;
	pthread_t		*mentor;
	long			philo_num;
	long			dying_time;
	long			eating_time;
	long			sleeping_time;
	long			meals;
	long			start_sim;
	bool			dead_flag;
	pthread_mutex_t	dead;
	pthread_mutex_t	lock;
};

//philo----------------------------------------------
void    parcing_data(int ac, char **av, t_data *ph);
int     checkvalidity(char *s);
void	start_simulation(t_data *ph);
void	simulation(t_data *ph);
size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);
void	join_philos(t_data *ph);
void	philo_creator(t_data *ph);
void	fork_creator(t_data *ph);
void	data_init(t_data *ph);
void	mentor_routine(t_data *ph);
void	sleep_odd_philo(t_data *ph);
void	eating_time(t_data *ph);
bool	is_dead(t_data *ph);

//libft----------------------------------------------
long	ft_atoi(char *str);
size_t	ft_strlen(char *s);

#endif;