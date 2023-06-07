/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 11:44:47 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/07 20:18:22 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft/libft.h"
#include "../minishell.h"

/**
 *	quotes_error - print erorr message and exit of program. 
 **/
void quotes_error(int type)
{
	if (type)
		printf("minishell: missing the single or double quotes.\n");
	else
		printf("minishell: : command not found\n");
	exit(1);
}

/**
 *	check_quotes - count the signle or double quotes in @input and return it.  
 *		@input: the string to be searched within either single or double quotes. 
 *		RETURN: return how many single or double quotes contained within the @input,
 *			or return -1 if any single or double quotes don't close. 		   
 **/
int	check_quotes(char *input)
{
	int	i;
	int quotes;

	i = 0;
	quotes = 0;
	while (input[i] != '\0' && (input[i] == ' ' || input[i] == '\t'))
		i++;
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
		{
			if (quotes == SINGLE_QUOTES)
				quotes = 0;
			else if (quotes == 0)
				quotes = SINGLE_QUOTES;
		}
		else if (input[i] == '\"')
		{
			if (quotes == DOUBLE_QUOTES)
				quotes = 0;
			else if (quotes == 0)
				quotes = DOUBLE_QUOTES;
		}
		i++;
	}
	if (quotes == 0)
		return (0);
	printf("minishell: missing the single or double quotes.\n");
	return (1);
}

/**
 *	get_cmd_len - counter the len of arguments in @input and return it.
 *		@input: the stirng to be counter how many arguments contains.
 *		RETURN: return the len of arguments.
 * **/
int get_cmd_len(char *input)
{
	int	i;
	int	len;
	int	quotes;

	i = 0;
	len = 0;
	quotes = 0;
	while ((input[i] == ' ' || input[i] == '\t') && input[i] != '\0')
		i++;
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
		{
			if (quotes == SINGLE_QUOTES)
			{
				quotes = 0;
				if (input[i + 1] == '\0' || input[i + 1] == ' ' || input[i + 1] == '\t')
					len++;
			}
			else if (quotes == 0)
			{
				quotes = SINGLE_QUOTES;
				if (i > 0 && (input[i - 1] != ' ' || input[i - 1] != '\t'))
					len--;
			}
		
		}
		else if (input[i] == '\"')
		{
			if (quotes == DOUBLE_QUOTES)
				quotes = 0;
			else if (quotes == 0)
			{
				quotes = DOUBLE_QUOTES;
				if (i > 0 && (input[i - 1] != ' ' || input[i - 1] != '\t'))
					len--;
			}
		}
		else if (quotes == 0 && input[i] != ' ' && input[i] != '\t' && input[i] != '\'' && input[i] != '\"' && (input[i + 1] == '\'' || input[i + 1] == '\"' || input[i + 1] == '\0' || input[i + 1] == ' ' || input[i + 1] == '\t'))
			len++;
		i++;
	}
	return (len);
}

int check_if_quotes(char *str, int i, int *quotes)
{
	if (*quotes != 0)
	{
		if (str[i] == '\'' && *quotes == SINGLE_QUOTES)
		{
			*quotes = 0;
			if (str[i + 1] == '\0' || str[i + 1] == ' ' || str[i + 1] == '\t')
				return (1);
		}
		else if (str[i] == '\"' && *quotes == DOUBLE_QUOTES)
		{
			*quotes = 0;
			if (str[i + 1] == '\0' || str[i + 1] == ' ' || str[i + 1] == '\t')
				return (1);
		}
	}
	else if (*quotes == 0)
	{
		if (str[i] == '\'')
			*quotes = SINGLE_QUOTES;
		else if (str[i] == '\"')
			*quotes = DOUBLE_QUOTES;
	}
	return (0);
}

int check_espace(char c, int quotes)
{
	if (c != '\0' && quotes == 0 && (c == ' ' || c == '\t'))
		return (1);
	return (0);
}

int find_quotes(char *str, int i, int *quotes)
{
	if (str[i] == '\'')
	{
		if (*quotes == 0)
			*quotes = SINGLE_QUOTES;
		else if (*quotes == SINGLE_QUOTES)
		{
			*quotes = 0;
			return (0);
		}
		else if (*quotes == DOUBLE_QUOTES)
			return (1);
		while (str[i++] != '\0')
		{
			if (str[i] == '\'' && *quotes == SINGLE_QUOTES)
				return (0);
		}
	}
	else if (str[i] == '\"')
	{
		if (*quotes == 0)
			*quotes = DOUBLE_QUOTES;
		else if (*quotes == DOUBLE_QUOTES)
		{
			*quotes = 0;
			return (0);
		}
		while (str[i++] != '\0')
		{
			if (str[i] == '\"' && *quotes == DOUBLE_QUOTES)
				return (0);
		}
	}
	return (1);
}

t_list *get_expantion(char *str)
{
	int		quotes;
	int		i;
	int		start;
	t_list *lst;
	quotes = 0;
	i = 0;
	while (str[i])
	{
		start = i;
		while (str[i] && find_quotes(str, i, &quotes) && (str[i] != '$' || quotes == SINGLE_QUOTES))
			i++;
		if (i > start)
		{
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, start, i - start)));
			printf("%s\n%d\n", ft_substr(str, start, i - start), i);
		}
		
	}
	exit(1);
	return (lst);
}

char *check_cmd_and_expand(char *old_cmd)
{
	char	*new_cmd = NULL;
	t_list *lst;
	
	lst = get_expantion(old_cmd);
	return (new_cmd);
}

char *check_cmd(char *old_cmd)
{
	char *new_cmd;
	int i;
	int j;
	int quotes;
	
	new_cmd = malloc(sizeof(char ) * ft_strlen(old_cmd) + 1);
	i = 0;
	j = 0;
	quotes = 0;
	// while (old_cmd[i] == ' ' || old_cmd[i] == '\t')
	// 	i++;
	// if (!old_cmd[i])
	// {
	// 	free(old_cmd);
	// 	return (0);
	// }
	while (old_cmd[i] != '\0')
	{
		if (find_quotes(old_cmd, i, &quotes) == 1)
		{
			new_cmd[j] = old_cmd[i];
			j++;
		}
		i++;
	}
	new_cmd[j] = '\0';
	return (new_cmd);
}

int check_if_redirections(char *c, int i, int quotes)
{
	if (quotes == 0 && (c[i] == 60 || c[i] == 62 || c[i] == '|')) 
		return (1);
	return (0);
}

// void split_redirection(char *input, int i, t_list *list)
// {
	
// }


/*

if (>> or <<) ft_strncmp(input, ">>", 2) == 0
	len = 2;
else if (| or > or <) *input == '|'
	len = 1;
else
	len = get_lenght(input);
ft_substr(input, 0, len);
input =+ len;


get_length
{
	len = 0;
	if (input[len] == '|', '>', '<', ' ', '\t')ft_strchr("|>< \t", input[len])
		return (len);
	else if (input[len] == '\'', '"')
	{
		c = input[len]
		len++;
		while (input[len] && input[len] != c)
			len++;
		if (input[len] == 0)
			return (len);
		len++;
	}
	else
		len++
}
*/


/**
 *	split_cmd - get the first value from input that contain the single or double quotes.
 *		@input: the string to extract the sub string from it.							
 *		@conv: pointer to t_conv struct set it value.									
 **/
void split_cmd(char *input, t_list **list)
{
	// int		j;
	int		i;
	int		quotes;
	int		start;
	char 	*cmd;
	char	c;

	if (!input)
		return ;
	// if (check_quotes(input) == 1)
	// 	quotes_error(1);
	// else if (check_quotes(input) == -1)
	// 	quotes_error(0);
	// j = 0;
	i = 0;
	quotes = 0;
	start = 0;
	while (input[i] != '\0')
	{
		while (check_espace(input[i], quotes))
			i++;
		if (!input[i])
			break ;
		start = i;
		while (input[i] != '\0' && !check_espace(input[i], quotes) && !check_if_quotes(input, i, &quotes) && !check_if_redirections(input, i, quotes))
			i++;
		if (input[i] == '\'' || input[i] == '\"')
			i++;
		cmd = ft_substr(input, start, i - start);
		if (cmd != NULL)
			ft_lstadd_back(list, ft_lstnew(cmd));
		if (ft_strchr("<>|", input[i]))
		{
			start = i;
			c = input[i];
			while (input[i] != '\0' && ft_strchr(&c, input[i]))
				i++;
			cmd = ft_substr(input, start, i - start);
			if (cmd != NULL)
				ft_lstadd_back(list, ft_lstnew(cmd));
		}
	}
}
