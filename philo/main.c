/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdanchal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:27:28 by kdanchal          #+#    #+#             */
/*   Updated: 2024/09/22 16:27:30 by kdanchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	*ft_god_look_full(t_data *data)
{
	int	i;

	if (data->number_of_must_eat < 1)
		return (NULL);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (data->human_qty_full == data->number_of_philosophers)
		{
			pthread_mutex_lock(&data->mutex_control);
			data->end_dinner = 1;
			pthread_mutex_unlock(&data->mutex_control);
			return ("all_full");
		}
		i++;
	}
	return (NULL);
}

char	*ft_god_look_die(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->mutex_control);
		data->philo[i].time_wait = ft_time_now_ms()
			- data->philo[i].time_last_meal;
		if ((data->philo[i].time_wait) >= (data->time_to_die))
		{
			printf("%lu	%d died\n", ft_time_now_ms()
				- data->time_start, data->philo[i].order);
			data->end_dinner = 1;
			pthread_mutex_unlock(&data->mutex_control);
			return ("die");
		}
		pthread_mutex_unlock(&data->mutex_control);
		i++;
	}
	return (NULL);
}

char	*ft_check_end_dinner(t_data *data)
{
	if (ft_god_look_die(data))
		return ("die");
	if (ft_god_look_full(data))
		return ("full");
	return (NULL);
}

int	ft_error_exit(char *s, int exit_type)
{
	ft_putstr_fd(s, 2);
	return (exit_type);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		i;

	if (ft_check_input(argc, argv))
		return (ft_error_exit("Error input", 1));
	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_error_exit("Error maloc: Cannot allocate memory", 1));
	ft_memset(data, 0, sizeof(t_data));
	if (ft_set(data, argv))
		return (ft_error_exit("Error input", 1));
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_create(&data->philo[i].th, NULL, ft_routine, &data->philo[i]);
		i++;
	}
	while (1)
	{
		if (ft_check_end_dinner(data))
			break ;
	}
	ft_join_and_free(data);
	return (0);
}
