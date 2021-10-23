/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <tharodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:19:55 by tharodon          #+#    #+#             */
/*   Updated: 2021/10/23 16:19:56 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_rdct_input(char *dest)
{
	if (!ft_strncmp(dest, ">>", 2) || \
	!ft_strncmp(dest, "<<", 2) || \
	!ft_strncmp(dest, ">", 1) || \
	!ft_strncmp(dest, "<", 1))
		return (1);
	return (0);
}

char	*add_space(char *s, int i)
{
	char	*new_input;
	int		str;

	str = 0;
	new_input = (char *)malloc(sizeof(char) * (ft_strlen(s) + 2));
	while (s[i] && (s[i] == '>' || s[i] == '<'))
		i++;
	while (str != i)
	{
		new_input[str] = s[str];
		str++;
	}
	new_input[str] = ' ';
	while (s[i])
		new_input[++str] = s[i++];
	new_input[++str] = '\0';
	return (new_input);
}

char	*space_between_redirect_and_file(char *input)
{
	char	*temp;
	int		i;
	char	c;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			c = input[i];
			while (input[++i] != c)
				;
			continue ;
		}
		if (is_rdct_input(input + i) && !is_rdct_input(input + i + 1))
		{
			temp = input;
			input = add_space(input, i);
			free_str(temp);
		}
	}
	return (input);
}
