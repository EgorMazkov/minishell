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
    // if (minishell->line[j][a] == '\"')
    // {
    //     while (minishell->line[j][a] != '\"')
    //     {
    //         tmp1 = minishell->line[j];
    //         tmp = ft_strjoin(tmp, tmp1);
    //         j++;
    //     }
    // }

//echo "123 123 123 123 123 123 1"

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

int preparser(t_ms *minishell, t_se *se)
{
    int i;
    int len;
    int j;
    int double_quote;

    i = 0;
    j = 0;
    double_quote = 0;
    len = ft_strlen(&minishell->input_line[j][i]);
    while (minishell->input_line[i][j] != '\"' && j != len)
        j++;
    if (j == len)
        return (double_quote);
    else
    {
        double_quote = j;
        se->start = j;
        j++;
        while (minishell->input_line[i][j] != '\"')
            j++;
        se->end = j;
        return (double_quote);
    }

}