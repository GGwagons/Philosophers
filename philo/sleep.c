/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:56:58 by ggwagons          #+#    #+#             */
/*   Updated: 2024/05/20 14:38:16 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_sleep(size_t time, t_philo *philo)
{
	struct timeval	start;
	struct timeval	now;
	size_t			elapsed;

	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&now, NULL);
		elapsed = (now.tv_sec - start.tv_sec) * 1000
			+ (now.tv_usec - start.tv_usec) / 1000;
		pthread_mutex_lock(&philo->data->dead_philo);
		if (elapsed >= time || philo->data->philo_is_dead != 0)
		{
			pthread_mutex_unlock(&philo->data->dead_philo);
			break ;
		}
		pthread_mutex_unlock(&philo->data->dead_philo);
		usleep(400);
	}
	return (0);
}

size_t	get_timestamp(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
	{
		ft_putstr_fd("Failed to get time\n", 2);
		return (0);
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_dead_msg(char *s, t_philo *philo, size_t i)
{
	size_t	time;

	if (philo->data->philo_is_dead == 1)
	{
		time = get_timestamp() - philo->data->start;
		printf("%zu\t%zu %s\n", time, i, s);
		return ;
	}
}

void	ft_message(char *s, t_philo *philo, size_t i)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->dead_philo);
	if (philo->data->philo_is_dead != 1)
	{
		time = get_timestamp() - philo->data->start;
		printf("%zu\t%zu %s\n", time, i, s);
		pthread_mutex_unlock(&philo->data->dead_philo);
		return ;
	}
	pthread_mutex_unlock(&philo->data->dead_philo);
}
