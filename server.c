/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 03:04:35 by oukadir           #+#    #+#             */
/*   Updated: 2025/03/20 01:52:58 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static	void	print_char(volatile sig_atomic_t *g_byte, int *bit_count)
{
	char	c;

	c = (char)(*g_byte);
	write(1, &c, 1);
	c = 0;
	*g_byte = 0;
	*bit_count = 0;
}

void	handle_sigusr(int sig, siginfo_t *info, void *context)
{
	static int						bit_count;
	static int						client_pid = 0;
	static volatile sig_atomic_t	g_byte = 0;

	(void)context;
	if (client_pid != info->si_pid)
	{
		bit_count = 0;
		g_byte = 0;
	}
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
		print_char(&g_byte, &bit_count);
	client_pid = info->si_pid;
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	sa.sa_sigaction = handle_sigusr;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
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
