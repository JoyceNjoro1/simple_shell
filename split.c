#include "main.h"

/**
 * swap_char - Swap | and & for non-printed characters in the input string.
 *
 * @input: Input string
 * @swap_type: Type of swap
 * Return: Swapped string
 */
char *swap_char(char *input, int swap_type)
{
    int i;

    if (swap_type == 0)
    {
        for (i = 0; input[i]; i++)
        {
            if (input[i] == '|')
            {
                if (input[i + 1] != '|')
                    input[i] = 16;
                else
                    i++;
            }

            if (input[i] == '&')
            {
                if (input[i + 1] != '&')
                    input[i] = 12;
                else
                    i++;
            }
        }
    }
    else
    {
        for (i = 0; input[i]; i++)
        {
            input[i] = (input[i] == 16 ? '|' : input[i]);
            input[i] = (input[i] == 12 ? '&' : input[i]);
        }
    }
    return input;
}

/**
 * add_nodes - Add separators and command lines to the lists.
 *
 * @separator_list: Head of the separator list
 * @command_line_list: Head of the command lines list
 * @input: Input string
 * Return: No return
 */
void add_nodes(sep_list **separator_list, line_list **command_line_list, char *input)
{
    int i;
    char *line;

    input = swap_char(input, 0);

    for (i = 0; input[i]; i++)
    {
        if (input[i] == ';')
            add_sep_node_end(separator_list, input[i]);

        if (input[i] == '|' || input[i] == '&')
        {
            add_sep_node_end(separator_list, input[i]);
            i++;
        }
    }

    line = _strtok(input, ";|&");
    do
    {
        line = swap_char(line, 1);
        add_line_node_end(command_line_list, line);
        line = _strtok(NULL, ";|&");
    } while (line != NULL);
}

/**
 * go_next - Move to the next command line stored in the lists.
 *
 * @separator_list: Separator list
 * @command_line_list: Command line list
 * @datash: Data structure
 * Return: No return
 */
void go_next(sep_list **separator_list, line_list **command_line_list, data_shell *datash)
{
    int loop_separator;
    sep_list *ls_separator;
    line_list *ls_command_line;

    loop_separator = 1;
    ls_separator = *separator_list;
    ls_command_line = *command_line_list;

    while (ls_separator != NULL && loop_separator)
    {
        if (datash->status == 0)
        {
            if (ls_separator->separator == '&' || ls_separator->separator == ';')
                loop_separator = 0;
            if (ls_separator->separator == '|')
                ls_command_line = ls_command_line->next, ls_separator = ls_separator->next;
        }
        else
        {
            if (ls_separator->separator == '|' || ls_separator->separator == ';')
                loop_separator = 0;
            if (ls_separator->separator == '&')
                ls_command_line = ls_command_line->next, ls_separator = ls_separator->next;
        }
        if (ls_separator != NULL && !loop_separator)
            ls_separator = ls_separator->next;
    }

    *separator_list = ls_separator;
    *command_line_list = ls_command_line;
}

/**
 * split_commands - Split command lines according to separators (;, |, and &)
 * and execute them.
 *
 * @datash: Data structure
 * @input: Input string
 * Return: 0 to exit, 1 to continue
 */
int split_commands(data_shell *datash, char *input)
{
    sep_list *head_separator_list, *list_separator;
    line_list *head_command_line_list, *list_command_line;
    int loop;

    head_separator_list = NULL;
    head_command_line_list = NULL;

    add_nodes(&head_separator_list, &head_command_line_list, input);

    list_separator = head_separator_list;
    list_command_line = head_command_line_list;

    while (list_command_line != NULL)
    {
        datash->input = list_command_line->line;
        datash->args = split_line(datash->input);
        loop = exec_line(datash);
        free(datash->args);

        if (loop == 0)
            break;

        go_next(&list_separator, &list_command_line, datash);

        if (list_command_line != NULL)
            list_command_line = list_command_line->next;
    }

    free_sep_list(&head_separator_list);
    free_line_list(&head_command_line_list);

    if (loop == 0)
        return 0;
    return 1;
}

/**
 * split_line - Tokenizes the input string.
 *
 * @input: Input string.
 * Return: String split into tokens.
 */
char **split_line(char *input)
{
    size_t buffer_size;
    size_t i;
    char **tokens;
    char *token;

    buffer_size = TOK_BUFSIZE;
    tokens = malloc(sizeof(char *) * (buffer_size));
    if (tokens == NULL)
    {
        write(STDERR_FILENO, ": allocation error\n", 18);
        exit(EXIT_FAILURE);
    }

    token = _strtok(input, TOK_DELIM);
    tokens[0] = token;

    for (i = 1; token != NULL; i++)
    {
        if (i == buffer_size)
        {
            buffer_size += TOK_BUFSIZE;
            tokens = _reallocdp(tokens, i, sizeof(char *) * buffer_size);
            if (tokens == NULL)
            {
                write(STDERR_FILENO, ": allocation error\n", 18);
                exit(EXIT_FAILURE);
            }
        }
        token = _strtok(NULL, TOK_DELIM);
        tokens[i] = token;
    }

    return tokens;
}

