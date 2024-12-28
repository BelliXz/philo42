/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_and_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdanchal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:27:10 by kdanchal          #+#    #+#             */
/*   Updated: 2024/09/22 16:27:12 by kdanchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_join_and_free(t_data *data)
{
	int	i;

	(void)i;
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(data->philo[i].th, NULL);
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->mutex_fork[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mutex_control);
	free(data->mutex_fork);
	free(data->philo);
	free(data);
}

int	ft_set_2(t_data *data)
{
	int	i;

	data->mutex_fork = malloc(sizeof(pthread_mutex_t)
			* data->number_of_philosophers);
	if (!data->mutex_fork)
		return (-1);
	i = 0;
	while (i < data->number_of_philosophers)
		pthread_mutex_init(&data->mutex_fork[i++], NULL);
	pthread_mutex_init(&data->mutex_control, NULL);
	data->philo = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->philo)
		return (-1);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philo[i].order = i + 1;
		data->philo[i].fork_left = i;
		data->philo[i].fork_right = (i + 1) % data->number_of_philosophers;
		data->philo[i].time_last_meal = ft_time_now_ms();
		data->philo[i].number_of_eat_now = 0;
		data->philo[i].one_full = 0;
		data->philo[i++].data = data;
	}
	return (0);
}

int	ft_set(t_data *data, char **argv)
{
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->number_of_must_eat = 0;
	if (argv[5])
		data->number_of_must_eat = ft_atoi(argv[5]);
	data->time_start = ft_time_now_ms();
	// data->human_all_full = 0;
	data->human_qty_full = 0;
	if (data->number_of_philosophers < 1 || data->time_to_die < 60
		|| data->time_to_eat < 60 || data->time_to_sleep < 60
		|| data->number_of_must_eat < 0)
	{
		return (-1);
	}
	if (ft_set_2(data))
		return (-1);
	return (0);
}

char	*ft_check_input(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc < 5 || 6 < argc)
		return ("Error many argc");
	if (argv[5])
	{
		if (argv[5][0] == '0')
			return ("Error quantity meal = 0");
	}
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return ("Error not number");
			j++;
		}
		i++;
	}
	return (NULL);
}

// void	ft_print_status(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->data->mutex_control);
// 	printf(GREEN);
// 	printf("			(121 set.c) philo->order 	= %d\n", philo->order);
// 	printf("			(122 set.c) time_last_meal 	= %zu\n",
// 		philo->time_last_meal - philo->data->time_start);
// 	printf("			(124 set.c) philo(%d)->nb_eat_now	= %d\n\n",
// 		philo->order, philo->number_of_eat_now);
// 	printf(RESET);
// 	pthread_mutex_unlock(&philo->data->mutex_control);
// }
