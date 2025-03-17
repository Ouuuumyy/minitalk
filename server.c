/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 03:04:35 by oukadir           #+#    #+#             */
/*   Updated: 2025/03/17 03:35:51 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_byte = 0;

void	handle_sigusr(int sig)
{
	static int	bit_count;
	char		c;

	if (sig == SIGUSR1)
	{
		g_byte = (g_byte << 1) | 0;
		bit_count++;
	}
	else if (sig == SIGUSR2)
	{
		g_byte = (g_byte << 1) | 1;
		bit_count++;
	}
	if (bit_count == 8)
	{
		c = (char)g_byte;
		write(1, &c, 1);
		g_byte = 0;
		bit_count = 0;
	}
}

int	main(void)
{
	int	pid;

	signal(SIGUSR1, handle_sigusr);
	signal(SIGUSR2, handle_sigusr);
	pid = (int)getpid();
	ft_putstr("Server pid ");
	ft_putnbr(pid);
	ft_putstr("\n");
	while (1)
	{
		pause();
	}
	return (0);
}
