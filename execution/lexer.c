/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:20:33 by ael-amin          #+#    #+#             */
/*   Updated: 2023/06/13 19:40:23 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
char **expand(char **args)
    while (args[i])
        str = args[i]
        if (!str[j] && !*str)
            break ;
        start = j;
        if (str[j] != '$')
        {
            while (str[j] && str[j] != '$')
                j++;
            ft_lst(ft_sub(str, start, j));
            str = str + j;  
        }
        else
        {
            j++;
            while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
                j++;
            name = ft_sub(str, 0, j);
            env = get_env(name)
            if (env)
                ft_lst(env)
        }
*/

