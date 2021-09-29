#include "../include/minishell.h"

void    parser(t_ms *minishell, int i)
{
    int j;
    int start; // начало где находится двойная кавычка
    int end; // конец где находится двойная кавычка
    char *tmp;
    // char *tmp1;
    int len;
    // char *tmp1;
    (void)i;

    j = 0;
    tmp = NULL;
    while (minishell->input[j] != '\"')
        j++;
    start = j;
    while (minishell->input[j] != '\"')
        j++;
    end = j;
    len = ft_strlen(&minishell->input[start]);
    tmp = malloc(sizeof(char *) * len);
    tmp = ft_strjoin(tmp, &minishell->input[start]);
    tmp = trimmer(tmp, '\"');
    printf("%s\n", tmp);
}

char    *trimmer(char *str, char c)
{
    int len;

    len = ft_strlen(str);
    if (*str == c && str[len-1] == c)
    {
        ft_memmove(str, &str[1], len - 1);
        str[len - 2] = '\0';
    }
    return (str);
}



