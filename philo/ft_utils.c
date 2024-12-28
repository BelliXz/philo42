/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdanchal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:37:18 by kdanchal          #+#    #+#             */
/*   Updated: 2024/02/14 14:03:13 by kdanchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	ft_atoi(const char *str)
{
	long long	n;
	int			pos;

	n = 0;
	pos = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			pos *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		n = n * 10 + (*str - '0');
		str++;
	}
	return (pos * n);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;
	unsigned char	ch;

	p = (unsigned char *)b;
	ch = c;
	while (len--)
	{
		*p = ch;
		p++;
	}
	return (b);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

size_t	ft_time_now_ms(void)
{
	struct timeval	t;
	size_t			time_now_ms;

	gettimeofday(&t, NULL);
	time_now_ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (time_now_ms);
}

void	ft_usleep(size_t time)
{
	size_t	start;

	start = ft_time_now_ms();
	while (ft_time_now_ms() < (start + time))
		usleep(59);
}
