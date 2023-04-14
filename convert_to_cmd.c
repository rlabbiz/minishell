/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 11:44:47 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/04/14 11:55:46 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
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
	int len;

	i = 0;
	quotes = 0;
	len = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
		{
			if (quotes == SINGLE_QUOTES)
			{
				len++;
				quotes = 0;
			}
			else if (quotes == 0)
				quotes = SINGLE_QUOTES;
		}
		else if (input[i] == '\"')
		{
			if (quotes == DOUBLE_QUOTES)
			{
				len++;
				quotes = 0;
			}
			else if (quotes == 0)
				quotes = DOUBLE_QUOTES;
		}
		i++;
	}
	if (quotes == 0)
		return (len);
	return (-1);
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
				quotes = SINGLE_QUOTES;
		}
		else if (input[i] == '\"')
		{
			if (quotes == DOUBLE_QUOTES)
			{
				quotes = 0;
				if (input[i + 1] == '\0' || input[i + 1] == ' ' || input[i + 1] == '\t')
					len++;
			}
			else if (quotes == 0)
				quotes = DOUBLE_QUOTES;
		}
		else if (quotes == 0 && input[i] != ' ' && input[i] != '\t' && input[i] != '\'' && input[i] != '\"' && (input[i + 1] == '\'' || input[i + 1] == '\"' || input[i + 1] == '\0' || input[i + 1] == ' ' || input[i + 1] == '\t'))
			len++;
		i++;
	}
	return (len);
}

/*char *get_sub(char *str, int start, int end)
{
	char	*sub;

}*/

/**
 *	split_cmd - get the first value from input that contain the single or double quotes.
 *		@input: the string to extract the sub string from it.							
 *		@conv: pointer to t_conv struct set it value.									
 **/
char **split_cmd(char *input)
{
	char	**split;
	int		start;
	int		end;
	int		i;
	int		len;
	int		quotes;
	
	len = get_cmd_len(input);
	split = malloc(sizeof(char *) * len + 1);
	if (!split)
		return (NULL);
	i = 0;
	start = 0;
	quotes = 0;
	end = 0;
	printf("%d\n", len);
	while (i < len)
	{
		while (quotes == 0 && input[start] != '\0' && (input[start] == ' ' || input[start] == '\t'))
			start++;
		end = start;
		while (input[end] != '\0' &&  !((quotes == SINGLE_QUOTES && input[end] == '\'') || (quotes == DOUBLE_QUOTES && input[end] == '\"') || (quotes == 0 && (input[end] == ' ' || input[end] == '\t'))))
		{
			if (input[end] == '\'')
			{
				if (quotes == 0)
					quotes = SINGLE_QUOTES;
				else if (quotes == SINGLE_QUOTES)
					quotes = 0;
			}
			else if (input[end] == '\"')
			{
				if (quotes == 0)
					quotes = DOUBLE_QUOTES;
				else if (quotes == DOUBLE_QUOTES)
					quotes = 0;
			}
			end++;
		}
		printf("the value of start is %d and the value of end is %d\n", start, end);
		split[i] = ft_substr(input, start, end);
		start = end + 1;
		i++;
	}
	split[i] = NULL;
	return (split);
}

/**
 *	conv_to_cmd - convert the @input to command and return it.   
 *		@input: the input readed from terminal of be converted. 
 *		RETURN: return the command extracted from @input.       
 **/
char *conv_to_cmd(char *input)
{
	char	*cmd;
	int		i;
	int 	quotes;
	//char	*sub;
	t_conv	conv;
	char	**split = split_cmd(input);
	 i = 0;
	 while (split[i] != NULL)
	 {
	 	printf("%s\n", split[i]);
		i++;
	 }
	
	conv.end = 0;
	conv.start = 0;
	// cmd = ft_strdup("\0");
	quotes = check_quotes(input);
	if (quotes == -1)
		quotes_error();
	i = get_cmd_len(input);
	cmd = NULL;
	// cmd = split_cmd(input, &conv);
/*	while (quotes > 0)
	{
		sub = split_cmd(input, &conv);
		cmd = ft_strjoin(cmd, sub);
		free(sub);
		quotes--;
	}*/
	return (cmd);
}
