
NAME= minishell

FLAGS = -fsanitize=address 

env_src = env/init_env.c env/utils_env.c env/get_env.c env/set_env.c
builtin_src = builtin/export_no_args.c builtin/echo.c builtin/unset.c builtin/env.c builtin/utils_builtin.c builtin/export.c
parser_src = parser/execut_here_doc.c parser/init_data.c parser/expan_env_utils2.c parser/init_data_utils.c parser/expand_env.c parser/lexer.c parser/expand_env_utils.c parser/parser.c parser/expander.c parser/spliter.c parser/ft_count_tokens.c parser/utils_parser.c
executions_src = execution/cd.c execution/pipe.c execution/utils.c execution/errors.c execution/pipe_utils.c execution/main.c execution/process_utils.c
gb_src = garbage_collector/garbage_collector.c
token = tokenizer/check_ambs.c tokenizer/check_syntax.c tokenizer/close_here_docs.c tokenizer/exec_here_doc.c tokenizer/expand_here_doc.c tokenizer/expand_quotes.c tokenizer/expand_vars_0.c tokenizer/expand_vars_1.c tokenizer/init_data.c tokenizer/initialize.c tokenizer/join_tokens.c tokenizer/tokenizer.c tokenizer/tokenizer_1.c tokenizer/tokenizer_2.c
utils = utils/error_log.c utils/linked_list.c utils/linked_list_1.c utils/string_0.c utils/string_1.c utils/string_2.c utils/string_3.c utils/string_4.c utils/tokens_0.c utils/tokens_1.c utils/valid_export.c utils/vars.c utils/ft_atoi.c

parser_objs = $(token:.c=.o)
executions_obj = $(executions_src:.c=.o)
gb_obj = $(gb_src:.c=.o)
env_obj = $(env_src:.c=.o)
builtin_obj = $(builtin_src:.c=.o)
utils_obj = $(utils:.c=.o)
readline = -lreadline $(rdl_path)

all : $(NAME)

# test
test_src = tests/test.c
test_obj = $(test_src:.c=.o)
test : $(test_obj) $(parser_objs) $(gb_obj) $(builtin_obj) $(env_obj) $(utils_obj) 
	cc $(FLAGS)  $(parser_objs) $(test_obj) $(gb_obj) $(builtin_obj) $(env_obj) $(utils_obj) $(readline)  -o test
test/%.o : test/%.c include/minishell.h
	cc $(FLAGS) -c $< $(rdl_include) -o $@
# test


$(NAME) : $(parser_objs) $(executions_obj) $(gb_obj) $(builtin_obj) $(env_obj) $(utils_obj) 
	cc $(FLAGS) $(parser_objs) $(executions_obj) $(gb_obj) $(builtin_obj) $(env_obj) $(utils_obj) $(readline) -o $(NAME)

tokenizer/%.o : tokenizer/%.c include/minishell.h
	cc $(FLAGS) -c $< $(rdl_include) -o $@

execution/%.o : execution/%.c include/minishell.h
	cc $(FLAGS) -c $< $(rdl_include) -o $@

garbage_collector/%.o : garbage_collector/%.c include/minishell.h
	cc $(FLAGS) -c $< $(rdl_include) -o $@
builtin/%.o : builtin/%.c include/minishell.h
	cc $(FLAGS) -c $< $(rdl_include) -o $@
env/%.o : env/%.c include/minishell.h
	cc $(FLAGS) -c $< $(rdl_include) -o $@

utils/%.o : utils/%.c include/minishell.h
	cc $(FLAGS) -c $< $(rdl_include) -o $@

clean : 
	rm -rf $(parser_objs) $(executions_obj) $(gb_obj) $(builtin_obj) $(env_obj) $(utils_obj) $(test_obj)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : clean