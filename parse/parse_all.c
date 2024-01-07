#include "../minishell.h"

int	parse_all(/*t_shell *shell_info, */char *str)
{
	t_token *token;
	token = NULL;
	// 1. parsing 전 에러 handling (>> 갯수, 파이프 닫혔는지 등 확인) -> 나중에

	// 2. 파이프 단위로 token 처리
	parse_pipe(&token, str);
	// 3. 리다이렉션 처리
	parse_redir(&token);
	// 4. white space 처리 -> token 완성
	parse_space(&token);

	t_token *current_token;
	current_token = token;
    while (current_token)
    {
        printf("Type: %d, Value: [%s]\n", current_token->type, current_token->value);
        current_token = current_token->next;
    }
	
	// 5. token 순회하면서 invalid token 삭제

	// 6. token 없거나 에러 걸리면 token free하고 fail return -> 나중에

	// 7. envp update -> 은영 실행부에서
	
	// 8. cmd init
	// 9. cmd argument 합치기
	return (SUCCESS);
}
