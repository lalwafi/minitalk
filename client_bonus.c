/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:59:23 by lalwafi           #+#    #+#             */
/*   Updated: 2024/07/08 22:39:13 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	bonus_handler(int signal_received)
{
	if (signal_received == SIGUSR1)
		ft_printf("got the signal from server!\n");
	else
		perror(NULL);
}

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
	int					pid;
	int					i;
	struct sigaction	sigbonus;
	int					check;

	if (check_arguments(argument_count, argument_variables) == 0)
		return (0);
	argument_variables[2] = ft_strjoin(argument_variables[2], "\n");
	i = 0;
	check = 0;
	pid = ft_atoi(argument_variables[1]);
	if (pid <= 0 || pid >= INT_MAX)
	{
		ft_printf("\033[31mPID is wrong?? open ur eyes maybe???\033[0m\n");
		return (0);
	}
	sigbonus.sa_handler = &bonus_handler;
	sigaction(SIGUSR1, &sigbonus, NULL);
	check = send_it(pid, argument_variables[2][i]);
	while (argument_variables[2][++i] && check == 0)
		check = send_it(pid, argument_variables[2][i]);
	if (check == 0)
		send_it(pid, '\0');
}
