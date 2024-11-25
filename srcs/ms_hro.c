/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_hro.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:07:18 by kjung             #+#    #+#             */
/*   Updated: 2024/11/25 21:34:03 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	hro_child_while(char *buffer, size_t buffer_size)
{
	ssize_t	bytes_read;
	int		empty_lines;

	empty_lines = 0;
	bytes_read = read(STDIN_FILENO, buffer, buffer_size);
	while (bytes_read > 0)
	{
		if (bytes_read == 1 && buffer[0] == '\n')
		{
			empty_lines++;
			if (empty_lines >= 2)
				break ;
		}
		else
			empty_lines = 0;
		write(STDOUT_FILENO, buffer, bytes_read);
		bytes_read = read(STDIN_FILENO, buffer, buffer_size);
	}
}

void	hro_child(t_pipe_info *info, t_cmd *cmd)
{
	char	buffer[4096];

	if (info->prev_pipe != -1)
	{
		dup2(info->prev_pipe, STDIN_FILENO);
		close(info->prev_pipe);
	}
	if (cmd->next && info->pipe_fd[1] != -1)
	{
		dup2(info->pipe_fd[1], STDOUT_FILENO);
		close(info->pipe_fd[1]);
	}
	handle_redirections(cmd);
	hro_child_while(buffer, sizeof(buffer));
	exit(0);
}

// void	handle_redirection_only(t_cmd *cmd, t_pipe_info *info)
// {
// 	pid_t	pid;

//     if (cmd->next)  // 파이프가 있는 경우
//     {
//         if (pipe(info->pipe_fd) == -1)
//         {
//             perror("pipe");
//             exit(1);
//         }
//     }
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		exit(1);
// 	}
// 	if (pid == 0)
// 		hro_child(info, cmd);
// 	else
// 	{
// 		if (info->prev_pipe != -1)
// 			close(info->prev_pipe);
// 		if (cmd->next)
// 		{
// 			close(info->pipe_fd[1]);
// 			info->prev_pipe = info->pipe_fd[0];
// 		}
// 		else
// 			info->prev_pipe = -1;
// 		wait_all_children();
// 	}
// }

void    handle_redirection_only(t_cmd *cmd, t_pipe_info *info)
{
    pid_t   pid;

    // 파이프 fd 초기값 설정
    info->pipe_fd[0] = -1;
    info->pipe_fd[1] = -1;

    // 다음 명령어가 있을 때만 파이프 생성
    if (cmd->next)
    {
        if (pipe(info->pipe_fd) == -1)
        {
            perror("pipe");
            exit(1);
        }
    }
    
    pid = fork();
    if (pid == -1)
    {
        if (info->pipe_fd[0] != -1)
            close(info->pipe_fd[0]);
        if (info->pipe_fd[1] != -1)
            close(info->pipe_fd[1]);
        perror("fork");
        exit(1);
    }
    if (pid == 0)
    {
        // 자식 프로세스에서는 읽기 end를 닫음
        if (cmd->next && info->pipe_fd[0] != -1)
            close(info->pipe_fd[0]);
            
        hro_child(info, cmd);
    }
    else
    {
        // 부모 프로세스
        if (info->prev_pipe != -1)
        {
            close(info->prev_pipe);
            info->prev_pipe = -1;
        }
        
        if (cmd->next)
        {
            if (info->pipe_fd[1] != -1)
                close(info->pipe_fd[1]);  // 쓰기 end를 닫음
            info->prev_pipe = info->pipe_fd[0];  // 다음 명령어를 위해 읽기 end 저장
        }
        
        waitpid(pid, NULL, 0);
    }
}
