/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:06:17 by miturk            #+#    #+#             */
/*   Updated: 2024/05/19 21:02:24 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(int argc, char **argv)
{
	int		j;
	char	*str;

	j = 1;
	while (j < argc)
	{
		str = ft_itoa(ft_atoi(argv[j]));
		if (!str)
			return (0);
		if (ft_strcmp(str, argv[j]))
		{
			free(str);
			return (1);
		}
		free(str);
		j++;
	}
	return (0);
}

int	arg_check(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (ft_putstr_fd("Invalid num of args\n", 2), 1);
	if (argv[i] == NULL)
		return (ft_putstr_fd("There are no arguments\n", 2), 1);
	while (argv[i] != NULL )
	{
		if (ft_error(argc, argv) != 0)
			return (ft_putstr_fd("Invalid arguments\n", 2), 1);
		arg_check2(argc, argv);
		i++;
	}
	return (0);
}

int	arg_check2(int argc, char **argv)
{
	if (argc != 6 && argc != 5)
		return (ft_putstr_fd("Invalid num of args\n", 2), 1);
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > MAX_PHILO
		|| ft_error(argc, argv) != 0)
		exit (write(2, "Invalid number of philos\n", 26));
	if (ft_atoi (argv[2]) <= 0)
		return (write(2, "Wrong time to die\n", 19), 1);
	if (ft_atoi(argv[3]) <= 0)
		return (write(2, "Wrong time to eat\n", 19), 1);
	if (ft_atoi(argv[4]) <= 0 || ft_error(argc, argv) != 0)
		return (write(2, "Wrong time to sleep\n", 21), 1);
	if (argc == 6)
		if (ft_atoi(argv[5]) < 0 || ft_error(argc, argv) != 0)
			return (write(2, "Wrong amount of meals\n", 23), 1);
	return (0);
}

void	init(t_data *data, char **argv)
{
	data->philo_is_dead = 0;
	data->finish_flag = 0;
	data->num_of_philo = (size_t)ft_atoi(argv[1]);
	data->time_to_die = (size_t)ft_atoi(argv[2]);
	data->time_to_eat = (size_t)ft_atoi(argv[3]);
	data->time_to_sleep = (size_t)ft_atoi(argv[4]);
	if (argv[5] != NULL)
		data->num_meals = (size_t)ft_atoi(argv[5]);
	else
		data->num_meals = -1;
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	philo[MAX_PHILO];

	if (arg_check(argc, argv) == 1)
		return (1);
	else
	{
		data.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
				* (ft_atoi(argv[1])));
		if (data.forks == NULL)
			return (1);
		init(&data, argv);
		ft_mutex_init(philo, &data);
		philos_init(philo, &data);
		ft_makethread(philo, &data);
		ft_destroy(philo, &data);
		free(data.forks);
	}
	return (0);
}
