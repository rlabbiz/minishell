/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 11:44:47 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/05/14 20:01:33 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft/libft.h"
#include "minishell.h"

/**
 *	strappend - append @c to end of @str.					  
 *		@str: the string to add the @c in end of it.		  
 *		@c: the character to be added in end of @str.		  
 *		RETURN: return the new string contain the @str and @c,
 *			or return @str if no @c   						  
 **/
char *strappend(char *str, char c)
{
	char	*result;
	int		i;

	result = malloc(sizeof(char ) * ft_strlen(str) + 2);
	if (!result)
		return (NULL);
	if (!c)
		return (str);
	i = 0;
	while (str[i] != '\0')
	{
		result[i] = str[i];
		i++;
	}
	result[i] = c;
	i++;
	result[i] = '\0';
	free(str);
	return (result);
}

/**
 *	skip_esp_tab - skip the first espaces or tabs form @str.		   
 *		@str: the string to be skipt from it.						   
 *		RETURN: return the index of non-expace and non-tab in the @str,
 *			if no espaces or tabs in the beginning return 0.		   
 **/
int skip_esp_tab(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] == ' ')
		i++;
	return (i);
}

/**
 *	quotes_error - print erorr message and exit of program. 
 **/
void quotes_error(void)
{
	printf("minishell: missing the single or double quotes.\n");
	exit(1);
}

/**
 *	check_quotes - count the signle or double quotes in @input and return it.  
 *		@input: the string to be searche into for the single or double quotes. 
 *		RETURN: return how many single or double quotes contains in the @input,
 *			or return -1 if any single or double quotes dosen't close. 		   
 **/
int	check_quotes(char *input)
{
	int	i;
	int quotes;

	i = 0;
	quotes = 0;
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
		while (str[i] != '\0')
		{ 
			if (str[i] == '\'')
				return (0);
			if (str[i] == '\"')
				return (1);
			i++;
		}
	}
	else if (str[i] == '\"')
	{
		if (*quotes == 0)
			*quotes = DOUBLE_QUOTES;
		while (str[i] != '\0')
		{
			if (str[i] == '\"')
				return (0);
			if (str[i] == '\'')
				return (1);
			i++;
		}
	}
	return (1);
}

int check_cmd(char *old_cmd)
{
	char *new_cmd;
	int i;
	int j;
	int quotes;
	
	new_cmd = malloc(sizeof(char ) * ft_strlen(old_cmd) + 1);
	i = 0;
	j = 0;
	quotes = 0;
	while (old_cmd[i] == ' ' || old_cmd[i] == '\t')
		i++;
	if (!old_cmd[i])
		return (0);
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
	if (ft_strlen(new_cmd) == 0)
		return (0);
	printf("%s\n", new_cmd);
	return (1);
}

/**
 *	split_cmd - get the first value from input that contain the single or double quotes.
 *		@input: the string to extract the sub string from it.							
 *		@conv: pointer to t_conv struct set it value.									
 **/
char **split_cmd(char *input, t_list *list)
{
	char	**ptr;
	int		len;
	int		j;
	int		i;
	int		quotes;
	int		start;
	char 	*cmd;

	list = NULL;
	if (!input)
		return (NULL);
	len = get_cmd_len(input);
	ptr = (char **)malloc((len + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	if (check_quotes(input))
		quotes_error();
	j = 0;
	i = 0;
	quotes = 0;
	start = 0;
	while (input[i])
	{
		while (check_espace(input[i], quotes))
			i++;
		start = i;
		while (input[i] != '\0' && !check_espace(input[i], quotes) && !check_if_quotes(input, i, &quotes))
			i++;
		if (input[i] == '\'' || input[i] == '\"')
			i++;
		cmd = ft_substr(input, start, i + 1 - start);
		if (check_cmd(cmd))
			ft_lstadd_back(&list, ft_lstnew(ft_substr(input, start, i + 1 - start)));
		// ptr[j] = ft_substr(input, start, i + 1 - start);
		// printf("%s\n", ptr[j]);
		j++;
	}
	while (list != NULL)
	{
		printf(" 1 ==== > %s\n", list->content);
		list = list->next;
	}
	ptr[j] = NULL;
	return (ptr);
}

