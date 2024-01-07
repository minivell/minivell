#include "../minishell.h"

void parse_redir(t_token **token)
{
    t_token *tmp = *token;
    t_token *next_tmp;
    t_token *new_token;

    while (tmp)
    {
        next_tmp = tmp->next; // 다음 토큰을 안전하게 저장

        if (tmp->token_flag && tmp->type == WORD)
        {
            new_token = NULL;
            parse_and_extract_redir(&new_token, tmp->value);
            if (new_token)
            {
                // 현재 토큰을 새로운 토큰으로 교체
                tmp->token_flag = FALSE;
                replace_token(token, tmp, new_token);
                tmp = next_tmp; // 저장된 next 값으로 tmp 업데이트
                continue; // 다음 반복으로 넘어감
            }
        }
        tmp = next_tmp; // 다음 토큰으로 이동
    }
}

void replace_token(t_token **token_list, t_token *old_token, t_token *new_tokens)
{
    t_token *prev = NULL;
    t_token *current = *token_list;
    while (current != old_token)
    {
        prev = current;
        current = current->next;
    }
    if (prev)
        prev->next = new_tokens;
    else
        *token_list = new_tokens;

    t_token *last_new = new_tokens;
    while (last_new->next)
        last_new = last_new->next;

    last_new->next = old_token->next;
    free(old_token->value);
    free(old_token);
}

void parse_and_extract_redir(t_token **token, char *str)
{
    char *tmp = str;
    t_quote q;
    q.quote_flag = FALSE;

    while (*str)
    {
        if (!check_quote(&q, *str) && (*str == '<' || *str == '>'))
        {
            if (str != tmp)
                add_back_token(token, new_token(WORD, ft_strndup(tmp, str - tmp)));
            
            create_redir_token(token, &str);
            tmp = str;
        }
        else
        {
            str++;
        }
    }

    if (*tmp)
        add_back_token(token, new_token(WORD, ft_strdup(tmp)));
}

void identify_redir(t_token **token, char **str, char *start_str)
{
    t_quote q;
    q.quote_flag = FALSE;
    
    if (!check_quote(&q, **str) && (**str == '<' || **str == '>'))
    {
        if (*str != start_str)
            add_back_token(token, new_token(WORD, ft_strndup(start_str, *str - start_str)));
        
        create_redir_token(token, str); // start_str 인자 제거
    }
}


void create_redir_token(t_token **token, char **str)
{
    if (**str == '<' && *(*str + 1) != '<')
    {
        (*str)++;
        add_back_token(token, new_token(IN_REDIR, ft_strdup("<")));
    }
    else if (**str == '<' && *(*str + 1) == '<')
    {
        (*str) += 2;
        add_back_token(token, new_token(HEREDOC, ft_strdup("<<")));
    }
    else if (**str == '>' && *(*str + 1) != '>')
    {
        (*str)++;
        add_back_token(token, new_token(OUT_REDIR, ft_strdup(">")));
    }
    else if (**str == '>' && *(*str + 1) == '>')
    {
        (*str) += 2;
        add_back_token(token, new_token(APPEND_REDIR, ft_strdup(">>")));
    }
}

