/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-amin <ael-amin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:24:07 by ael-amin          #+#    #+#             */
/*   Updated: 2023/06/06 15:56:19 by ael-amin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void routine_fils(pid_t pid, int *nb)
{
	printf("fils : coucou! je suis le file. Pid recu de fork = %d\n", pid);
	printf("file : le nombre est : %d\n", *nb);
}

// Routine du processus père :
void	routine_pere(pid_t pid, int *nb)
{
	printf("Pere : Je suis le pere. PID recu de fork = %d\n", pid);
	printf("Pere : Le nombre est %d\n", *nb);
	*nb *= 2;
	printf("Pere : Le nombre modifie est %d\n", *nb);
}

int	main(void)
{
	pid_t	pid; // Stocke le retour de fork
	int	nb;  // Stocke un entier

	nb = 42;
	printf("Avant fork, le nombre est %d\n", nb);
	pid = fork(); // Création du processus fils
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0) // Retour de fork est 0, on est dans le fils
		routine_fils(pid, &nb);
	else if (pid > 0) // Retour de fork > 0, on est dans le père
		routine_pere(pid, &nb);
	return (EXIT_SUCCESS);
}
