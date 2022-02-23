/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaegan <smaegan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:06:09 by ildar             #+#    #+#             */
/*   Updated: 2022/02/23 17:33:20 by smaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

struct s_jo
{
	pid_t	pid;
	int		i;
	char	**argv;
} g_jo;

void	sigusr1_serv_handler(int sig)
{	
	usleep(30);
	signal(SIGUSR1, sigusr1_serv_handler);
	if (g_jo.argv[2][0] == '\0')
		return ;
	if (g_jo.i < 0)
	{
		g_jo.argv[2]++;
		if (g_jo.argv[2] == '\0')
			return ;
		g_jo.i = 7;
	}
	if (g_jo.argv[2][0] != '\0' && !((g_jo.argv[2][0] >> g_jo.i) & 1))
	{
		g_jo.i--;
		kill(g_jo.pid, SIGUSR1);
	}
	else if (g_jo.argv[2][0] != '\0')
	{
		g_jo.i--;
		kill(g_jo.pid, SIGUSR2);
	}
}

int	main(int argc, char **argv)
{
	if (argc < 3 || !argv[2])
		return (0);
	g_jo.i = 7;
	g_jo.argv = argv;
	signal(SIGUSR1, sigusr1_serv_handler);
	g_jo.pid = atoi(argv[1]);
	kill(getpid(), SIGUSR1);
	while (g_jo.argv[2][0])
		;
}
