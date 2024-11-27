/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 07:03:28 by kjung             #+#    #+#             */
/*   Updated: 2024/11/26 22:26:27 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_dir(t_cmd *cmd)
{
	struct stat	*buf;

	buf = ft_calloc(sizeof(struct stat), 1);
	stat(cmd->cmd, buf);
	if (S_ISDIR(buf->st_mode))
	{
		ft_putstr_fd("Minishell: Is Directory\n", STDERR_FILENO);
		free(buf);
		exit(1);
	}
	free(buf);
	return ;
}

void	execute_command(t_cmd *cmd, t_data **data)
{
	char	*full_path;
	char	**new_args;
	int		i;

	if (!cmd->cmd || cmd->cmd[0] == '\0')
		exit(0);
	check_dir(cmd);
	full_path = find_path((*data)->envp, cmd->cmd);
	if (!full_path)
		exit(ft_print_ret("Command not found: ", 2));
	new_args = malloc(sizeof(char *) * (cmd->arg_cnt + 2));
	if (!new_args)
	{
		perror("malloc");
		exit(1);
	}
	new_args[0] = cmd->cmd;
	i = -1;
	while (++i < cmd->arg_cnt)
		new_args[i + 1] = cmd->args[i];
	new_args[cmd->arg_cnt + 1] = NULL;
	execve(full_path, new_args, (*data)->envp);
	perror("execve");
	exit(1);
}

// void    execute_command(t_cmd *cmd, t_data **data)
// {
//     char    *full_path;
//     char    **new_args;
//     int     i;

//     if (!cmd->cmd || cmd->cmd[0] == '\0')
//         exit(0);
        
//     check_dir(cmd);
//     full_path = find_path((*data)->envp, cmd->cmd);
//     if (!full_path)
//     {
//         fprintf(stderr, "Command not found: %s\n", cmd->cmd);
//         exit(127);  // 명령어를 찾을 수 없을 때의 표준 exit code
//     }
//     new_args = malloc(sizeof(char *) * (cmd->arg_cnt + 2));
//     if (!new_args)
//     {
//         free(full_path);  // 메모리 누수 방지
//         perror("malloc");
//         exit(1);
//     }
    
//     // 인자 배열 설정
//     new_args[0] = cmd->cmd;
//     i = -1;
//     while (++i < cmd->arg_cnt)
//         new_args[i + 1] = cmd->args[i];
//     new_args[cmd->arg_cnt + 1] = NULL;
//     printf("fuck\n");
//     // execve 실행
//     execve(full_path, new_args, (*data)->envp);
    
//     // execve가 실패한 경우에만 여기에 도달
//     perror("execve");
//     free(full_path);
//     free(new_args);
//     exit(126);  // execve 실패 시의 표준 exit code
// }

int	is_special_builtin(t_cmd *cmd)
{
	if (!cmd->cmd)
		return (0);
	if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd->cmd, "export", 6) == 0)
		return (1);
	if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
		return (1);
	return (0);
}

void	execute_pipeline(t_data **data)
{
	t_pipe_info	info;
	// pid_t		*pids;

	// pids = malloc(sizeof(pid_t) * (*data)->cmdline->count);
	// if (!pids)
	// {
	// 	perror("malloc");
	// 	exit(1);
	// }
	info.prev_pipe = -1;
	info.data = data;
	// init_info(data, &info);
	exe_pipe_while(data, &info);
	// free(pids);
	ft_ctrl_signal();
}
