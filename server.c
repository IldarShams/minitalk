/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaegan <smaegan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:46:49 by ildar             #+#    #+#             */
/*   Updated: 2022/02/23 17:33:25 by smaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

struct s_char
{
	char	g_char;
	int		signals;
} g_jo;

void	sigusr1_serv_handler(int sig, siginfo_t *info, void *uncontext)
{
	usleep(30);
	g_jo.g_char = (g_jo.g_char << 1) + 0;
	g_jo.signals++;
	if (g_jo.signals >= 8)
	{	
		write(1, &g_jo.g_char, 1);
		g_jo.signals = 0;
		g_jo.g_char = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

void	sigusr2_serv_handler(int sig, siginfo_t *info, void *uncontext)
{
	usleep(30);
	g_jo.g_char = (g_jo.g_char << 1) + 1;
	g_jo.signals++;
	if (g_jo.signals >= 8)
	{	
		write(1, &g_jo.g_char, 1);
		g_jo.signals = 0;
		g_jo.g_char = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(int argc, char **argv)
{
	sigset_t				set;
	struct sigaction	sigusr1_act;
	struct sigaction	sigusr2_act;

	sigemptyset(&set);
	sigusr1_act.sa_flags = SA_SIGINFO;
	sigusr2_act.sa_flags = SA_SIGINFO;
	sigusr1_act.sa_sigaction = &sigusr1_serv_handler;
	sigusr2_act.sa_sigaction = &sigusr2_serv_handler;
	sigaction(SIGUSR1, &sigusr1_act, NULL);
	sigaction(SIGUSR2, &sigusr2_act, NULL);
	g_jo.g_char = 0;
	g_jo.signals = 0;
	printf("%d\n", getpid());
	while (1)
		;
}
