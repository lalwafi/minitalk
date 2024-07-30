/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:12:17 by lalwafi           #+#    #+#             */
/*   Updated: 2024/07/08 22:22:21 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	send_it(int pid, char c)
{
	int	bits;
	int	checker;

	bits = 0;
	checker = 0;
	while (bits < 8)
	{
		if (c & 0b10000000)
			checker = kill(pid, SIGUSR1);
		else
			checker = kill(pid, SIGUSR2);
		if (checker == -1)
		{
			ft_printf("\033[31mThe signal didn't send 😢\033[0m\n");
			return (1);
			break ;
		}
		usleep(300);
		c = c << 1;
		bits++;
	}
	return (0);
}

int	check_arguments(int argument_count, char **argument_variables)
{
	int	i;

	i = 0;
	if (argument_count != 3)
	{
		ft_printf("\033[31mGotta have 3 arguments, write it like this;");
		ft_printf(" \"./client <Server PID> <string>\"\033[0m\n");
		return (0);
	}
	while (argument_variables[1][i])
	{
		if (!ft_isdigit(argument_variables[1][i]))
		{
			ft_printf("\033[31mWhy are there letters in your PID??\033[0m\n");
			return (0);
		}
		i++;
	}
	if (argument_variables[2][0] == '\0')
	{
		ft_printf("\033[31mEmpty string?? Write something maybe???\033[0m\n");
		return (0);
	}
	return (1);
}

int	main(int argument_count, char **argument_variables)
{
	int	pid;
	int	i;
	int	check;

	if (check_arguments(argument_count, argument_variables) == 0)
		return (0);
	i = 0;
	pid = ft_atoi(argument_variables[1]);
	if (pid <= 0 || pid >= INT_MAX)
	{
		ft_printf("\033[31mPID can't even be that number, ");
		ft_printf("just copy it from the server\033[0m\n");
		return (0);
	}
	while (argument_variables[2][i] && check == 0)
	{
		check = send_it(pid, argument_variables[2][i]);
		i++;
	}
	if (check == 0)
	{
		send_it(pid, '\n');
		send_it(pid, '\0');
	}
}
