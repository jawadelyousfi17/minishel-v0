#include "../includes/minishell.h"

void	process1(int fd[2][2], t_data *data, char **env)
{
	char	*p;

	dup_and_close(0, fd[0][1], fd);
	redirection(data);
	p = process_helper(data);
	if (!p)
		if_not_found(data);
	execve(p, data->cmd, env);
	if_execve_failed(data, p);
}

void	last_process(int fd[2][2], t_data *data, char **env,int i)
{
	char	*p;
    
	if (i % 2 == 0)
		dup_and_close(fd[1][0], 1, fd);
	else
		dup_and_close(fd[0][0], 1, fd);
		// sleep(20);
	redirection(data);
	p = process_helper(data);
	if (!p)
		if_not_found(data);
	execve(p, data->cmd, env);
	if_execve_failed(data,p);
}

// void	process_in_middle(int fd[2][2], t_data *data, char **env)
// {
// 	char	*p;
// 	char    *s = malloc(20);
// 	read(fd[0],s,20);
// 	printf("--|%s|----\n",s);
// 	dup_and_close(fd[0], fd[1], fd);
//     redirection(data);
// 	p = process_helper(data);
// 	if (!p)
// 		if_not_found(data);
// 	execve(p, data->cmd, env);
// 	if_execve_failed(data,p);
// }
void	process_in_middle_odd(int fd[2][2], t_data *data, char **env)
{
	char	*p;

	dup_and_close(fd[0][0], fd[1][1], fd);
    redirection(data);
	p = process_helper(data);
	if (!p)
		if_not_found(data);
	execve(p, data->cmd, env);
	if_execve_failed(data,p);
}

void	process_in_middle_even(int fd[2][2], t_data *data, char **env)
{
	char	*p;

	dup_and_close(fd[1][0], fd[0][1], fd);
    redirection(data);
	p = process_helper(data);
	if (!p)
		if_not_found(data);
	execve(p, data->cmd, env);
	if_execve_failed(data,p);
}
