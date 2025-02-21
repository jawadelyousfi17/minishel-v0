#include "../includes/minishell.h"

#include <stdio.h>



void clean_t_cmd(t_cmd cmd) {
	
}

t_data *testing_cmd(char *str) {
	t_data *test_1 = malloc(sizeof(t_data));
	t_cmd *cmd = malloc(sizeof(t_cmd));
	cmd->cmd = true;
	cmd->cmd = NULL;
	cmd->cmd = ft_split("/bin/ls la", ' ');

	test_1->redirect_input = REDIRECT;
	test_1->infile = "infile";
	test_1->n_of_cmds = 1;
	test_1->outfile = NULL;
	test_1->pipe = false;
	test_1->pipe_cmd = NULL;
	
	test_1->redirect_output = NO;
	test_1->outfile = NULL;
	test_1->cmd = cmd;

	return test_1;
}

t_data *testing_pipe_cmd(char *str) {
	t_data *test_1 = malloc(sizeof(t_data));
	t_cmd *cmd = malloc(sizeof(t_cmd));
	cmd->cmd = true;
	cmd->cmd = NULL;
	cmd->cmd = ft_split("/bin/ls la", ' ');

	test_1->redirect_input = REDIRECT;
	test_1->infile = "infile";
	test_1->n_of_cmds = 1;
	test_1->outfile = NULL;
	test_1->pipe = false;
	test_1->pipe_cmd = NULL;
	
	test_1->redirect_output = NO;
	test_1->outfile = NULL;
	test_1->cmd = cmd;

	return test_1;
}


int main() {

	t_data *cmd = testing_cmd("");
	t_data **five_cmd = malloc(sizeof(t_data) * 6);

	for (size_t i = 0; i < 5; i++)
	{
		five_cmd[i] = testing_cmd("dd");
	}
	five_cmd[5] = NULL;
	

	printf("cmd = %s\n", five_cmd[0]->cmd.message);
	clean_t_cmd(five_cmd[0]->cmd);

}

void clean_t_data(t_data **tdata) {

}
