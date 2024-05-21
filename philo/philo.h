/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:48:38 by ggwagons          #+#    #+#             */
/*   Updated: 2024/05/20 14:33:59 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <ctype.h>
# include <pthread.h>

# define MAX_PHILO 500

typedef struct s_data
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_philo;
	pthread_mutex_t	print;
	size_t			time_to_sleep;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			num_of_philo;
	size_t			num_meals;
	size_t			philo_is_dead;
	size_t			start;
	size_t			finish_flag;
}			t_data;

typedef struct s_philo
{
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	philo_mutex;
	size_t			id;
	size_t			finished;
	size_t			last_meal;
	size_t			meals;
	size_t			okay;
	t_data			*data;
}			t_philo;

// UTILS.C
int		ft_strcmp(const char *s1, const char *s2);
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);
void	ft_putstr_fd(char *s, int fd);

// UTILS2.C
void	*monitoring_thread(void *p);
int		dead_flag(t_philo *philo);
int		check_all_finished(t_philo *philo);
int		check_any_dead(t_philo *philo);

// STEPS.C
void	*steps(void *p);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

// MAIN.C
int		ft_error(int argc, char **argv);
int		arg_check(int argc, char **argv);
int		arg_check2(int argc, char **argv);
void	init(t_data *data, char **argv);

// SLEEP.C
int		ft_sleep(size_t time, t_philo *philo);
size_t	get_timestamp(void);
void	ft_dead_msg(char *s, t_philo *philo, size_t i);
void	ft_message(char *s, t_philo *philo, size_t i);

// PHILO.C
void	philos_init(t_philo *philo, t_data *data);
void	ft_mutex_init(t_philo *philo, t_data *data);
void	ft_destroy(t_philo *philo, t_data *data);
int		ft_makethread(t_philo *philo, t_data *data);
int		thread_join(t_philo *philo, t_data *data, pthread_t *thread);

// ACTION.C
void	philo_eat(t_philo *philo);
void	acquire_forks(pthread_mutex_t *first_fork,
			pthread_mutex_t *second_fork, t_philo *philo);
void	release_forks(pthread_mutex_t *first_fork,
			pthread_mutex_t *second_fork);
void	update_meal_info(t_philo *philo);

#endif