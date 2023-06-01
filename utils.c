/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:52:26 by ael-amin          #+#    #+#             */
/*   Updated: 2023/05/31 22:54:41 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    int fd = open("test.txt", O_WRONLY | O_TRUNC);
    write(fd, "rida", 4);
}