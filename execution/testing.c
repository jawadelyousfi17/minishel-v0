#include "../includes/minishell.h"

t_data *alloc_cmds(char *str)
{
    t_data *test_1 = malloc(sizeof(t_data));
	// t_cmd *cmd = malloc(sizeof(t_cmd));
	// cmd->cmd = true;
	// cmd->cmd = NULL;
	// cmd->cmd = ft_split("/bin/ls la", ' ');

	test_1->redirect_input = NO;
	test_1->infile = "main.c";
	test_1->n_of_cmds = 3;
	test_1->outfile = NULL;
	test_1->pipe = false;
	test_1->pipe_cmd = malloc(3 * sizeof(t_data *));
	test_1->limiter = ft_strdup("end");
	test_1->redirect_output = NO;
	test_1->outfile = "out";
	// test_1->cmd = cmd;
	test_1->cmd = ft_split(str, ' ');

	return test_1;
}

t_data *testing_cmd(char *str) {
	t_data *test_1 = malloc(sizeof(t_data));
	// t_cmd *cmd = malloc(sizeof(t_cmd));
	// cmd->cmd = true;
	// cmd->cmd = NULL;
	// cmd->cmd = ft_split("/bin/ls la", ' ');

	test_1->redirect_input = NO;
	test_1->infile = "main.c";
	test_1->n_of_cmds = 5;
	test_1->outfile = NULL;
	test_1->pipe = true;
	test_1->pipe_cmd = malloc(4 * sizeof(t_data *));
	test_1->pipe_cmd[0] = alloc_cmds("ls -la");
	test_1->pipe_cmd[1] = alloc_cmds("grep minishell");
	test_1->pipe_cmd[2] = alloc_cmds("cat -e");
	test_1->pipe_cmd[3] = alloc_cmds("tr m q");
	test_1->pipe_cmd[4] = alloc_cmds("tr l o");
	test_1->limiter = ft_strdup("end");
	test_1->redirect_output = NO;
	test_1->outfile = "out";
	// test_1->cmd = cmd;
	test_1->cmd = ft_split(str, ' ');

	return test_1;
}