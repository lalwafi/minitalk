/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:59:54 by lalwafi           #+#    #+#             */
/*   Updated: 2024/07/08 22:55:25 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler_thing(int signal_received, siginfo_t *info, void *context)
{
	static char	bits = 0;
	static char	character = 0;

	(void) context;
	if (signal_received == SIGUSR1)
		character |= (1 << (7 - bits));
	bits++;
	if (bits == 8)
	{
		ft_putchar_fd(character, 1);
		if (character == '\0')
		{
			if (kill(info->si_pid, SIGUSR1) == -1)
				ft_printf("didnt send signal to client :(\n");
		}
		character = 0;
		bits = 0;
	}
}

int	main(void)
{
	struct sigaction	siga;

	ft_printf("\n********************************\n");
	ft_printf("* Hallo!! This is my server!!! *\n");
	ft_printf("* Server PID is \033[95m%d\033[0m          *\n", getpid());
	ft_printf("********************************\n");
	ft_printf("\n\033[4mMESSAGES!! :\033[0m\n");
	siga.sa_sigaction = &handler_thing;
	siga.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &siga, NULL);
	sigaction(SIGUSR2, &siga, NULL);
	while (1)
		usleep(350);
	return (0);
}
