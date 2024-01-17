#include "../minishell.h"

char *find_env_value(t_env *env_list, char *key) 
{
    while (env_list != NULL) 
	{
        if (ft_strncmp(env_list->key, key, ft_strlen(key) + 1))
		{
            return env_list->value;
        }
        env_list = env_list->next;
    }
    return NULL;
}

void replace_env_variables_in_token(t_shell *shell_info, t_token *token) 
{
    while (token != NULL) {
        if (token->value[0] == '$') 
		{
            char *env_var_name = token->value + 1;
            char *env_value = find_env_value(shell_info->env, env_var_name);

            if (env_value != NULL) {
                free(token->value);
                token->value = ft_strndup(env_value, ft_strlen(env_value));
            }
        }
        token = token->next;
    }
}
