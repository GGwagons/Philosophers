/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:01:28 by ggwagons          #+#    #+#             */
/*   Updated: 2024/05/19 20:33:08 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write (fd, &s[i], 1);
		i++;
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (((s1[i] != '\0') || (s2[i] != '\0')))
	{
		if (s1[i] != s2[i])
			return ((int)(unsigned char)s1[i] - (int)(unsigned char)s2[i]);
		i++;
	}
	return ((int)(unsigned char)s1[i] - (int)(unsigned char)s2[i]);
}

int	ft_atoi(const char *nptr)
{
	unsigned long long	result;
	int					sign;
	int					i;

	result = 0;
	i = 0;
	sign = 1;
	if (nptr == NULL)
		return (0);
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	while (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = sign * -1;
		i++;
		if ((nptr[i] == '+') || (nptr[i] == '-'))
			return (0);
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - '0';
		i++;
	}
	return (result * sign);
}

static int	ft_length(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len = len + 1;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int					len;
	int					i;
	char				*str;
	long long int		num;

	len = ft_length(n);
	i = len - 1;
	num = n;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	else if (num < 0)
	{
		str[0] = '-';
		num = num * -1;
	}
	else if (num == 0)
		str[0] = '0';
	while (num != 0)
	{
		str[i--] = (num % 10) + '0';
		num = num / 10;
	}
	str[len] = '\0';
	return (str);
}
